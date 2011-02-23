#include <iostream>
#include "cv.h"
#include "highgui.h"
#include <unistd.h >
#include <stdlib.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include "shmstruct.h"

int main (int argc, char** argv){
    
    //using sharedmemory
    struct shm_var *shared_stuff;
    int shmid;
    void *shared_mem = (void *)0;
    srand((unsigned int)getpid());
    
    /* Create the segment */
    shmid = shmget((key_t)1234, size0f(struct shm_var), 0666 | IPC_CREATE);
    if(shmid = -1){
        cerr<<"shmget failed"<<endl;
        exit(EXIT_FAILURE);
    }
    
    /* Attach the segment to our data space */
    shared_mem = shmat(shmid,(void *)0, 0);
    if(shared_mem == (void *)-1)
        cerr<<"shmat failed"<<endl;
        exit(EXIT_FAILURE);
    }
    cout<<"memory attached at"<<(int)shared_mem<<endl;
    
    shared_stuff = (struct shm_var)share_mem;
    
    IplImage *img = cvLoadImage(argv[1]);
	IplImage *tmpImage = cvCreateImage(cvSize(img->Width, img->Height), IPL_DEPTH_8U, 3);
    tmpImage = cvCopy(img,tmpImage);
	
    shared_stuff->input3Ch = cvCreateMat(img->Height, img->Width, CV_32FC3);
	shared_stuff->output1Ch = cvCreateMat(img->Height, img->Width, CV_32FC1);
	shared_stuff->input_morph = cvCreateMat(output1Ch->height, output1Ch->width, CV_32FC1);

	//cvConvertScale(tmpImage, input3Ch);
    cvThreshold(shared_stuff->output1Ch, shared_stuff->input_morph, -0.5, 255.0, CV_THRESH_BINARY);                                                                                                  t1Ch, input_morph, -0.5, 255.0, CV_THRESH_BINARY);
    IplConvKernel *se1 = cvCreateStructuringElementEx(3, 3, 1, 1, CV_SHAPE_ELLIPSE);
    cvMorphologyEx(shared_stuff->input_morph, shared_stuff->input_morph, nullptr, se1, CV_MOP_OPEN); // remove noise

    out_single = cvCreateMat(input_morph->height, input_morph->width, CV_32FC1);
    cvSetZero(out_single);
    tmp8UC1 = cvCreateImage(cvGetSize(input_morph), IPL_DEPTH_8U, 1);
