#include <iostream>
#include <fstream>
#include <cv.h>
#include <highgui.h>
#include <sys/time.h>
#include <time.h>

using namespace std;
using namespace cv;

#define FILENAME_SIZE 60

int saveMat( string& filename, const Mat& M);

int main (int argc, char** argv){
    
    Mat src  = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    
    CvMat input3Ch = src;
    CV_Assert(input3Ch.cols == src.cols && input3Ch.rows == src.rows &&
    input3Ch.data.ptr == (uchar*)src.data && input3Ch.step == src.step);

    IplImage *tmp8UC3 = cvCreateImage(cvGetSize(&input3Ch), IPL_DEPTH_8U, 3);
    cvConvert(&input3Ch, tmp8UC3);
    
    
    if(!cvSaveImage("matToCvMat.jpg", tmp8UC3))
        cout<<"can't save image" << endl;
    
    cvReleaseImage(&tmp8UC3);
    //cvReleaseMat(input3Ch);
    src.release();
    return 0;
}
