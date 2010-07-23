#include "cv.h"
#include "highgui.h"
#include <iostream>

using namespace std;

int main ()
{
	IplImage* img = cvLoadImage("img.jpg",1);
	if(!img){
		cout<<"can not load image"<<endl;
	}

	IplImage* gray  = cvCreateImage(cvGetSize(img), img->depth,1);
	cvCvtColor( img, gray, CV_BGR2GRAY );
	
	if(img != 0) {
		cvNamedWindow("Display", CV_WINDOW_AUTOSIZE); // create a window
		cvShowImage("Display", img); // show image in window
		cvWaitKey(0); // wait until user hits a key
		cvDestroyWindow("Display");
	}

	if(gray != 0) {
		cvNamedWindow("Display", CV_WINDOW_AUTOSIZE);
		cvShowImage("Display", gray); // show image in window
		cvWaitKey(0); // wait until user hits a key
		cvDestroyWindow("Display");
	}
    
	char* out = "img2.jpg";
	if(!cvSaveImage(out,gray)) 
		cout<<"Could not save:"<<out<<endl;
	

	return 0;
}


