#include <iostream>
#include <cv.h>
#include <highgui.h>
using namespace std;
using namespace cv;

int main (int argc, char** argv)
{
    IplImage *img = cvLoadImage(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
    CvMat *mat32FC1 = cvCreateMat(img->height, img->width, CV_32FC1);
    cvConvertScale(img, mat32FC1);
    
    cout<<mat32FC1->data.ptr<<endl;
    cvReleaseImage(&img);
    cvReleaseMat(&mat32FC1);
    return 0;
}
