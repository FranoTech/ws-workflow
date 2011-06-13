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
    IplImage* src = cvLoadImage(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
    //CvMat *mat32FC1 = cvCreateMat(src->height, src->width, CV_32FC1);
    Mat mat32FC1(src->height, src->width, CV_32FC1);

    /* Create the segment */
    if ((shmid = shmget(key, src->imageSize, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
        
    /* Attach the segment to our data space */
    if ((addr = (char *) shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }
    
    = addr;
    cvCopy(img,tmpImage);
    
    cvReleaseImage(&img);
    cvReleaseImage(&tmpImage);
    
    return 0;
}
