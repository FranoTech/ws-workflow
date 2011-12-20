#include <iostream>
#include "cv.h"
#include "highgui.h"

int main (int argv, char** argc[])
{
    
		IplConvKernel *se1 = cvCreateStructuringElementEx(3, 3, 1, 1, CV_SHAPE_ELLIPSE);
		cvMorphologyEx(input_morph, input_morph, nullptr, se1, CV_MOP_OPEN); // remove noise

		CvMat out_single = cvCreateMat(input_morph->height, input_morph->width, CV_32FC1);
		cvSetZero(out_single);
		tmp8UC1 = cvCreateImage(cvGetSize(input_morph), IPL_DEPTH_8U, 1);
			
		// remove small cells and fill holes.
		cvConvert(input_morph, tmp8UC1);
		cvFindContours(tmp8UC1, storage, &first_con, sizeof(CvContour), CV_RETR_EXTERNAL);
		cur = first_con;
		while (cur != nullptr) {
			double area = fabs(cvContourArea(cur));
			int npts = cur->total;
			CvPoint *p = new CvPoint[npts];
			cvCvtSeqToArray(cur, p);
			if (area < 1500.0) // remove small area
				cvFillPoly(input_morph, &p, &npts, 1, cvScalar(0.0)); // remove from input
			else if (area < 7500.0) {
				cvFillPoly(out_single, &p, &npts, 1, cvScalar(255.0)); // move to single
				cvFillPoly(input_morph, &p, &npts, 1, cvScalar(0.0)); // remove from input
			}else
				cvFillPoly(input_morph, &p, &npts, 1, cvScalar(255.0)); // fill hole
			delete[] p;
			cur = cur->h_next;
		}

		output_morph = cvCreateMat(input_morph->height, input_morph->width, CV_32FC1);
		cvOr(input_morph, out_single, output_morph);
		cvReleaseStructuringElement(&se1);
	//}
