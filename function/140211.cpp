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
    IplImage* s = cvCreateImage(cvGetSize(src), IPL_DEPTH_32F, 1);


    cvNamedWindow("result", CV_WINDOW_AUTOSIZE);
    cvShowImage("result", dst);
    cvWaitKey(10000);
    cvDestroyWindow("result");
    
    
    
    /* release memory */
    cvReleaseImage(&img);
    cvReleaseImage(&tmpImage);
    cvReleaseMat(&s);
    //cvReleaseImage(&tmp8UC1);
    
    return 0;
}
