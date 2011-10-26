//worked!!

#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <sys/types.h>
using namespace std;

int main (int argc, char** argv){
    

    IplImage* img = 0;
    IplImage* tmpImage = 0; 
    
    if((img = cvLoadImage(argv[1],CV_LOAD_IMAGE_GRAYSCALE)) == 0 ) {
        perror("cvLoadImage");
    }
    
    CvMat *output1Ch = cvCreateMat(img->height, img->width, CV_32FC1);
    cvConvertScale(img, output1Ch);
    //output1Ch = cvGetMat(tmpImage,output1Ch,0,0);
    
    CvMat *input_morph = cvCreateMat(output1Ch->height, output1Ch->width, CV_32FC1);
    cvThreshold(output1Ch, input_morph, 100, 255.0, CV_THRESH_BINARY);
    
    IplConvKernel *se1 = cvCreateStructuringElementEx(3, 3, 1, 1, CV_SHAPE_ELLIPSE);
    cvMorphologyEx(input_morph, input_morph, NULL, se1, CV_MOP_OPEN);
    
    IplImage *tmp8UC1 = cvCreateImage(cvGetSize(input_morph), IPL_DEPTH_8U, 1);
    cvConvert(input_morph, tmp8UC1);
    
    cvNamedWindow("result", CV_WINDOW_AUTOSIZE);
    cvShowImage("result",tmp8UC1);
    cvWaitKey(10000);
    cvDestroyWindow("result");
    
    cvReleaseImage(&img);
    cvReleaseImage(&tmpImage);
    cvReleaseImage(&tmp8UC1);
    cvReleaseMat(&output1Ch);
    cvReleaseMat(&input_morph);
    
    return 0;
}
