#include <iostream>
#include <cv.h>
#include <highgui.h>
//#include <opencv.hpp>
using namespace std;
using namespace cv;

int main (int argc, char** argv)
{
    IplImage *img = cvLoadImage(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
    cout<<"img->imageSize = "<<img->imageSize<<endl;
    cout<<"img->width = "<<img->width<<endl;
    cout<<"img->height = "<<img->height<<endl;
    
    CvMat *mat32FC1 = cvCreateMat(img->height, img->width, CV_32FC1);
    cvConvertScale(img, mat32FC1);
    
    CvSize size = cvGetSize(mat32FC1);
    cout<<"mat32FC1->width"<<mat32FC1->width<<endl;
    cout<<"mat32FC1->height"<<mat32FC1->height<<endl;
    
    //copied data
    //Mat newMat(img); 
    
    //create mat and then copy data
    //Mat newMat(img->height, img->width, CV_32FC1);
    //newMat = cvarrToMat(img);
    
    //cout<<"newMat.size() = "<<newMat.size()<<endl; //error!!
    
    //cvSetZero(newMat); // not work!!
    
    //cout<<"newMat->rows = "<<newMat.rows<<endl;
    //cout<<"newMat->cols = "<<newMat.cols<<endl;
    //cout<<"isempty = "<<newMat.empty()<<endl;
    //cout<<"mat data = "<<newMat.data<<endl;

    //newMat.release();
    cvReleaseImage(&img);
    cvReleaseMat(&mat32FC1);
    return 0;
}
