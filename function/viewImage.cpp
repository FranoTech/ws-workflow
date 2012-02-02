#include <iostream>
#include <fstream>
#include <cv.h>
//#include <highgui.h>

using namespace std;
using namespace cv;

int readMat( const char *filename, Mat& M);

int main (int argc, char** argv){
	
	Mat matSrc;
	if(!readMat(argv[1], matSrc))
			cout<<"can't read image"<<endl;
	else{
		
			namedWindow("src", CV_WINDOW_AUTOSIZE);
			imshow("src", matSrc);
			waitKey(0);
		}
   
    matSrc.release();
    
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
