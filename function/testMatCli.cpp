//worked !!

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
    uchar *addr;
	CvMat *mat32FC1 = cvCreateMatHeader(2880, 3600, CV_32FC1);
	
	int matSize = sizeofmat(mat32FC1);
    
    
    /* Create the segment */
    if ((shmid = shmget(key, matSize, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    
    /* Attach the segment to our data space */
    if ((addr = (uchar *) shmat(shmid, NULL, 0)) == (uchar *) -1) {
        perror("shmat");
        exit(1);
    }
    
    mat32FC1->data.ptr = addr;
    
    CvSize mat_Size = cvGetSize(mat32FC1);
    cout<<mat32FC1->height<<endl;
    cout<<mat32FC1->width<<endl;
    cout<<"[1,33] = "<<CV_MAT_ELEM(*mat32FC1, float, 1, 33)<<endl;
    
    IplImage *tmp8UC1 = cvCreateImage(cvGetSize(mat32FC1), IPL_DEPTH_8U, 1);
    cvConvert(mat32FC1, tmp8UC1);
    
    cvNamedWindow("result", CV_WINDOW_AUTOSIZE);
    cvShowImage("result", tmp8UC1);
    cvWaitKey(10000);
    cvDestroyWindow("result");
    
    cvReleaseMat(&mat32FC1);
    cvReleaseImage(&tmp8UC1);
    
    return 0;
}


