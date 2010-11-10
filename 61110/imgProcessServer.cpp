#include "soapH.h"
#include "imgProcess.nsmap"
#include "cv.h"
#include "highgui.h"
#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;
#define BASE_DIR "/home/lluu/dir"
//#define MAX_FILE_SIZE (10000)	// Max. file size

int main(int argc, char **argv)
{    
    struct soap soap;
    soap_init(&soap);
    if (argc < 2)		    // no args: assume this is a CGI application
    {    
        soap_serve(&soap);	// serve request
        soap_destroy(&soap);// cleanup class instances
        soap_end(&soap);	// cleanup
     }
    return 0;
}

int ns__getImage(struct soap *soap, char *name, ns__base64Binary &image)
{ 
    if (name)
    { 
        //find execution time
	    timeval tm;
	    gettimeofday(&tm, NULL);
	
	    double t1=tm.tv_sec+(tim.tv_usec/1000000.0);
        cerr<<t1<<"  start time"<<endl;
        //load image to ipl data
        IplImage* img = cvLoadImage(name,1);
        if (!img)
        { 	
            soap_fault(soap);
      	    cerr<<"Can not open file"<<endl;
      	    soap->fault->faultstring = "Cannot open file";
      	    return SOAP_FAULT;
        }

    
    double t2=tm.tv_sec+(tim.tv_usec/1000000.0);
	cerr<<t2-t1<<" loaded img"<<endl;
	IplImage* gray  = cvCreateImage(cvGetSize(img), img->depth,1);
	cvCvtColor( img,gray,CV_BGR2GRAY ); //convert to gray

    //// char *dest = "img3.jpg";
    //// string s = string(BASE_DIR);
    //// s+="/img3.jpg";
    
	ostringstream sout;

	sout<<BASE_DIR<<"/img4.jpg";
	if(!cvSaveImage(sout.str().c_str(), gray))
    { 	soap_fault(soap);
      	cerr<<"Can not save to new image"<<endl;
      	soap->fault->faultstring = "Cannot save to new image";
      	return SOAP_FAULT;
    }
	cvReleaseImage(&img);
	cvReleaseImage(&gray);
	
    FILE *fd = fopen(sout.str().c_str(), "r");
	fseek(fd,0,SEEK_END); // seek to end of file
	int size = ftell(fd); // get current file pointer
	fseek(fd, 0, SEEK_SET); // seek back to beginning of file

//  struct stat fs;
//	fstat(fd, &fs);
//	int size = fs.st_size;

    image.__ptr = (unsigned char*)soap_malloc(soap, size);
    for (int i = 0; i < size; i++)
    { if ((int c = fgetc(fd)) == EOF)
        break;
      image.__ptr[i] = c;
    }
    image.__size = i;
	cerr<<"read file"<<endl;
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
