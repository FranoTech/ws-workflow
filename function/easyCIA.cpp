
#include <iostream>
#include <fstream>
#include <cv.h>
//#include <highgui.h>
#include <ml.h>
using namespace std;
using namespace cv;

void ByteArrayToANN(char *annfile, CvANN_MLP* ann);

int main (int argc, char** argv){
    
    CvANN_MLP* neuron = NULL ;
    IplImage *img = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);
    CvMat *input3Ch = cvCreateMat(img->height, img->width, CV_32FC3);
    CvMat *output1Ch = cvCreateMat(img->height, img->width, CV_32FC1);
    CvMat *morph = cvCreateMat(img->height, img->width, CV_32FC1);

    // train ANN
    cvConvertScale(img, input3Ch);
    
    if (neuron == NULL )
		neuron = new CvANN_MLP();
	else
		neuron->clear();
    ByteArrayToANN("cia.tmp", neuron);
    
    CvMat input_nn = cvMat(input3Ch->height*input3Ch->width, 3, CV_32FC1, input3Ch->data.fl);
    CvMat output_nn = cvMat(output1Ch->height*output1Ch->width, 1, CV_32FC1, output1Ch->data.fl);

    neuron->predict(&input_nn, &output_nn);

    //do threshold
    cvThreshold(output1Ch, morph, -0.5, 255.0, CV_THRESH_BINARY);
    
    // morph open
    IplConvKernel *se1 = cvCreateStructuringElementEx(3, 3, 1, 1, CV_SHAPE_ELLIPSE);
    cvMorphologyEx(morph, morph, NULL, se1, CV_MOP_OPEN); // remove noise


    CvMat *cell = cvCreateMat(morph->height, morph->width, CV_32FC1);
    cvSetZero(cell);
    IplImage *tmp8UC1 = cvCreateImage(cvGetSize(morph), IPL_DEPTH_8U, 1);
    
    // remove small cells and fill holes.
    CvMemStorage *storage = cvCreateMemStorage();
	CvSeq *first_con = NULL;
	CvSeq *cur = NULL;
    
    cvConvert(morph, tmp8UC1);
    cvFindContours(tmp8UC1, storage, &first_con, sizeof(CvContour), CV_RETR_EXTERNAL);
    cur = first_con;
    while (cur != NULL) {
        double area = fabs(cvContourArea(cur));
        int npts = cur->total;
        CvPoint *p = new CvPoint[npts];
        cvCvtSeqToArray(cur, p);
        if (area < 1500.0) // remove small area
            cvFillPoly(morph, &p, &npts, 1, cvScalar(0.0)); // remove from input
        else if (area < 7500.0) {
            cvFillPoly(cell, &p, &npts, 1, cvScalar(255.0)); // move to single
            cvFillPoly(morph, &p, &npts, 1, cvScalar(0.0)); // remove from input
        }else
            cvFillPoly(morph, &p, &npts, 1, cvScalar(255.0)); // fill hole
        delete[] p;
        cur = cur->h_next;
    }

    CvMat *afterOr = cvCreateMat(morph->height, morph->width, CV_32FC1);
    cvOr(morph, cell, afterOr);
    cvReleaseStructuringElement(&se1);
    
    
    //## Scanning Cells ##//
	int ncell = 0, prev_ncontour = 0, same_count = 0, ncontour = 1;
    while(ncontour != 0){
        cvConvert(morph, tmp8UC1);
        cvClearMemStorage(storage);
        int ncontour = cvFindContours(tmp8UC1, storage, &first_con, sizeof(CvContour), CV_RETR_EXTERNAL);
        if (ncontour == 0)
            break; // finish extract cell
        if (ncontour == prev_ncontour) {
            cvErode(morph, morph);
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
                cvFillPoly(cell, &p, &npts, 1, cvScalar(255.0)); // move to single
                cvFillPoly(morph, &p, &npts, 1, cvScalar(0.0)); // remove from input
                delete[] p;
                ncell++;
            }
            cur = cur->h_next;
        }
    }
    
    /* ### separate cells ### */
    cvConvert(cell, tmp8UC1);
    cvClearMemStorage(storage);
    cvFindContours(tmp8UC1, storage, &first_con, sizeof(CvContour), CV_RETR_EXTERNAL);
    int count = 1;
    cur = first_con;
    while (cur != NULL) {
        int npts = cur->total;
        CvPoint *p = new CvPoint[npts];
        cvCvtSeqToArray(cur, p);
        cvFillPoly(cell, &p, &npts, 1, cvScalar((count++%254)+1)); // fill label, must be 1-255
        delete[] p;
        cur = cur->h_next;
    }

    cvConvertScale(afterOr, tmp8UC1);
    
    CvMat *inwater = cvCreateMat(cell->height, cell->width, CV_8UC3);
    CvMat outwater = cvMat(cell->height, cell->width, CV_32SC1, cell->data.fl);

    cvMerge(tmp8UC1, tmp8UC1, tmp8UC1, NULL, inwater);

    cvWatershed(inwater, &outwater);
    cvErode(cell, cell, NULL, 2);
    cvConvertScale(afterOr, tmp8UC1);
    cvSub(afterOr, cell, afterOr, tmp8UC1);
    
    

    cvReleaseMat(&inwater);

    /* ### prepare result ### */
    
    cvConvertScale(afterOr, tmp8UC1);
    cvClearMemStorage(storage);
    cvFindContours(tmp8UC1, storage, &first_con, sizeof(CvContour), CV_RETR_EXTERNAL);
    

    IplImage *tmpImage = cvCreateImage(cvSize(tmp8UC1->width, tmp8UC1->height), IPL_DEPTH_8U, 3);
    cvSet(tmpImage, CV_RGB(0,0,255)); // Background, blue

    cvSetZero(tmp8UC1);
    CvScalar pixel;
    cur = first_con;
    ncell = 0; // total cells
    while (cur != NULL) {
        if ((cur->total > 2) && (fabs(cvContourArea(cur)) > 1500.0)) { // remove small area
            int npts = cur->total;
            CvPoint *p = new CvPoint[npts];
            cvCvtSeqToArray(cur, p);
            cvFillPoly(tmp8UC1, &p, &npts, 1, cvScalar(255)); // set mask
            pixel = cvAvg(output1Ch, tmp8UC1);
            cvFillPoly(tmp8UC1, &p, &npts, 1, cvScalar(0)); // clear mask
            if (pixel.val[0] > 0.5) { // Negative, green
                if (tmpImage != NULL)
                    cvFillPoly(tmpImage, &p, &npts, 1, CV_RGB(0,255,0));
                    
            } else if (pixel.val[0] > -0.5) { // Positive, red
                if (tmpImage != NULL)
                    cvFillPoly(tmpImage, &p, &npts, 1, CV_RGB(255,0,0));
            }
            delete[] p;
        }
        cur = cur->h_next;
    }
    
    cvSaveImage("result.jpg", tmpImage);

    cvReleaseMat(&inwater);
    //cvReleaseMat(outwater);
	if (tmp8UC1 != NULL) cvReleaseImage(&tmp8UC1);
	if (morph != NULL) cvReleaseMat(&morph);
	if (cell != NULL) cvReleaseMat(&cell);
	if (afterOr != NULL) cvReleaseMat(&afterOr);
	//if (input3Ch != NULL) cvReleaseMat(&input3Ch);
	if (output1Ch != NULL) cvReleaseMat(&output1Ch);
	if (tmpImage != NULL) cvReleaseImageHeader(&tmpImage);
	if (storage != NULL) cvReleaseMemStorage(&storage);
    
        
    return 0;
}


void ByteArrayToANN(char *annfile, CvANN_MLP* ann)
{
    char *buffer;
    long size;
	ifstream file (annfile, ios::in|ios::binary|ios::ate);
    size = file.tellg();
    file.seekg (0, ios::beg);
    buffer = new char [size];
    file.read (buffer, size);
    file.close();
	CvFileStorage *cvfs = cvOpenFileStorage(annfile, NULL, CV_STORAGE_READ);

	if (cvfs != NULL) {
		ann->read(cvfs, cvGetFileNodeByName(cvfs, NULL, "CIA_Neuron"));
		cvReleaseFileStorage(&cvfs);
	}
}
