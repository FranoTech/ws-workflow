#include <iostream>
#include <fstream>
#include <cv.h>
#include <highgui.h>
using namespace std;
using namespace cv;

int main (int argc, char** argv){
    
    IplImage *img = cvLoadImage(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    CvMat *output1Ch = cvCreateMat(img->height, img->width, CV_32FC1);
    CvMat *input_morph = cvCreateMat(img->height, img->width, CV_32FC1);
    cvConvertScale(img, output1Ch);
    
    //do threshold
    cvThreshold(output1Ch, input_morph, 127.0, 255.0, CV_THRESH_BINARY);
    
    // morph open
    IplConvKernel *se1 = cvCreateStructuringElementEx(3, 3, 1, 1, CV_SHAPE_ELLIPSE);
    cvMorphologyEx(input_morph, input_morph, NULL, se1, CV_MOP_OPEN); // remove noise

    CvMat *out_single = cvCreateMat(input_morph->height, input_morph->width, CV_32FC1);
    cvSetZero(out_single);
    IplImage *tmp8UC1 = cvCreateImage(cvGetSize(input_morph), IPL_DEPTH_8U, 1);
    
    // remove small cells and fill holes.
    
    CvMemStorage *storage = cvCreateMemStorage();
	CvSeq *first_con = NULL;
	CvSeq *cur = NULL;
    
    cvConvert(input_morph, tmp8UC1);
    cvFindContours(tmp8UC1, storage, &first_con, sizeof(CvContour), CV_RETR_EXTERNAL);
    cur = first_con;
    while (cur != NULL) {
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
    
    Mat tmpmat = cvarrToMat(out_single, true);
    tmpmat.convertTo(tmpmat, CV_8UC1);
    if(!imwrite("c_out_single.jpg", tmpmat))
    {
		cout<<"error writing image"<<endl;
    }
    
    tmpmat = cvarrToMat(input_morph, true);
    tmpmat.convertTo(tmpmat, CV_8UC1);
    if(!imwrite("c_input_morph.jpg", tmpmat))
    {
		cout<<"error writing image"<<endl;
    }
    
    CvMat *output_morph = cvCreateMat(input_morph->height, input_morph->width, CV_32FC1);
    cvOr(input_morph, out_single, output_morph);
    cvReleaseStructuringElement(&se1);
    
    //## Scanning Cells ##//
	int ncell = 0, prev_ncontour = 0, same_count = 0, ncontour = 1;
    while(ncontour != 0){
        cvConvert(input_morph, tmp8UC1);
            cvClearMemStorage(storage);
            int ncontour = cvFindContours(tmp8UC1, storage, &first_con, sizeof(CvContour), CV_RETR_EXTERNAL);
            if (ncontour == 0)
                break; // finish extract cell
            if (ncontour == prev_ncontour) {
                cvErode(input_morph, input_morph);
                same_count++;
            } else
                same_count = 0;
            prev_ncontour = ncontour;
            cur = first_con;
            while (cur != NULL) {
                double area = fabs(cvContourArea(cur));
                if ((area < 3000.0) || (same_count > 10)) {
                    int npts = cur->total;
                    CvPoint *p = new CvPoint[npts];
                    cvCvtSeqToArray(cur, p);
                    cvFillPoly(out_single, &p, &npts, 1, cvScalar(255.0)); // move to single
                    cvFillPoly(input_morph, &p, &npts, 1, cvScalar(0.0)); // remove from input
                    delete[] p;
                    ncell++;
                }
                cur = cur->h_next;
            }
    }
    
    tmpmat = cvarrToMat(out_single, true);
    tmpmat.convertTo(tmpmat, CV_8UC1);
    if(!imwrite("c_out_single_scanningCell.jpg", tmpmat))
    {
		cout<<"error writing image"<<endl;
    }
    
    
    tmpmat = cvarrToMat(input_morph, true);
    tmpmat.convertTo(tmpmat, CV_8UC1);
    if(!imwrite("c_input_morph_scanningCell.jpg", tmpmat))
    {
		cout<<"error writing image"<<endl;
    }
}
