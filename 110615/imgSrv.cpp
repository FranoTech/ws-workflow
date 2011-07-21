//แยกมาจาก 270211
// เปลี่ยน จากการใช้ xml เป็น sharedmem

// to do list
// แก้ฟังก์ชันจับเวลาใหม่
// - current_time เวลาปัจจุบัน, เวลาเริ่มต้น
// current_time - previous_time เวลาที่ใช้ไป
// - previous_time = current_time 
// แก้เป็น shared memory

#include "soapH.h"
#include "img.nsmap"
#include <iostream>
#include "cv.h"
#include "highgui.h"
#include <sstream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/time.h> // time
#include <stdlib.h>  //rand()
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


int rand_key() {

    srand(time(NULL));  
    return rand()%10000;
    
}



int ns__Ipl1ChToMat(struct soap *soap, char *InputFilename, int *sharedkey)
{   
    
    // shared memory initail
    int shmid;
    uchar *addr;
    int randkey = rand_key();
    *sharedkey = randkey;
    
    cerr<<"got randkey = "<<randkey<<endl;
    cerr<<"got shared key = "<<*sharedkey<<endl;
    
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
        cerr<<"loaded img"<<endl;
        CvMat *output1Ch = cvCreateMat(src->height, src->width, CV_32FC1);

        /* Create the segment */
        if ((shmid = shmget(randkey, get_matSize(output1Ch), IPC_CREAT | 0666)) < 0) {
            perror("shmget");
            exit(1);
        }
        /* Attach the segment to our data space */
        if ((addr = (uchar *) shmat(shmid, NULL, 0)) == (uchar *) -1) {
            perror("shmat");
            exit(1);
        }
        cerr<<"attached shared memory"<<endl;
        output1Ch->data.ptr = addr;
        cvConvertScale(src, output1Ch);
        
        cerr<<"do convert scale"<<endl;
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

// LATER**
//int ns__MatToIpl1Ch(struct soap *soap, int *sharedkey)
//{ 
    //if(sharedkey)
    //{ 
        //int shmid;
        //uchar *addr;
        //CvMat *mat32FC1 = cvCreateMatHeader(imgHeight, imgWidth, CV_32FC1);
        
        ///* Create the segment */
        //if ((shmid = shmget(*sharedkey, get_matSize(mat32FC1), IPC_CREAT | 0666)) < 0) {
            //perror("shmget");
            //exit(1);
        //}
        
        ///* Attach the segment to our data space */
        //if ((addr = (uchar *) shmat(shmid, NULL, 0)) == (uchar *) -1) {
            //perror("shmat");
            //exit(1);
        //}
        
        //IplImage *tmp8UC1 = cvCreateImage(cvGetSize(output1Ch), IPL_DEPTH_8U, 1);
        //cvConvert(output1Ch, tmp8UC1);

        
        //if(!cvSaveImage(filename, tmp8UC1))
        //{ 	
            //soap_fault(soap);
            //cerr<<"Can not save to new image"<<endl;
            //soap->fault->faultstring = "Cannot save to new image";
            //return SOAP_FAULT;
        //}
        
        //cvReleaseImage(&tmp8UC1);
        
        //OutputFilename = new char[strlen(filename)];
        ////memcpy(OutputFilename,filename,strlen(filename));
        //strcpy(OutputFilename,filename);
        //get_time("finished : MatToIpl1Ch \n\n");

  //}
  //else
  //{ 
    //cerr<<"File Name require"<<endl;
    //soap_fault(soap);
    //soap->fault->faultstring = "Name required";
    //return SOAP_FAULT;
  //}
  //return SOAP_OK;
//}


int ns__BinaryThreshold(struct soap *soap, double threshold, 
                        double maxValue,int *sharedkey)
{ 
    if(*sharedkey)
    { 
        int shmid;
        uchar *addr;
        int matSize;
        
        CvMat *mat32FC1 = cvCreateMatHeader( imgHeight, imgWidth, CV_32FC1);
        matSize = get_matSize(mat32FC1);
        
        /* Create the segment */
        if ((shmid = shmget(*sharedkey, matSize, IPC_CREAT | 0666)) < 0) {
            perror("shmget");
            exit(1);
        }
        
        /* Attach the segment to our data space */
        if ((addr = (uchar *) shmat(shmid, NULL, 0)) == (uchar *) -1) {
            perror("shmat");
            exit(1);
        }
        
        if (!mat32FC1)
        { 	
            soap_fault(soap);
            cerr<<"Can not open image file"<<endl;
            soap->fault->faultstring = "Cannot open image file";
            return SOAP_FAULT;
        }
        mat32FC1->data.ptr = addr;
    
        // do threshold
        CvMat *matThreshold = cvCreateMat(mat32FC1->height, mat32FC1->width, CV_32FC1);
        cvThreshold(mat32FC1, matThreshold, threshold, maxValue, CV_THRESH_BINARY);
        
        char *filename = "/home/lluu/dir/threshold.xml";
        cvSave(filename,matThreshold);
    
        if(!filename)
        { 	
            soap_fault(soap);
            cerr<<"Can not save to mat"<<endl;
            soap->fault->faultstring = "Cannot save to mat";
            return SOAP_FAULT;
        }
        cvReleaseMat(&mat32FC1);
        cvReleaseMat(&matThreshold);

    }
    else
    { 
        cerr<<"shared key error"<<endl;
        soap_fault(soap);
        soap->fault->faultstring = "shared key error";
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
