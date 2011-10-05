#include <iostream>
#include <fstream>
#include <cv.h>
#include <highgui.h>

using namespace std;
using namespace cv;
int saveMat( string& filename, const Mat& M);
int readMat( const string& filename, Mat& M);

int main (int argc, char** argv){
    
    Mat src  = imread(argv[1],0);
    Mat gray;
    
    Mat result = Mat::zeros(src.rows,src.cols, CV_32FC1);
    threshold(src, gray, 127.0, 255.0, CV_THRESH_BINARY);
