// แตกมาจาก 060111
// แยกฟังก์ชันแล้ว
// 

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
    cerr<<"******Test started at"<<1900+tm->tm_year<<'-'<<1+tm->tm_mon<<'-'<<tm->tm_mday<<' time'<<tm->tm_hour<<':'<<tm->tm_min<<"******"<<endl;
}

void get_time(char *msg) {
    timeval t;
    gettimeofday(&t, NULL);
    cerr<<(int64) (t.tv_sec - start_time.tv_sec) + (t.tv_usec -start_time.tv_usec)/1000000.0<<" "<<msg;
}

int ns__getImage(struct soap *soap, char *name, ns__ImageData &image)
{ 
    init_time();
    cerr<<"imgProcessServer started\n"<<endl;
    if(name)
    { 
        // load image from directory
        FILE *fd = fopen(name, "r");
        if(fd!=NULL){
            fseek(fd,0,SEEK_END); // seek to end of file
            int size = ftell(fd); // get current file pointer
            fseek(fd, 0, SEEK_SET); // seek back to beginning of file

            image.__ptr = (unsigned char*)soap_malloc(soap, size);
            int i, c;
            for (i = 0; i < size; i++)
            { 
                if ((c = fgetc(fd)) == EOF)
                break;
                image.__ptr[i] = c;
            }
            image.__size = i;
        } else {
            soap_fault(soap);
            cerr<<"Can not read file"<<endl;
            soap->fault->faultstring = "Cannot read file";
            return SOAP_FAULT;
        }
        get_time("Readed out to taverna client\n");
    }
    else
    { 
    cerr<<"Name require"<<endl;
    soap_fault(soap);
    soap->fault->faultstring = "Name required";
    return SOAP_FAULT;
    }
    return SOAP_OK;
}


int ns__1ChIplToMat(struct soap *soap, char *InputFilename, char *filename, int depth, char *&OutputFilename)
{ 
    init_time();
    cerr<<"imgProcessServer started\n"<<endl;
    if(InputFilename)
    { 
        // load image from directory
        IplImage* img = cvLoadImage(InputFilename,1);
        if (!img)
        { 	
            soap_fault(soap);
            cerr<<"Can not open file"<<endl;
            soap->fault->faultstring = "Cannot open file";
            return SOAP_FAULT;
        }
        
        
        if(!cvSave(filename,))
        { 	
            soap_fault(soap);
            cerr<<"Can not save to new image"<<endl;
            soap->fault->faultstring = "Cannot save to new image";
            return SOAP_FAULT;
        }
        cvReleaseImage(&img);
        OutputFilename = filename;
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
