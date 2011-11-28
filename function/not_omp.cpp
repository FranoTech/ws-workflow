#include <iostream>
#include <fstream>
#include <cv.h>
#include <highgui.h>
#include <omp.h>

using namespace std;
using namespace cv;
int saveMat( const char *filename, const Mat& M);
int readMat( const char *filename, Mat& M);

int main (int argc, char** argv){
    
    //Mat src  = imread(argv[1],0);
    // Mat dst;
    Mat src = 
    //int height    = src.rows;
    //int width     = src.cols;
    //int step      = src.step;
    //uchar *data   = (uchar *)src.data;
    //uchar *ddst   = (uchar *)dst.data;
    //uchar *data2      = (uchar *)dst->imageData;
    int i = step;
    #pragma omp parallel for
        for(int i = 0; i < src.rows; i++)
        {       
            for(int j = 0; j < src.cols; j++)
            {
                bitwise_not(src.at<uchar>(i, j), src.at<uchar>(i, j));
            }
        }
    if(!imwrite("not.jpg", src))
    {
		cout<<"error writing image"<<endl;
    }
    
    src.release();
    
    return 0;
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
