#include <iostream>
#include <cv.h>
#include <highgui.h>
using namespace std;

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include "27_1.h"

int main (int argc, char** argv){
    
    struct shared_stuff *stuff;
    int shmid;
    key_t key = 5678;
    char *stuff_addr;  // addr for adding data space
    
    /*  load image and create header */ 
    IplImage *img = cvLoadImage(argv[0]);
	stuff->tmpImage = cvCreateImageHeader(cvSize(img->width, img->height), IPL_DEPTH_8U, 3);
    stuff->output1Ch = cvCreateMatHeader(img->Height, img->Width, CV_32FC1);
    
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

    /* Realease Memory */
    cvReleaseImage(&img);
    
    return 0;
}

