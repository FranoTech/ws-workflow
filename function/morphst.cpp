#include <iostream>
#include <cv.h>
#include <highgui.h>
using namespace std;

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

int sizeofmat(CvMat *mat) {
    return mat->rows * mat->step;
}

int main (int argc, char** argv){
    
    int shmid;
    key_t key = 5678;
    uchar *matdata;
    
    /*  load image  */ 
    IplImage *img = cvLoadImage(argv[1]);
	IplImage *tmpImage = cvCreateImage(cvSize(img->Width, img->Height), IPL_DEPTH_8U, 3);
    tmpImage = cvCopy(img,tmpImage);
    
    CvMat *output1Ch = cvCreateMat(img->Height, img->Width, CV_32FC1);
    CvMat *input_morph = cvCreateMat(output1Ch->height, output1Ch->width, CV_32FC1);
    
    const size_t matsize = sizeofmat(input_morph);
    
    /* Create the segment */
    if ((shmid = shmget(key, matsize, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    /* Attach the segment to our data space */
    if ((mataddr = (uchar *) shmat(shmid, NULL, 0)) == (uchar *) -1) {
        perror("shmat");
        exit(1);
    }

    input_morph->data.ptr = mataddr;
    
    /* remove noise */
    cvThreshold(output1Ch, input_morph, -0.5, 255.0, CV_THRESH_BINARY);
    IplConvKernel *se1 = cvCreateStructuringElementEx(3, 3, 1, 1, CV_SHAPE_ELLIPSE);
    cvMorphologyEx(input_morph, input_morph, nullptr, se1, CV_MOP_OPEN); // remove noise

    
    

