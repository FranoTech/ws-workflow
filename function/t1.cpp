//s = image w/ color, why ?

#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <sys/types.h>
using namespace std;

int main (int argc, char** argv){
    
    /*  init  */ 
    IplImage* img = 0;
    //IplImage* tmpImage = 0; 
    
    if((img = cvLoadImage(argv[1],1)) == 0 ) {
        perror("cvLoadImage");
    }
    IplImage* s = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
    s->imageData = img->imageData;
    cvCopy(img,s);

    cvNamedWindow("result", CV_WINDOW_AUTOSIZE);
    cvShowImage("result", s);
    cvWaitKey(10000);
    cvDestroyWindow("result");
    
    
    
    /* release memory */
    cvReleaseImage(&img);
    cvReleaseImage(&s);
    //cvReleaseMat(&s);
    //cvReleaseImage(&tmp8UC1);
    
    return 0;
}
