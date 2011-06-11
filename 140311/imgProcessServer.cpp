#include "soapH.h"
#include "imgProcess.nsmap"
#include <iostream>
#include "cv.h"
#include "highgui.h"
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <time.h>
#include <string.h>
#include <cstring>

//init variable
#define BASE_DIR "/home/lluu/dir/"
#define int64 long long
using namespace std;
static timeval start_time;


//function
void init_time();
void get_time(char);
//void get_Filename(char*&); 


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

void init_time() {
    gettimeofday(&start_time, NULL);
    time_t init = time(0);
    tm* tm = localtime(&init);
    cerr<<"******Start Time :"<<1900+tm->tm_year<<'-'<<1+tm->tm_mon<<'-'<<tm->tm_mday<<' time'<<tm->tm_hour<<':'<<tm->tm_min<<"******"<<endl;
}

void get_time(char *msg) {
    timeval t;
    gettimeofday(&t, NULL);
    cerr<<(int64) (t.tv_sec - start_time.tv_sec) + (t.tv_usec -start_time.tv_usec)/1000000.0<<" "<<msg;
}



int ns__LoadToIpl8U1Ch(struct soap *soap, char *InputFilename) // can't change image solution
{ 
    init_time();
    cerr<<"imgProcessServer started\n"<<endl;
    if(InputFilename)
    { 
        int shmid;
        key_t key = 5678;
        char *addr;
        
        // load image from directory
        IplImage* src = cvLoadImage(InputFilename,CV_LOAD_IMAGE_GRAYSCALE);
        if (!src)
        { 	
            soap_fault(soap);
            cerr<<"Can not open image file"<<endl;
            soap->fault->faultstring = "Cannot open image file";
            return SOAP_FAULT;
        }
        
        IplImage *dst = cvCreateImageHeader(cvSize(src->width, src->height), IPL_DEPTH_8U, 3);
        
        if ((shmid = shmget(key, dst->imageSize, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
        }
        
        /* Attach the segment to our data space */
        if ((addr = (char *) shmat(shmid, NULL, 0)) == (char *) -1) {
            perror("shmat");
            exit(1);
        }
        
        tmpImage->imageData = addr;
        cvCopy(src,dst);
    
        CvMat *output1Ch = cvCreateMat(src->height, src->width, CV_32FC1);
        cvConvertScale(src, output1Ch);
        cvSave(filename,output1Ch);
    
    }
    else
    { 
        cerr<<"File Name require"<<endl;
        soap_fault(soap);
        soap->fault->faultstring = "Name required";
        return SOAP_FAULT;
    }
    return SOAP_OK;
}

int ns__Ipl1ChToMat(struct soap *soap, char *InputFilename, 
                    char *filename, char *&OutputFilename) // can't change image solution
{ 
    init_time();
    cerr<<"imgProcessServer started\n"<<endl;
    if(InputFilename)
    { 
        // load image from directory
        IplImage* src = cvLoadImage(InputFilename,CV_LOAD_IMAGE_GRAYSCALE);
        if (!src)
        { 	
            soap_fault(soap);
            cerr<<"Can not open image file"<<endl;
            soap->fault->faultstring = "Cannot open image file";
            return SOAP_FAULT;
        }
    
        CvMat *output1Ch = cvCreateMat(src->height, src->width, CV_32FC1);
        cvConvertScale(src, output1Ch);
        cvSave(filename,output1Ch);
    
        if(!filename)
        { 	
            soap_fault(soap);
            cerr<<"Can not save to mat"<<endl;
            soap->fault->faultstring = "Cannot save to mat";
            return SOAP_FAULT;
        }
        cvReleaseImage(&src);
        cvReleaseMat(&output1Ch);

        OutputFilename = new char[strlen(filename)+1];
        memcpy(OutputFilename,filename,strlen(filename)+1);
    }
    else
    { 
        cerr<<"File Name require"<<endl;
        soap_fault(soap);
        soap->fault->faultstring = "Name required";
        return SOAP_FAULT;
    }
    return SOAP_OK;
}
