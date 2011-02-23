#include <iostream>
#include <cv.h>
#include <highgui.h>
using namespace std;

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

int main (int argc, char** argv){
    
    int shmid;
    key_t key = 5678;
    char *addr;
    
    
    
    /*  load image  */ 
    IplImage *img = cvLoadImage(argv[1]);
	IplImage *tmpImage = cvCreateImageHeader(cvSize(img->width, img->height), IPL_DEPTH_8U, 3);
    
    //const size_t imgSize = sizeofmat(tmpImage);
    /* Create the segment */
    if ((shmid = shmget(key, tmpImage->imageSize, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    //cout<<tmpImage->imageSize<<endl;
    
    /* Attach the segment to our data space */
    if ((addr = (char *) shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    tmpImage->imageData = addr;
    cvCopy(img,tmpImage);
    
    cvReleaseImage(&img);
    cvReleaseImage(&tmpImage);
    
    return 0;
}


