#include <iostream>
#include <fstream>
#include <cv.h>
#include <omp.h>

using namespace std;
using namespace cv;

int readMat( const char *filename, Mat& M);
int main (int argc, char** argv){
    
    Mat A;
    Mat B;
    
	if(!readMat(argv[1], A))
        cout<<"can't read image"<<endl;
        
    if(!readMat(argv[2], B))
        cout<<"can't read image"<<endl;

    int srcType1 = A.type();
    int srcType2 = B.type();

    if(srcType1 != srcType2)
    {
        B.convertTo(B, srcType1);
	}

    Mat dst;
    int i = 0;
    int j = 0;

    for(i = 0; i< )


    
    //~ bitwise_or(A, B, dst);
    
    dst.convertTo(dst, CV_8U);
    
    namedWindow("src", CV_WINDOW_AUTOSIZE);
    imshow("src", dst);
    waitKey(0);
    
    A.release();
    B.release();
    dst.release();
    
    return 0;

}

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
