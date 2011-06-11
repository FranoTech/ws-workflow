//s = image w/ color, why ?

#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <sys/types.h>
using namespace std;

int main (int argc, char** argv){
    
    /*  init  */ 
    IplImage* src = 0;
    //IplImage* tmpImage = 0; 
    
    if((src = cvLoadImage(argv[1],1)) == 0 ) {
        perror("cvLoadImage");
    }
    IplImage* dst = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, );
    cvConvert(src,dst);

    cvNamedWindow("result", CV_WINDOW_AUTOSIZE);
    cvShowImage("result", dst);
    cvWaitKey(10000);
    cvDestroyWindow("result");
    
    
    
    /* release memory */
    cvReleaseImage(&src);
    cvReleaseImage(&dst);
    //cvReleaseMat(&s);
    //cvReleaseImage(&tmp8UC1);
    
    return 0;
}
