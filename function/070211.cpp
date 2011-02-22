#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <sys/types.h>
using namespace std;

int main (int argc, char** argv){
    
    /*  init  */ 
    IplImage* img = 0;
    IplImage* tmpImage = 0; 
    IplImage *tmp8UC1 = 0;
    
    if((img = cvLoadImage(argv[1],1)) == 0 ) {
        perror("cvLoadImage");
    }
    
    //tmpImage = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 1);
    //tmpImage->imageData = img->imageData;
    //cvCopy(img,tmpImage);
    
    //cvCvtColor(img,tmpImage,CV_BGR2GRAY);

    CvMat *output1Ch = cvCreateMat(img->height, img->width, CV_32FC1);
    //cvConvertScale(tmpImage, output1Ch);
    cvConvertScale(img, output1Ch);
    
    cvSave( "output1Ch.xml", &output1Ch);
    
    /* view image */
    //cvNamedWindow("result", CV_WINDOW_AUTOSIZE);
    //cvShowImage("result", tmpImage);
    ////cvShowImage("result", img);
    //cvWaitKey(10000);
    //cvDestroyWindow("result");
    
    //CvMat *input_morph = cvCreateMat(output1Ch->height, output1Ch->width, CV_32FC1);
    //cvThreshold(output1Ch, input_morph, -0.5, 255.0, CV_THRESH_BINARY);
    
    //IplConvKernel *se1 = cvCreateStructuringElementEx(3, 3, 1, 1, CV_SHAPE_ELLIPSE);
    //cvMorphologyEx(input_morph, input_morph, NULL, se1, CV_MOP_OPEN);
    
    //tmp8UC1 = cvCreateImage(cvGetSize(input_morph), IPL_DEPTH_8U, 1);
    //cvConvert(input_morph, tmp8UC1);
    
    cvNamedWindow("result", CV_WINDOW_AUTOSIZE);
    cvShowImage("result", output1Ch);
    cvWaitKey(10000);
    cvDestroyWindow("result");
    
    
    
    /* release memory */
    cvReleaseImage(&img);
    //cvReleaseImage(&tmpImage);
    cvReleaseMat(&output1Ch);
    //cvReleaseImage(&tmp8UC1);
    
    return 0;
}

