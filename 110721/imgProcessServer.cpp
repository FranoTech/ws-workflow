//แยกมาจาก 280611

#include "soapH.h"
#include "imgProcess.nsmap"
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



int ns__Ipl1ChToMat(struct soap *soap, char *InputFilename, ns__ImageData &out)
{   
    
    // shared memory initail
    int shmid;
    uchar *addr;
    int randkey = rand_key();
    out.sharedKey = randkey;
    
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
        
        out.imgHeight = src->height;
        out.imgWidth = src->width;
        
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


// ยังไม่เสร็จ

 //	------------      ----------  
 //	|  mat32FC1|   => | output |
 //	------------      ----------

int ns__BinaryThreshold(struct soap *soap, int sharedKey, int imgHeight, int imgWidth, double threshold, 
                        double maxValue, ns__ImageData &out)
{ 
    if(sharedKey)
    { 
        int shmid;
        uchar *addr;
        int matSize;
        
        CvMat *mat32FC1 = cvCreateMatHeader(imgHeight, imgWidth, CV_32FC1);
        matSize = get_matSize(mat32FC1);
        
        /* Create the segment */
        if ((shmid = shmget(sharedKey, matSize, IPC_CREAT | 0666)) < 0) {
            perror("shmget");
            cerr<<"shmget::can't create shared segment"<<endl;
            exit(1);
        }
        
        /* Attach the segment to our data space */
        if ((addr = (uchar *) shmat(shmid, NULL, 0)) == (uchar *) -1) {
            perror("shmat");
            cerr<<"shmat:: can't attach shared segment"<<endl;
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
        
        // prepare sharedmem segment to do thresholding
        CvMat *output = cvCreateMatHeader(imgHeight, imgWidth, CV_32FC1);
        outputSize = get_matSize(output);
        
        /* Create the segment */
        if ((shmid = shmget(sharedKey, outputSize, IPC_CREAT | 0666)) < 0) {
            perror("shmget");
            cerr<<"shmget::can't create shared segment"<<endl;
            exit(1);
        }
        
        /* Attach the segment to our data space */
        if ((addr = (uchar *) shmat(shmid, NULL, 0)) == (uchar *) -1) {
            perror("shmat");
            cerr<<"shmat:: can't attach shared segment"<<endl;
            exit(1);
        }
        output->data.ptr = addr;
        
        // do threshold
        cvThreshold(mat32FC1, output, threshold, maxValue, CV_THRESH_BINARY);
        
        //char *filename = "/home/lluu/dir/threshold.xml";
        //cvSave(filename,matThreshold);
    
        //if(!filename)
        //{ 	
            //soap_fault(soap);
            //cerr<<"Can not save to mat"<<endl;
            //soap->fault->faultstring = "Cannot save to mat";
            //return SOAP_FAULT;
        //}
        
        
        int randkey = rand_key();
        out.sharedKey = randkey;
        out.imgHeight = imgHeight ;
        out.imgWidth = imgWidth ;

        cvReleaseMat(&mat32FC1);
        cvReleaseMat(&output);
        
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

// ยังไม่เสร็จ


int ns__MorphOpen(  struct soap *soap, int sharedKey, int imgHeight, int imgWidth, 
					ns__ImageData &out)
{ 

    if(sharedKey)
    { 
		int shmid;
        uchar *addr;
        int matSize;
		
		CvMat *mat32FC1 = cvCreateMatHeader(imgHeight, imgWidth, CV_32FC1);
        matSize = get_matSize(mat32FC1);
        
        /* Create the segment */
        if ((shmid = shmget(sharedKey, matSize, IPC_CREAT | 0666)) < 0) {
            perror("shmget");
            cerr<<"shmget::can't create shared segment"<<endl;
            exit(1);
        }
        
        /* Attach the segment to our data space */
        if ((addr = (uchar *) shmat(shmid, NULL, 0)) == (uchar *) -1) {
            perror("shmat");
            cerr<<"shmat:: can't attach shared segment"<<endl;
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
    
		// do morphology
        IplConvKernel *se1 = cvCreateStructuringElementEx(3, 3, 1, 1, CV_SHAPE_ELLIPSE);
        cvMorphologyEx(mat32FC1, mat32FC1, NULL, se1, CV_MOP_OPEN);
                
        cvReleaseMat(&mat32FC1);
        cvReleaseMat(&input_morph);
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

//	------------	------- 
//	| mat32FC1 | => | JPG |
//	------------	-------
int ns__MatToJPG(struct soap *soap, int sharedKey, int imgHeight, int imgWidth, char *&OutputFilename)
{   
    if(sharedKey)
    { 
        int shmid;
        uchar *addr;
        int matSize;
        
        CvMat *mat32FC1 = cvCreateMatHeader(imgHeight, imgWidth, CV_32FC1);
        matSize = get_matSize(mat32FC1);
        
        /* Create the segment */
        if ((shmid = shmget(sharedKey, matSize, IPC_CREAT | 0666)) < 0) {
            perror("shmget");
            cerr<<"shmget::can't create shared segment"<<endl;
            exit(1);
        }
        
        /* Attach the segment to our data space */
        if ((addr = (uchar *) shmat(shmid, NULL, 0)) == (uchar *) -1) {
            perror("shmat");
            cerr<<"shmat:: can't attach shared segment"<<endl;
            exit(1);
        }
        mat32FC1->data.ptr = addr;

		//do convert image scale
        IplImage *tmp8UC1 = cvCreateImage(cvGetSize(mat32FC1), IPL_DEPTH_8U, 1);
        cvConvert(mat32FC1, tmp8UC1);
        
		//preparing filename to save
        ostringstream sout;
        char* filename;
        time_t init = time(0);
        tm* tm = localtime(&init);
        sout<<1900+tm->tm_year<<1+tm->tm_mon<<tm->tm_mday<<tm->tm_hour<<tm->tm_min<<":MatToJPG.xml";
        filename = sout.str();
        
        //save result to .jpg
        cvSave(filename,tmp8UC1);
        if(!filename)
        { 	
            soap_fault(soap);
            cerr<<"Can not save to mat"<<endl;
            soap->fault->faultstring = "Cannot save to mat";
            return SOAP_FAULT;
        }

        OutputFilename = new char[strlen(filename)+1];
        memcpy(OutputFilename,filename,strlen(filename)+1);
        
        cerr<<"do convert scale"<<endl;
        cvReleaseImage(&tmp8UC1);
        cvReleaseMat(&mat32FC1);

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
