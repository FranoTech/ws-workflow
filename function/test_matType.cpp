#include <iostream>
#include <fstream>
#include <cv.h>
#include <highgui.h>

using namespace std;
using namespace cv;

int getMatType ( const Mat& M)
{
	int type = 0;
    int chan = M.channels();
    int eSiz = (M.dataend-M.datastart)/(M.cols*M.rows*chan);
    
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
    
    return type;
}

int main (int argc, char** argv){
	
	Mat src  = imread(argv[1],0);
    cout<<"src type = "<<getMatType(src)<<endl;
	
    //Mat dst = Mat(src.rows, src.cols, CV_32FC1);
    //cout<<"dst type = "<<getMatType(dst)<<endl;
    
    src.convertTo(src, CV_32FC1);
    cout<<"src type = "<<getMatType(src)<<endl;
	//cout<<"dst type = "<<getMatType(dst)<<endl;

    
    src.release();
    //dst.release();
    
    return 0;
    
}

