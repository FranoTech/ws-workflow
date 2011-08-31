#include <iostream>
#include <cv.h>
#include <highgui.h>
using namespace std;

#include <sys/types.h>
#include <stdio.h>

int main (int argc, char** argv){
    
    Mat im_rgb  = imread("image.jpg");
    Mat im_gray;
    cvtColor(im_rgb,im_gray,CV_RGB2GRAY);
    
    namedWindow("result", CV_WINDOW_AUTOSIZE);
    imshow("result_image", im_gray);
    waitKey(1000);
    destroyWindow("result");
    
    im_gray.release();
    im_rgb.release();

    return 0;
}
