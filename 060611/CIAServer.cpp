//      CIAServer.cpp
//      
// 06.06.2011
// rewrite all again for better things.
// fighto!


//#include "soapH.h"
//#include "imgProcess.nsmap"
#include "soapCIAService.h"
#include "CIA.nsmap"
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <cstring>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>

#include "cv.h"
#include "highgui.h"

using namespace std;

int main()
{
	CIAService server;
	return server.serve();
}


// 
// name: Ipl1ChToMat
// @param char *InputFilename
// @return ns__ImageData &output
// fixed mat's depth = CV_32FC1
// fixed key = 001
int CIAService::Ipl1ChToMat(char *InputFilename, ns__ImageData &output)
{	
	if(InputFilename)
	{
		//load image to Ipl object
		IplImage* src = cvLoadImage(InputFilename,CV_LOAD_IMAGE_GRAYSCALE);
        if (!src)
        { 	
            soap_fault(soap);
            cerr<<"Can not open image file"<<endl;
            soap->fault->faultstring = "Can not open image file";
            return SOAP_FAULT;
        }
		//create mat and convert image data to mat object
        CvMat *mat32FC1 = cvCreateMat(src->height, src->width, CV_32FC1);
        cvConvertScale(src, mat32FC1);
        
        //attached data to shared memory
        
		
	}else{
        cerr<<"File Name required"<<endl;
        soap_fault(soap);
        soap->fault->faultstring = "InputFilename required";
        return SOAP_FAULT;
    } 
	return SOAP_OK;
}
