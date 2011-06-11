#include <iostream>
#include <cv.h>
#include <highgui.h>
using namespace std;

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
//#include "27_1.h"

struct shared_stuff {
    CvMat *output1Ch;
    IplImage *tmpImage;
};

int main (int argc, char** argv){
    
    struct shared_stuff *stuff;
    int shmid;
    key_t key = 5678;
    char *stuff_addr;  // addr for adding data space
    
    /*  load image and create header */ 
    IplImage *img = cvLoadImage(argv[0],CV_LOAD_IMAGE_GRAYSCALE);
	stuff->tmpImage = cvCreateImageHeader(cvSize(img->width, img->height), IPL_DEPTH_8U, 1);
    stuff->output1Ch = cvCreateMatHeader(img->height, img->width, CV_32FC1);
    
    /* Create the segment */
    if ((shmid = shmget(key,sizeof(shared_stuff), IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    /* Attach the segment to our data space */
    if ((stuff_addr = (char *) shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    /* assign data address */
    stuff = (struct shared_stuff *)stuff_addr;
    
    CvMat *input_morph = cvCreateMat(stuff->output1Ch->height,stuff->output1Ch->width,CV_32FC1);
    cvThreshold(stuff->output1Ch, input_morph, -0.5, 255.0, CV_THRESH_BINARY);
    IplConvKernel *se1 = cvCreateStructuringElementEx(3, 3, 1, 1, CV_SHAPE_ELLIPSE);
    cvMorphologyEx(input_morph, input_morph, NULL, se1, CV_MOP_OPEN);
    
    IplImage *tmp8UC1 = cvCreateImage(cvGetSize(input_morph), IPL_DEPTH_8U, 1);
    cvConvert(input_morph, tmp8UC1);
    
    cvNamedWindow("tmpImage", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("tmp8UC1", CV_WINDOW_AUTOSIZE);
    cvShowImage("tmpImage", stuff->tmpImage);
    cvShowImage("tmp8UC1", tmp8UC1);
    cvWaitKey(10000);
    cvDestroyWindow("tmpImage");
    cvDestroyWindow("tmp8UC1");
    
    if(!cvSaveImage("tmp8UC1.jpg", tmp8UC1))
        { 	
            cerr<<"Can not save to new image"<<endl;
        }
    /* Realease Memory */
    cvReleaseImage(&img);
    cvReleaseImage(&tmp8UC1);
    
    if (shmdt(stuff_addr) == -1) {
        perror("shmdt");
        exit(1);
    }

    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        perror("shmctl");
        exit(1);
    }
    return 0;
}

