#include <iostream>
#include <cv.h>
#include <highgui.h>
using namespace std;

int main (int argc, char** argv){

    IplImage *img = cvLoadImage(argv[1]);
    cout<<"width = "<<img->width<<endl;
    cout<<"heigh = "<<img->height<<endl;
    cout<<"size?? = "<<img->width*img->height<<endl;
    cout<<"Size = "<<img->imageSize<<endl;
    cvReleaseImage(&img);

}
