//แยกมาจาก 270211
// เปลี่ยน จากการใช้ xml เป็น sharedmem

// to do list
// แก้ฟังก์ชันจับเวลาใหม่
// - current_time เวลาปัจจุบัน, เวลาเริ่มต้น
// current_time - previous_time เวลาที่ใช้ไป
// - previous_time = current_time 
// แก้เป็น shared memory

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
#include <time.h>
#include <string.h>
#include <cstring>

//init variable
#define BASE_DIR "/home/lluu/dir/"
#define int64 long long
#define imgWidth 3600
#define imgHeight 2880
#define img1ChSize 10368000
using namespace std;

static timeval start_time;
//static timeval previous_time;
//static timeval current_time;

//function
void init_time();
void get_time(char);
int get_matSize(CvMat*);


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
    cerr<<"***Time :"<<1900+tm->tm_year<<'-'<<1+tm->tm_mon<<'-'<<tm->tm_mday<<" "<<tm->tm_hour<<':'<<tm->tm_min<<"***"<<endl;
}

void get_time(char *msg) {

    timeval t;
    gettimeofday(&t, NULL);
    cerr<<(int64) (t.tv_sec - start_time.tv_sec) + (t.tv_usec -start_time.tv_usec)/1000000.0<<" "<<msg;
}

int get_matSize(CvMat *mat) {
    return mat->rows * mat->step;
}


int rand_lim() {
/* return a random number between 0 and limit inclusive.
 */

    int divisor = RAND_MAX/(1000);
    int retval;

    do { 
        retval = rand() / divisor;
    } while (retval > limit);

    return retval;
}



int ns__Ipl1ChToMat(struct soap *soap, char *InputFilename, int &key)
{   
    // shared memory initail
    int shmid;
    key = rand_lim();
    uchar *addr;
    
    if(InputFilename)
    { 
        // load image from directory
        IplImage* src = cvLoadImage(InputFilename,CV_LOAD_IMAGE_GRAYSCALE);
        if (!src)
        { 	
            soap_fault(soap);
            cerr<<"Can not open image file"<<endl;
            soap->fault->faultstring = "Can not open image file";
            return SOAP_FAULT;
        }
    
        CvMat *output1Ch = cvCreateMat(src->height, src->width, CV_32FC1);

        /* Create the segment */
        if ((shmid = shmget(key, get_matSize(output1h), IPC_CREAT | 0666)) < 0) {
            perror("shmget");
            exit(1);
        }
        /* Attach the segment to our data space */
        if ((addr = (uchar *) shmat(shmid, NULL, 0)) == (uchar *) -1) {
            perror("shmat");
            exit(1);
        }
    
        output1Ch->data.ptr = addr;
        cvConvertScale(src, output1Ch);
    
        cvReleaseImage(&src);
        cvReleaseMat(&output1Ch);

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


int ns__MatToIpl1Ch(struct soap *soap, char *InputFilename, 
                    char *filename, char *&OutputFilename)
{ 
    init_time();
    cerr<<"MatToIpl1Ch started"<<endl;
    if(InputFilename)
    { 
        
        CvMat* output1Ch;
        output1Ch = (CvMat*)cvLoad(InputFilename);
        
        if (!output1Ch)
        { 	
            soap_fault(soap);
            cerr<<"Can not open image file"<<endl;
            soap->fault->faultstring = "Cannot open image file";
            return SOAP_FAULT;
        }
        IplImage *tmp8UC1 = cvCreateImage(cvGetSize(output1Ch), IPL_DEPTH_8U, 1);
        cvConvert(output1Ch, tmp8UC1);
        //cvSave(filename,tmp8UC1);
        
        //if(!filename)
        //{ 	
            //soap_fault(soap);
            //cerr<<"Can not save to new image"<<endl;
            //soap->fault->faultstring = "Cannot save to new image";
            //return SOAP_FAULT;
        //}
        
        //ostringstream sout;
        //sout<<filename<<".jpg";
        //size_t len = sout.str().length();
        //OutputFilename = new char[len+1];
        //memcpy(OutputFilename,sout.str().c_str(),len);
        
        if(!cvSaveImage(filename, tmp8UC1))
        { 	
            soap_fault(soap);
            cerr<<"Can not save to new image"<<endl;
            soap->fault->faultstring = "Cannot save to new image";
            return SOAP_FAULT;
        }
        
        cvReleaseImage(&tmp8UC1);
        
        OutputFilename = new char[strlen(filename)];
        //memcpy(OutputFilename,filename,strlen(filename));
        strcpy(OutputFilename,filename);
        get_time("finished : MatToIpl1Ch \n\n");

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


int ns__BinaryThreshold(struct soap *soap, char *InputFilename, 
                        double threshold, double maxValue, 
                        char *filename, char *&OutputFilename)
{ 
    init_time();
    cerr<<"BinaryThreshold started"<<endl;
    if(InputFilename)
    { 
        // load image from directory
        CvMat* src1Ch;
        src1Ch = (CvMat*)cvLoad(InputFilename);
        if (!src1Ch)
        { 	
            soap_fault(soap);
            cerr<<"Can not open image file"<<endl;
            soap->fault->faultstring = "Cannot open image file";
            return SOAP_FAULT;
        }
    
        CvMat *matThreshold = cvCreateMat(src1Ch->height, src1Ch->width, CV_32FC1);
        cvThreshold(src1Ch, matThreshold, threshold, maxValue, CV_THRESH_BINARY);
        cvSave(filename,matThreshold);
    
        if(!filename)
        { 	
            soap_fault(soap);
            cerr<<"Can not save to mat"<<endl;
            soap->fault->faultstring = "Cannot save to mat";
            return SOAP_FAULT;
        }
        cvReleaseMat(&src1Ch);
        cvReleaseMat(&matThreshold);

        OutputFilename = new char[strlen(filename)];
        //memcpy(OutputFilename,filename,strlen(filename)+1);
        strcpy(OutputFilename,filename);
        get_time("finished : BinaryThreshold \n\n");
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




int ns__MorphOpen(  struct soap *soap, char *InputFilename, 
                char *filename, char *&OutputFilename)
{ 
    init_time();
    cerr<<"MorphOpen started"<<endl;
    if(InputFilename)
    { 
        // load image from directory
        CvMat* input_morph;
        input_morph = (CvMat*)cvLoad(InputFilename);
        if (!input_morph)
        { 	
            soap_fault(soap);
            cerr<<"Can not open image file"<<endl;
            soap->fault->faultstring = "Cannot open image file";
            return SOAP_FAULT;
        }
    
        IplConvKernel *se1 = cvCreateStructuringElementEx(3, 3, 1, 1, CV_SHAPE_ELLIPSE);
        cvMorphologyEx(input_morph, input_morph, NULL, se1, CV_MOP_OPEN);
        
        cvSave(filename,input_morph);
        if(!filename)
        { 	
            soap_fault(soap);
            cerr<<"Can not save to mat"<<endl;
            soap->fault->faultstring = "Cannot save to mat";
            return SOAP_FAULT;
        }
        
        cvReleaseMat(&input_morph);

        OutputFilename = new char[strlen(filename)];
        //memcpy(OutputFilename,filename,strlen(filename)+1);
        strcpy(OutputFilename,filename);
        get_time("finished : MorphOpen \n\n");
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
