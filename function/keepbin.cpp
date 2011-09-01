#include <iostream>
//#include <cv.hpp>
#include <cv.h>
#include <highgui.h>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main (int argc, char** argv){
    
    Mat im_rgb  = imread(argv[1],1);
    Mat im_gray;
    cvtColor( im_rgb, im_gray, CV_RGB2GRAY );
    
    namedWindow("result", CV_WINDOW_AUTOSIZE);
    imshow("result", im_gray);
    waitKey(0);
    //destroyWindow("result");
    
    im_gray.release();
    im_rgb.release();

    return 0;
}
