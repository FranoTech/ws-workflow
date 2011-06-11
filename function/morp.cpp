#include <iostream>
#include "cv.h"
#include "highgui.h"

int main (int argc, char** argv){
        
    IplImage *img = cvLoadImage(argv[1]);
	IplImage *tmpImage = cvCreateImage(cvSize(img->Width, img->Height), IPL_DEPTH_8U, 3);
    tmpImage = cvCopy(img,tmpImage);
	input3Ch = cvCreateMat(img->Height, img->Width, CV_32FC3);
	output1Ch = cvCreateMat(img->Height, img->Width, CV_32FC1);
	////Morphological
	CvMat *input_morph = cvCreateMat(output1Ch->height, output1Ch->width, CV_32FC1);
	//IplImage *tmp8UC1 = nullptr;
	//CvMemStorage *storage = cvCreateMemStorage();
	//CvSeq *first_con = nullptr;
	//CvSeq *cur = nullptr;
	//CvMat *out_single = nullptr;
	//CvMat *output_morph = nullptr;
 
	cvConvertScale(tmpImage, input3Ch);
    cvThreshold(output1Ch, input_morph, -0.5, 255.0, CV_THRESH_BINARY);
    IplConvKernel *se1 = cvCreateStructuringElementEx(3, 3, 1, 1, CV_SHAPE_ELLIPSE);
    cvMorphologyEx(input_morph, input_morph, nullptr, se1, CV_MOP_OPEN); // remove noise

    out_single = cvCreateMat(input_morph->height, input_morph->width, CV_32FC1);
    cvSetZero(out_single);
    tmp8UC1 = cvCreateImage(cvGetSize(input_morph), IPL_DEPTH_8U, 1);
