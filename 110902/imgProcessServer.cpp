//trying to transpost code to c++
//gsoap
#include "soapH.h"
#include "imgProcess.nsmap"
//opencv
#include "cv.h"
#include "highgui.h"
//STL
#include <sstream>
#include <iostream>
#include <string.h>
#include <cstring>
#include <fstream>
//system
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


//init variable
#define BASE_DIR "/home/lluu/dir/"
#define LOGNAME_SIZE 60
#define int64 long long

using namespace std;
using namespace cv;
static timeval start_time, now;

//global function
//void writeToBin (char *&OutputFilename, Mat& M);
int saveMat( const char *filename, const Mat& M);
int readMat( const char *filename, Mat& M);

int main(int argc, char **argv)
{ 
    struct soap soap;
    soap_init(&soap);
    if (argc < 2)		// no args: assume this is a CGI application
    { 
        soap_serve(&soap);	// serve request
        soap_destroy(&soap);// cleanup class instances
        soap_end(&soap);	// cleanup
    }
    return 0;
}

/* Load image data to Mat, save to bin */
int ns__LoadMat (struct soap *soap,
                char *InputImageFilename,
                int loadparam,
                char *&OutputMatFilename)
{
    Mat src;
    
	/* Determine type of the matrix */
	if(InputImageFilename){
        
        switch (loadparam){
			case 0:
                src  = imread(InputImageFilename,CV_LOAD_IMAGE_GRAYSCALE);
				break;
			case 1:
                src  = imread(InputImageFilename,CV_LOAD_IMAGE_COLOR);
				break;
			case -1:
				src  = imread(InputImageFilename,CV_LOAD_IMAGE_UNCHANGED);
				break;
			default :
				src  = imread(InputImageFilename,CV_LOAD_IMAGE_COLOR);
	    }
	    
	    if(src.empty()) {
			soap_fault(soap);
			cerr << "error :: can not load image" << endl;
			soap->fault->faultstring = "error :: can not load image";
			return SOAP_FAULT;
		}
		
    } else {
		soap_fault(soap);
		cerr << "param error" << endl;
		soap->fault->faultstring = " param error";
		return SOAP_FAULT;
	}
	
	/* generate output file name */
	*&OutputMatFilename = (char*)soap_malloc(soap, 60);
    time_t now = time(0);
    strftime(OutputMatFilename, sizeof(OutputMatFilename)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_LoadMat", localtime(&now));
	
	/* save to bin */
    if(!saveMat(OutputMatFilename, src))
    {
        soap_fault(soap);
        cerr << "error:: save mat to binary file" << endl;
		soap->fault->faultstring = "error:: save mat to binary file";
        return SOAP_FAULT;
    }
    
    return SOAP_OK;
}

int ns__BinaryThreshold(struct soap *soap, 
                        char *InputMatFilename, 
                        double thresholdValue, 
                        double maxValue,
                        char *&OutputMatFilename)
{ 
	/* read from bin */
	Mat src;
	if(!readMat(InputMatFilename, src))
	    {
	        soap_fault(soap);
	        cerr << "error :: can not read bin file" << endl;
			soap->fault->faultstring = "error :: can not read bin file";
	        return SOAP_FAULT;
	    }
	
    Mat dst(src.rows, src.cols, src.depth());
    threshold(src, dst, thresholdValue, maxValue, CV_THRESH_BINARY);
    
    /* generate output file name */
	*&OutputMatFilename = (char*)soap_malloc(soap, 60);
    time_t now = time(0);
    strftime(OutputMatFilename, sizeof(OutputMatFilename)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_BinaryThreshold", localtime(&now));
	
	/* save to bin */
    if(!saveMat(OutputMatFilename, src))
    {
        soap_fault(soap);
        cerr << "error:: save mat to binary file" << endl;
		soap->fault->faultstring = "error:: save mat to binary file";
        return SOAP_FAULT;
    }
    return SOAP_OK;
}

int ns__MorphOpen(  struct soap *soap, char *InputMatFilename, char *&OutputMatFilename)
{ 
   
    /* read from bin */
    Mat src;
    if(!readMat(InputMatFilename, src))
        {
            soap_fault(soap);
            cerr << "error :: can not read bin file" << endl;
            soap->fault->faultstring = "error :: can not read bin file";
            return SOAP_FAULT;
        }
    
    Mat dst(src.rows, src.cols, src.depth());
    Mat se; 
    Size seSize(3, 3); 
    Point seAnc(1, 1);
    
    se = getStructuringElement(MORPH_ELLIPSE, seSize, seAnc);
    morphologyEx(src, dst, MORPH_OPEN, se, seAnc);
    
    if(src.empty()) {
			soap_fault(soap);
			cerr << "error :: morphologyEx" << endl;
			soap->fault->faultstring = "error :: morphologyEx";
			return SOAP_FAULT;
    }
    
    /* generate output file name */
    *&OutputMatFilename = (char*)soap_malloc(soap, 60);
    time_t now = time(0);
    strftime(OutputMatFilename, sizeof(OutputMatFilename)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_MorphOpen", localtime(&now));
    
    /* save to bin */
    if(!saveMat(OutputMatFilename, src))
    {
        soap_fault(soap);
        cerr << "error:: save mat to binary file" << endl;
        soap->fault->faultstring = "error:: save mat to binary file";
        return SOAP_FAULT;
    }
    return SOAP_OK;
    
}

int ns__MatToJPG (struct soap *soap, char *InputMatFilename, char *&OutputMatFilename)
{
    Mat src;
    if(!readMat(InputMatFilename, src))
    {
        soap_fault(soap);
        cerr << "error :: can not read bin file" << endl;
        soap->fault->faultstring = "error :: can not read bin file";
        return SOAP_FAULT;
    }
    
    /* generate output file name */
    *&OutputMatFilename = (char*)soap_malloc(soap, 60);
    time_t now = time(0);
    strftime(OutputMatFilename, sizeof(OutputMatFilename)*60, "/home/lluu/dir/%Y%m%d_%H%M%S.jpg", localtime(&now));
    
    if(!imwrite(OutputMatFilename, src))
    {
        soap_fault(soap);
        cerr << "error :: can not save to jpg" << endl;
        soap->fault->faultstring = "error :: can not save to jpg";
        return SOAP_FAULT;
    }
    
    return SOAP_OK;
}

int ns__removeSmallCell (struct soap *soap, char *InputMatFilename, char *&OutputMatFilename)
{
    Mat src;
    if(!readMat(InputMatFilename, src))
    {
        soap_fault(soap);
        cerr << "error :: can not read bin file" << endl;
        soap->fault->faultstring = "error :: can not read bin file";
        return SOAP_FAULT;
    }
    
    //Mat outSingle ;
    //outSingle = Mat::zeros(src.rows, src.cols, CV_32F);
	
	CvMat *out_single = nullptr;
   	IplImage tmp8UC1 = src;
   	CvMat *out_single = nullptr;
	CvMemStorage *storage = cvCreateMemStorage();
	CvSeq *first_con = nullptr;
	CvSeq *cur = nullptr;
	
    out_single = cvCreateMat(input_morph->height, input_morph->width, CV_32FC1);
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
    
    //vector<vector<Point> > contours;
    //findContours(src, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0,0));
    //for(int i = 0; i< contours.size(); i++)
    //{
		//double area = contourArea(contours);
		
		//cerr << area << endl;
		//if(area < lowerBound)
		//{
			//fillPoly(src)
		//}
		
	//}
}



int ns__removeSmallCell (struct soap *soap, char *InputMatFilename, char *&OutputMatFilename)
{
    Mat src;
    if(!readMat(InputMatFilename, src))
    {
        soap_fault(soap);
        cerr << "error :: can not read bin file" << endl;
        soap->fault->faultstring = "error :: can not read bin file";
        return SOAP_FAULT;
    }
    
    Mat outSingle ;
    outSingle = Mat::zeros(src.rows, src.cols, CV_32F);
	
	//CvMat *out_single = nullptr;
   	//IplImage tmp8UC1 = src;
   	//CvMat *out_single = nullptr;
	//CvMemStorage *storage = cvCreateMemStorage();
	//CvSeq *first_con = nullptr;
	//CvSeq *cur = nullptr;
	
	//out_single = cvCreateMat(tmp8UC1->height, tmp8UC1->width, CV_32FC1);
	//cvSetZero(out_single);
	
	//cvFindContours(tmp8UC1, storage, &first_con, sizeof(CvContour), CV_RETR_EXTERNAL);
	//cur = first_con;
	//while (cur != nullptr) {
		//double area = fabs(cvContourArea(cur));
		//int npts = cur->total;
		//CvPoint *p = new CvPoint[npts];
		//cvCvtSeqToArray(cur, p);
		//if (area < 1500.0) // remove small area
			//cvFillPoly(input_morph, &p, &npts, 1, cvScalar(0.0)); // remove from input
		//else if (area < 7500.0) {
			//cvFillPoly(out_single, &p, &npts, 1, cvScalar(255.0)); // move to single
			//cvFillPoly(input_morph, &p, &npts, 1, cvScalar(0.0)); // remove from input
		//}else
			//cvFillPoly(input_morph, &p, &npts, 1, cvScalar(255.0)); // fill hole
		//delete[] p;
		//cur = cur->h_next;
	//}
    
    vector<vector<Point> > contours;
    findContours(src, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0,0));
    for(size_t i = 0; i< contours.size(); i++)
    {
		double area = contourArea(Mat(contours[i]);
		int npts = contours.size();
		vector<Point> p;
		
		cerr << area << endl;
		if(area < lowerBound)
		{
			fillPoly(src)
		}
		
	}
}

/* Save matrix to binary file */
int saveMat( const char *filename, const Mat& M){
    if (M.empty()){
       return 0;
    }
    ofstream out(filename, ios::out|ios::binary);
    if (!out)
       return 0;

    int cols = M.cols;
    int rows = M.rows;
    int chan = M.channels();
    int eSiz = (M.dataend-M.datastart)/(cols*rows*chan);

    /* Write header */
    out.write((char*)&cols,sizeof(cols));
    out.write((char*)&rows,sizeof(rows));
    out.write((char*)&chan,sizeof(chan));
    out.write((char*)&eSiz,sizeof(eSiz));

    /* Write data. */
    if (M.isContinuous()){
       out.write((char *)M.data,cols*rows*chan*eSiz);
    }
    else{
       return 0;
    }
    out.close();
    return 1;
}



/* Read matrix from binary file */
int readMat( const char *filename, Mat& M)
{    
    ifstream in(filename, ios::in|ios::binary);
    if (!in){
       M.data = NULL;
       return 0;
    }
    int cols;
    int rows;
    int chan;
    int eSiz;

    /* Read header */
    in.read((char*)&cols,sizeof(cols));
    in.read((char*)&rows,sizeof(rows));
    in.read((char*)&chan,sizeof(chan));
    in.read((char*)&eSiz,sizeof(eSiz));

    /* Determine type of the matrix */
    int type = 0;
    switch (eSiz){
    case sizeof(char):
         type = CV_8UC(chan);
         break;
    case sizeof(float):
         type = CV_32FC(chan);
         break;
    case sizeof(double):
         type = CV_64FC(chan);
         break;
    }

    /* Alocate Matrix. */
    M = Mat(rows,cols,type,Scalar(1));  

    /* Read data. */
    if (M.isContinuous()){
       in.read((char *)M.data,cols*rows*chan*eSiz);
    }
    else{
       return 0;
    }
    in.close();
    return 1;
} 


