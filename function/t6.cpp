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
    
    cvSave("o1Ch.xml",output1Ch);
    
    cvReleaseImage(&img);
    cvReleaseMat(&output1Ch);
    
    return 0;
}
