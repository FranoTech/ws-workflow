#include <iostream>
#include <cv.h>
#include <highgui.h>
using namespace std;

int main (int argc,char** argv)
{
    CvMat *output1Ch  = (CvMat*)cvLoad("output1Ch");
    CvMat *input_morph = cvCreateMat(output1Ch->height, output1Ch->width, CV_32FC1);
    cvThreshold(output1Ch, input_morph, -0.5, 255.0, CV_THRESH_BINARY);
    
    IplConvKernel *se1 = cvCreateStructuringElementEx(3, 3, 1, 1, CV_SHAPE_ELLIPSE);
    cvMorphologyEx(input_morph, input_morph, NULL, se1, CV_MOP_OPEN);
    
    IplImage *tmp8UC1 = cvCreateImage(cvGetSize(input_morph), IPL_DEPTH_8U, 1);
    cvNamedWindow("result", CV_WINDOW_AUTOSIZE);
    cvShowImage("result", tmp8UC1);
    cvWaitKey(10000);
    cvDestroyWindow("result");
    cvReleaseImage(&tmp8UC1);

    
}
