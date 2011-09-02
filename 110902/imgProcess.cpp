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
int saveMat( const string& filename, const Mat& M);
int readMat( const string& filename, Mat& M);

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

int ns__LoadMat (struct soap *soap,
                string InputImageFilename,
                int loadparam,
                string& OutputMatFilename)
{
    switch (loadparam){
    case 0:
        Mat src  = imread(InputImageFilename.c_str(),CV_LOAD_IMAGE_GRAYSCALE);
        break;
    case (loadparam > 0):
        Mat src  = imread(InputImageFilename.c_str(),CV_LOAD_IMAGE_COLOR);
        break;
    case loadparam < 0:
        Mat src  = imread(InputImageFilename.c_str(),CV_LOAD_IMAGE_UNCHANGED);
        break;
    default
        Mat src  = imread(InputImageFilename.c_str(),CV_LOAD_IMAGE_COLOR);
        break;
    }
    
    if(!saveMat(OutputMatFilename, src))
    {
        soap_fault(soap);
        Exception& e
        const char* err_msg = e.what();
        cerr << "exception caught: " << err_msg << endl;
        soap->fault->faultstring = e.what();
        return SOAP_FAULT;
    }
    
    return SOAP_OK;
}

int ns__BinaryThreshold(struct soap *soap, 
                        string InputImageFilename, 
                        double threshold, 
                        double maxValue, 
                        char *&OutputMatFilename)
{ 
    
    
}




// Save matrix to binary file
int saveMat( const string& filename, const Mat& M){
    if (M.empty()){
       return 0;
    }
    ofstream out(filename.c_str(), ios::out|ios::binary);
    if (!out)
       return 0;

    int cols = M.cols;
    int rows = M.rows;
    int chan = M.channels();
    int eSiz = (M.dataend-M.datastart)/(cols*rows*chan);

    // Write header
    out.write((char*)&cols,sizeof(cols));
    out.write((char*)&rows,sizeof(rows));
    out.write((char*)&chan,sizeof(chan));
    out.write((char*)&eSiz,sizeof(eSiz));

    // Write data.
    if (M.isContinuous()){
       out.write((char *)M.data,cols*rows*chan*eSiz);
    }
    else{
       return 0;
    }
    out.close();
    return 1;
}



// Read matrix from binary file
int readMat( const string& filename, Mat& M)
{    
    ifstream in(filename.c_str(), ios::in|ios::binary);
    if (!in){
       M.data = NULL;
       return 0;
    }
    int cols;
    int rows;
    int chan;
    int eSiz;

    // Read header
    in.read((char*)&cols,sizeof(cols));
    in.read((char*)&rows,sizeof(rows));
    in.read((char*)&chan,sizeof(chan));
    in.read((char*)&eSiz,sizeof(eSiz));

    // Determine type of the matrix 
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

    // Alocate Matrix.
    M = Mat(rows,cols,type,Scalar(1));  

    // Read data.
    if (M.isContinuous()){
       in.read((char *)M.data,cols*rows*chan*eSiz);
    }
    else{
       return 0;
    }
    in.close();
    return 1;
} 
