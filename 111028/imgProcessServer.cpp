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
#define FILENAME_SIZE 60
#define int64 long long

//namespace
using namespace std;
using namespace cv;
static timeval start_time, t;

//helper function
int saveMat( const char *filename, const Mat& M);
int readMat( const char *filename, Mat& M);
int getMatType (const char *typeName);
int getColorFlag(int colorflag);


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


/* Load image data to Mat, convert to 32FC1, save to bin */
int ns__loadMat (struct soap *soap,
                char *InputImageFilename,
                int colorflag=0,
                char *types=5,
                char **OutputMatFilename=NULL)
{
    gettimeofday(&start_time, NULL);
    Mat src;
    
	/* Determine type of the matrix */
	if(InputImageFilename){
	    
        src = imread(InputImageFilename,getColorFlag(colorflag));
	    if(src.empty()) {
			soap_fault(soap);
			cerr << "error :: can not load image" << endl;
			soap->fault->faultstring = "error :: can not load image";
			return SOAP_FAULT;
		}
        
        if(src.type()!= getMatType(types))
        {
            src.convertTo(src,getMatType(types));
        }
		
    } else {
		soap_fault(soap);
		cerr << "InputImageFilename error" << endl;
		soap->fault->faultstring = "InputImageFilename error";
		return SOAP_FAULT;
	}
    
	/* generate output file name */
	*OutputMatFilename = (char*)soap_malloc(soap, FILENAME_SIZE);
    time_t now = time(0);
    strftime(*OutputMatFilename, sizeof(OutputMatFilename)*FILENAME_SIZE, "/home/lluu/dir/%Y%m%d_%H%M%S_LoadMat", localtime(&now));
	
	/* save to bin */
    if(!saveMat(*OutputMatFilename, src))
    {
        soap_fault(soap);
        cerr << "error:: save mat to binary file" << endl;
		soap->fault->faultstring = "error:: save mat to binary file";
        return SOAP_FAULT;
    }
    
    gettimeofday(&t, NULL);
    cerr<<(int64) (t.tv_sec - start_time.tv_sec) + (t.tv_usec -start_time.tv_usec)/1000000.0<<" secs ::LoadMat"<<endl;
    
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


int getMatType ( const char *typeName)
{
    if(strcmp("CV_8UC1", typeName) == 0)
        return 0;
    else if(strcmp("CV_8UC2", typeName) == 0)
        return 8;
    else if(strcmp("CV_8UC3", typeName) == 0)
        return 16;
    else if(strcmp("CV_32FC1", typeName) == 0)
        return 5;
    else if(strcmp("CV_32FC2", typeName) == 0)
        return 13;
    else if(strcmp("CV_32FC3", typeName) == 0)
        return 21;
}

int getColorFlag(int colorflag)
{
    switch (colorflag){
			case 0:
                return CV_LOAD_IMAGE_GRAYSCALE);
				break;
			case 1:
                return CV_LOAD_IMAGE_COLOR);
				break;
			case -1:
				return CV_LOAD_IMAGE_UNCHANGED);
				break;
			default :
				return CV_LOAD_IMAGE_COLOR);
	    }
}
        
