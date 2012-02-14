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
                const char *InputImageFilename,
                int loadparam,
                char *&OutputMatFilename)
{
	/* Determine type of the matrix */
	if(loadparam){
	    switch (loadparam){
			case 0:
				Mat src  = imread(InputImageFilename,CV_LOAD_IMAGE_GRAYSCALE);
				break;
			case (loadparam > 0):
				Mat src  = imread(InputImageFilename,CV_LOAD_IMAGE_COLOR);
				break;
			case (loadparam < 0):
				Mat src  = imread(InputImageFilename,CV_LOAD_IMAGE_UNCHANGED);
				break;
			default
				Mat src  = imread(InputImageFilename,CV_LOAD_IMAGE_COLOR);
	    }
	    
	    if( !src ) {
			soap_fault(soap);
			cerr << "error :: can not load image" << endl;
			soap->fault->faultstring = "error :: can not load image";
			return SOAP_FAULT;
		}
		
    } else {
		soap_fault(soap);
		cerr << "loadparam error" << endl;
		soap->fault->faultstring = "loadparam error";
		return SOAP_FAULT;
	}
	
	/* generate output file name */
	*&OutputMatFilename = (char*)soap_malloc(soap, 60);
    time_t now = time(0);
    strftime(OutputMatFilename, sizeof(OutputMatFilename)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_load_mat", localtime(&now));
	
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
                        const char *InputMatFilename, 
                        double threshold, 
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
    threshold(src, dst, threshold, maxValue, CV_THRESH_BINARY);
    
    writeToBin (OutputFilename, dst);


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

void writeToBin (char *&OutputFilename, Mat& M)
{
	*&OutputFilename = (char*)soap_malloc(soap, 60);
    time_t now = time(0);
    strftime(OutputMatFilename, sizeof(OutputMatFilename)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_bi_threshold", localtime(&now));

		/* save to bin */
    if(!saveMat(OutputMatFilename, src))
    {
        soap_fault(soap);
        cerr << "error:: save mat to binary file" << endl;
		soap->fault->faultstring = "error:: save mat to binary file";
        return SOAP_FAULT;
    }
}
