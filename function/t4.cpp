//convert 8U 1Ch -> 32F 1Ch

#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <sys/types.h>
using namespace std;

int main (int argc, char** argv){
    

    IplImage* img = 0;
    IplImage* tmpImage = 0; 

    
    //if((img = cvLoadImage(argv[1],CV_LOAD_IMAGE_GRAYSCALE)) == 0 ) {
        //perror("cvLoadImage");
    //}
    
    if((img = cvLoadImage(argv[1])) == 0 ) {
        perror("cvLoadImage");
    }
    
    tmpImage = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_32F, 1);
    cvConvert(img,tmpImage);
    
    CvMat *output1Ch = cvCreateMat(img->height, img->width, CV_32FC1);
    cvConvertScale(img,output1Ch);
    -
