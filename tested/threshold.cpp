#include <cv.h>
#include <highgui.h>
#include <iostream>


using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    Mat src = imread(argv[1],0);
    threshold(src,src,60.0,255.0,cv::THRESH_BINARY);
	namedWindow("Image"); // define the window
	imshow("Image", src); // show the image
	waitKey(0);
    src.release();
 
    return 0;
}