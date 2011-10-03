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
int getMatType (const Mat& M);

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
int ns__loadMat (struct soap *soap,
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

int ns__binaryThreshold(struct soap *soap, 
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

int ns__morphOpen(  struct soap *soap, char *InputMatFilename, char *&OutputMatFilename)
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

// save mat data to jpg file
// name: MatToJPG 
// @param char *InputMatFilename
// @return char *&OutputMatFilename


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


// 
// name: findContoursAndFillPoly
// @param	
//			-lowerbound พื้นที่น้อยสุดที่ใช้ fillPoly น้อยกว่านี้จะถูก remove
//			-InputMatFilename
// @return	
// 			-ns_FindContours out.smallerArea
//			-ns_FindContours out.biggerArea



int ns__findContoursAndFillpoly (struct soap *soap, 
						char *InputMatFilename,
						int lowerBound,
						ns_FindContours &out )
{
    Mat src;
    if(!readMat(InputMatFilename, src))
    {
        soap_fault(soap);
        cerr << "error :: can not read bin file" << endl;
        soap->fault->faultstring = "error :: can not read bin file";
        return SOAP_FAULT;
    }
    
    Mat outSingle = Mat::zeros(src.rows, src.cols, CV_32FC1);
	vector<vector<Point> > contours;
    findContours(	src, contours, CV_RETR_EXTERNAL, 
					CV_CHAIN_APPROX_SIMPLE, Point(0,0));
    for(size_t i = 0; i< contours.size(); i++)
    {
		const Point* p = &contours[i][0];
        int n = (int)contours[i].size();
		double area = contourArea(Mat(contours[i]));
		
		if(area < lowerBound) //lower bound
		{
			fillPoly( src, &p, &n, 1, Scalar(0, 0, 0)); // remove from src (put white area instead the old one)
			fillPoly(outSingle, &p, &n, 1, Scalar(255, 255, 255)); // keep small area here with black color
		}
		
	}

	contours.clear();

    /* generate output file name */
    out.smallerArea = (char*)soap_malloc(soap, 60);
    out.biggerArea = (char*)soap_malloc(soap, 60);

    time_t now = time(0);
    strftime(out.smallerArea, sizeof(out.smallerArea)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_smallerArea", localtime(&now));
    strftime(out.biggerArea, sizeof(out.biggerArea)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_biggerArea", localtime(&now));
    
    /* save to bin */
    if(!saveMat(out.smallerArea, outSingle))
    {
        soap_fault(soap);
        cerr << "error:: save mat to binary file" << endl;
        soap->fault->faultstring = "error:: save mat to binary file";
        return SOAP_FAULT;
    }
    
    if(!saveMat(out.biggerArea, src))
    {
        soap_fault(soap);
        cerr << "error:: save mat to binary file" << endl;
        soap->fault->faultstring = "error:: save mat to binary file";
        return SOAP_FAULT;
    }
    
    
    return SOAP_OK;
}

// 
// name: ns__erode
// @param
//		- src Source image.
//		- element Structuring element used for erosion.
//		- iteration  Number of times erosion is applied.
// @return
// 		- OutputMatFilename


int ns__erode(  struct soap *soap, char *src,
				char *element,
				int iteration=1,
				char *&OutputMatFilename)
{ 
	Mat src;
    if(!readMat(Input1, src))
    {
        soap_fault(soap);
        cerr << "error :: can not read bin file" << endl;
        soap->fault->faultstring = "error :: can not read bin file";
        return SOAP_FAULT;
    }
    
    Mat dst;
    Mat element;
    
    if(!readMat(Input2, src))
    {
        erode(src, dst, Mat(), iteration);
    } else {
        erode(src, dst, element, iteration);
    }
    
    /* generate output file name */
    *&OutputMatFilename = (char*)soap_malloc(soap, 60);
    time_t now = time(0);
    strftime(OutputMatFilename, sizeof(OutputMatFilename)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_erode", localtime(&now));
    
    if(!imwrite(OutputMatFilename, dst))
    {
        soap_fault(soap);
        cerr << "error :: can not save to jpg" << endl;
        soap->fault->faultstring = "error :: can not save to jpg";
        return SOAP_FAULT;
    }
    
    return SOAP_OK;
}




// 
// name: ns__dilate
// @param
//		- src Source image.
//		- element Structuring element used for dilation.
//		- iteration  Number of times erosion is applied.
// @return
// 		- OutputMatFilename


int ns__dilate(  struct soap *soap, char *src,
				char *element,
				int iteration=1,
				char *&OutputMatFilename)
{ 
	Mat src;
    if(!readMat(Input1, src))
    {
        soap_fault(soap);
        cerr << "error :: can not read bin file" << endl;
        soap->fault->faultstring = "error :: can not read bin file";
        return SOAP_FAULT;
    }
    
    Mat element;
    if(!readMat(Input2, src))
    {
        element.release();
        dilate(src, dst, Mat(), iteration);
    } else {
        dilate(src, dst, element, iteration);
    }
    
    /* generate output file name */
    *&OutputMatFilename = (char*)soap_malloc(soap, 60);
    time_t now = time(0);
    strftime(OutputMatFilename, sizeof(OutputMatFilename)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_dilate", localtime(&now));
    
    if(!imwrite(OutputMatFilename, dst))
    {
        soap_fault(soap);
        cerr << "error :: can not save to jpg" << endl;
        soap->fault->faultstring = "error :: can not save to jpg";
        return SOAP_FAULT;
    }
    
    return SOAP_OK;
}


/* helper function */
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

int getMatType ( const Mat& M)
{
	int type = 0;
    int chan = M.channels();
    int eSiz = (M.dataend-M.datastart)/(cols*rows*chan);
    
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
    
    return type;
}
