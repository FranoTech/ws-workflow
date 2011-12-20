#include <iostream>
#include <fstream>
#include <cv.h>
#include <highgui.h>
#include <ml.h>
using namespace std;
using namespace cv;

void ByteArrayToANN(char *annfile, CvANN_MLP* ann);

int main (int argc, char** argv){
    
    CvANN_MLP* neuron = NULL ;
    IplImage *img = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);
    CvMat *input3Ch = cvCreateMat(img->height, img->width, CV_32FC3);
    CvMat *output1Ch = cvCreateMat(img->height, img->width, CV_32FC1);
    CvMat *input_morph = cvCreateMat(img->height, img->width, CV_32FC1);
    //cvConvertScale(img, output1Ch);
    
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
    cvThreshold(output1Ch, input_morph, -0.5, 255.0, CV_THRESH_BINARY);
    
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
        //~ cout<<area<<" ";
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
    
    /* ### separate cells ### */
    cvConvert(out_single, tmp8UC1);
    cvClearMemStorage(storage);
    cvFindContours(tmp8UC1, storage, &first_con, sizeof(CvContour), CV_RETR_EXTERNAL);
    int count = 1;
    cur = first_con;
    while (cur != NULL) {
        int npts = cur->total;
        CvPoint *p = new CvPoint[npts];
        cvCvtSeqToArray(cur, p);
        cvFillPoly(out_single, &p, &npts, 1, cvScalar((count++%254)+1)); // fill label, must be 1-255
        delete[] p;
        cur = cur->h_next;
    }

    cvConvertScale(output_morph, tmp8UC1);
    
    CvMat *inwater = cvCreateMat(out_single->height, out_single->width, CV_8UC3);
    CvMat outwater = cvMat(out_single->height, out_single->width, CV_32SC1, out_single->data.fl);

    cvMerge(tmp8UC1, tmp8UC1, tmp8UC1, NULL, inwater);

    cvWatershed(inwater, &outwater);
    cvErode(out_single, out_single, NULL, 2);
    cvConvertScale(output_morph, tmp8UC1);
    cvSub(output_morph, out_single, output_morph, tmp8UC1);

    cvReleaseMat(&inwater);

    /* ### prepare result ### */
    
    cvConvertScale(output_morph, tmp8UC1);
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
	if (input_morph != NULL) cvReleaseMat(&input_morph);
	if (out_single != NULL) cvReleaseMat(&out_single);
	if (output_morph != NULL) cvReleaseMat(&output_morph);
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
