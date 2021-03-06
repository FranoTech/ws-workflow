#include <iostream>
#include <fstream>
#include <cv.h>
#include <ml.h>
#include <highgui.h>
#include <sys/time.h>
#include <time.h>

using namespace std;
using namespace cv;

#define FILENAME_SIZE 60


void ByteArrayToANN(char *annfile, CvANN_MLP* ann);
int saveMat( const char *filename, const Mat& M);
int readMat( const char *filename, Mat& M);

int main (int argc, char** argv){
    
    IplImage *src = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);
    CvANN_MLP* neuron = NULL ;
    
    CvMat *input3Ch = cvCreateMat(src->height, src->width, CV_32FC3);
    CvMat *output1Ch = cvCreateMat(src->height, src->width, CV_32FC1);
    cvConvertScale(src, input3Ch);
    
    
    if (neuron == NULL ) 
        neuron = new CvANN_MLP();
	else 
        neuron->clear();
        
    ByteArrayToANN(argv[2], neuron);
    cout<<"loaded cia.tmp"<<endl;
    
    //~ CvMat input_nn = cvMat(input3Ch->height*input3Ch->width, 3, CV_32FC1, input3Ch->data.fl);
    //~ CvMat output_nn = cvMat(output1Ch->height*output1Ch->width, 1, CV_32FC1, output1Ch->data.fl);
    CvMat input_nn = cvMat(input3Ch->height*input3Ch->width, 3, CV_32FC1, input3Ch->data.fl);
    CvMat output_nn = cvMat(output1Ch->height*output1Ch->width, 1, CV_32FC1, output1Ch->data.fl);
    
    neuron->predict(&input_nn, &output_nn);
    
    cout<<"trained"<<endl;
    
    IplImage *tmp8UC1 = cvCreateImage(cvSize(output1Ch->width, output1Ch->height), IPL_DEPTH_8U, 1);
    cvConvertScale(output1Ch, tmp8UC1);
    //~ cvSaveImage("cppANN_result.jpg", tmp8UC1);

    cvNamedWindow("result", CV_WINDOW_AUTOSIZE);
    cvShowImage("result", tmp8UC1);
    cvWaitKey(10000);

    cvReleaseImage(&src);
    cvReleaseMat(&output1Ch);
    cvReleaseMat(&input3Ch);
    
    cvReleaseImage(&tmp8UC1);
    
    return 0;
}


void ByteArrayToANN(char *annfile, CvANN_MLP* ann)
{
    char *buffer;
    long size;
	ifstream file (annfile, ios::in|ios::binary|ios::ate);
    size = file.tellg();
    file.seekg (0, ios::beg);
    buffer = new char [size];
    file.read (buffer, size);
    file.close();
	CvFileStorage *cvfs = cvOpenFileStorage(annfile, NULL, CV_STORAGE_READ);

	if (cvfs != NULL) {
		ann->read(cvfs, cvGetFileNodeByName(cvfs, NULL, "CIA_Neuron"));
		cvReleaseFileStorage(&cvfs);
	}
}

/* helper function */
/* Save matrix to binary file */
int saveMat( const char *filename, const Mat& M){
    if (M.empty()){
       return 0;
    }
    ofstream out(filename, ios::out|ios::binary);
    if (!out)
       return 0;

    int cols = M.cols;
    int rows = M.rows;
    int chan = M.channels();
    int eSiz = (M.dataend-M.datastart)/(cols*rows*chan);

    /* Write header */
    out.write((char*)&cols,sizeof(cols));
    out.write((char*)&rows,sizeof(rows));
    out.write((char*)&chan,sizeof(chan));
    out.write((char*)&eSiz,sizeof(eSiz));

    /* Write data. */
    if (M.isContinuous()){
       out.write((char *)M.data,cols*rows*chan*eSiz);
    }
    else{
       return 0;
    }
    out.close();
    return 1;
}

/* Read matrix from binary file */
int readMat( const char *filename, Mat& M)
{    
    ifstream in(filename, ios::in|ios::binary);
    if (!in){
       M.data = NULL;
       return 0;
    }
    int cols;
    int rows;
    int chan;
    int eSiz;

    /* Read header */
    in.read((char*)&cols,sizeof(cols));
    in.read((char*)&rows,sizeof(rows));
    in.read((char*)&chan,sizeof(chan));
    in.read((char*)&eSiz,sizeof(eSiz));

    /* Determine type of the matrix */
    int type = 0;
    switch (eSiz){
    case sizeof(char):
         type = CV_8UC(chan);
         break;
    case sizeof(float):
         type = CV_32FC(chan);
         break;
    case sizeof(double):
         type = CV_64FC(chan);
         break;
    }

    /* Alocate Matrix. */
    M = Mat(rows,cols,type,Scalar(1));  

    /* Read data. */
    if (M.isContinuous()){
       in.read((char *)M.data,cols*rows*chan*eSiz);
    }
    else{
       return 0;
    }
    in.close();
    return 1;
} 
