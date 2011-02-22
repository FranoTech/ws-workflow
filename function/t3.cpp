//we can transfrom 8U 3ch to 32FC3 already

#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <sys/types.h>
using namespace std;

int main (int argc, char** argv){
    

	IplImage *tmpImage = cvCreateImage(cvSize(320, 240), IPL_DEPTH_8U, 3);
    cvSet(tmpImage,CV_RGB(255,255,255));
    IplImage *img = cvCreateImage(cvSize(320, 240), IPL_DEPTH_32F, 3);
    CvMat *input3Ch = cvCreateMat(320, 240, CV_32FC3);
    
    printf("before\n");
    /* CV_IMAGE_ELEM( img, uchar, row, col * img->nChannels + ch )*/
    int element32 = CV_IMAGE_ELEM( tmpImage, uchar, 3, 2);
    cout<<"element 3 2 : "<<element32<<endl;
     
    //for(int row=0; row<input3Ch->rows; row++ ) 
    //{
        //const float* ptr = (const float*)(input3Ch->data.ptr + row * input3Ch->step);
        //for( int col=0; col<input3Ch->cols; col++ ) 
        //{
            //printf("data %d, %d = %f\n", row, col, *ptr);
        //}
    //}
    
    printf("After\n");
    cvSetZero(tmpImage);
    cvConvertScale(tmpImage,img);
    input3Ch = cvGetMat(img,input3Ch,0,0);
    
    float e32 = CV_IMAGE_ELEM( img, float, 3, 2);
    cout<<"element 3 2 : "<<e32<<endl;
    
    float element_3_2 = CV_MAT_ELEM( *input3Ch, float, 3, 2 );
    cout<<"element 3 2 : "<<element_3_2<<endl;
    //cvConvertScale(tmpImage, input3Ch, 1/255.);
    //cvConvertScale(tmpImage, input3Ch);
    //for(int row=0; row<input3Ch->rows; row++ ) 
    //{
        //const float* ptr = (const float*)(input3Ch->data.ptr + row * input3Ch->step);
        //for( int col=0; col<input3Ch->cols; col++ ) 
        //{
            //printf("data %d, %d = %f\n", row, col, *ptr);
        //}
    //}



    return 0;
}
