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
    IplImage *img = cvLoadImage(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    if(!img){
        cout<<"can not load image";
        exit(1);
    }
    
	CvMat *mat32FC1 = cvCreateMatHeader(img->height, img->width, CV_32FC1);
	if(!mat32FC1){
        cout<<"can not create mat";
        exit(1);
    }
    
	//IplImage *tmpImage = cvCreateImageHeader(cvSize(img->width, img->height), IPL_DEPTH_8U, 3);
	//const size_t imgSize = sizeofmat(tmpImage);
    
    
    /* Create the segment */
    if ((shmid = shmget(key, img->imageSize, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    
    /* Attach the segment to our data space */
    if ((addr = (char *) shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }
    
    // !!!!!!!!!!!!!!!!!
    mat32FC1->data.ptr = (unsigned char *)addr;
    cvConvertScale(img, mat32FC1);
    
    CvSize matSize = cvGetSize(mat32FC1);
    cout<<mat32FC1->height<<endl;
    cout<<mat32FC1->width<<endl;
    cout<<"[1,33] = "<<CV_MAT_ELEM(*mat32FC1, float, 1, 33)<<endl;
    
    cvReleaseImage(&img);
    cvReleaseMat(&mat32FC1);
    
    return 0;
}


