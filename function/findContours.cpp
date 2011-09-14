#include <iostream>
#include <fstream>
//#include <cv.hpp>
#include <cv.h>
#include <highgui.h>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;
int saveMat( string& filename, const Mat& M);
int readMat( const string& filename, Mat& M);

int main (int argc, char** argv){
    
    Mat src  = imread(argv[1],0);
    Mat gray;
    threshold(src, gray, 127.0, 255.0, CV_THRESH_BINARY);
    cout<<"threshold"<<endl;
    
    CvMat input_morph = gray;
    //fail
    //CvMat *input_morph = cvCreateMatHeader(input_morph_tmp.rows, input_morph_tmp.cols, CV_32FC1);
   	//input_morph->data.ptr = input_morph_tmp.data.ptr; 
    
    //fail
    //CvMat *input_morph = cvCreateMat(input_morph_tmp.rows, input_morph_tmp.cols, CV_32FC1);
    //cvConvertScale(input_morph, &input_morph_tmp);
    
    cout<<"input_morph->data.ptr = input_morph_tmp.data.ptr; "<<endl;
    
    IplImage *tmp8UC1 = NULL;;
	CvMemStorage *storage = cvCreateMemStorage();
	CvSeq *first_con = NULL;
	CvSeq *cur = NULL;
	CvMat *out_single = NULL;
	//CvMat *output_morph = NULL;
	
    cout<<"init var"<<endl;
    
    out_single = cvCreateMat(input_morph.rows, input_morph.cols, CV_32FC1);
    cvSetZero(out_single);

    tmp8UC1 = cvCreateImage(cvGetSize(&input_morph), IPL_DEPTH_8U, 1);        
    cout<<"init out_single and tmp8UC1"<<endl;    
        
    // remove small cells and fill holes.
    cvConvert(&input_morph, tmp8UC1);
    
    cout<<"cvConvert"<<endl;
    
    cvFindContours(tmp8UC1, storage, &first_con, sizeof(CvContour), CV_RETR_EXTERNAL);
    cur = first_con;
    cout<<"cvFindContours(tmp8UC1"<<endl;
    while (cur != NULL) {
        double area = fabs(cvContourArea(cur));
        cout<<area<<"    ";
        int npts = cur->total;
        CvPoint *p = new CvPoint[npts];
        cvCvtSeqToArray(cur, p);
        if (area < 200.0) // remove small area
            cvFillPoly(&input_morph, &p, &npts, 1, cvScalar(0.0)); // remove from input
        else if (area < 1500.0) {
            cvFillPoly(out_single, &p, &npts, 1, cvScalar(255.0)); // move to single
            cvFillPoly(&input_morph, &p, &npts, 1, cvScalar(0.0)); // remove from input
        }else
            cvFillPoly(&input_morph, &p, &npts, 1, cvScalar(255.0)); // fill hole
        delete[] p;
        cur = cur->h_next;
    }
    cout<<endl;

    cvNamedWindow("out_single", CV_WINDOW_AUTOSIZE);
    cvShowImage("out_single", out_single);
    cvWaitKey(10000);
    cvDestroyWindow("out_single");
    
    
    cvNamedWindow("input_morph", CV_WINDOW_AUTOSIZE);
    cvShowImage("input_morph", &input_morph);
    cvWaitKey(10000);
    cvDestroyWindow("input_morph");
    
    cvReleaseMat(&out_single);
    //cvReleaseMat(&input_morph_tmp);
    //cvReleaseMat(input_morph);
    src.release();
    gray.release();
    
    
    return 0;
}

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


