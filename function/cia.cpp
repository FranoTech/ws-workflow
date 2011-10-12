#include <iostream>
#include <fstream>
#include <cv.h>
#include <highgui.h>

using namespace std;
using namespace cv;

int main (int argc, char** argv){
    
    Mat src  = imread(argv[1],0);
    Mat input_morph(src.rows, src.cols, CV_32FC1);
    
    /* thresholding */
    threshold(src, input_morph, 127.0, 255.0, CV_THRESH_BINARY); //input_morph = 8UC1
    input_morph.convertTo(input_morph, CV_32FC1); //transform input_morph to 32FC1
    
    /* morph opening */
    Mat se; 
    Size seSize(3, 3);
    Point seAnc(1, 1);
    
    se = getStructuringElement(MORPH_ELLIPSE, seSize, seAnc);
    morphologyEx(input_morph, input_morph, MORPH_OPEN, se, seAnc);

    /* find contour */
    Mat out_single = Mat::zeros(input_morph.rows, input_morph.cols, CV_32FC1);
    Mat tmp8UC1(src.rows, src.cols, CV_8UC1);
    input_morph.convertTo(tmp8UC1, CV_8UC1);
    
    
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    double area = 0;
    findContours( tmp8UC1, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    for(size_t i = 0; i< contours.size(); i++)
    {
		const Point* p = &contours[i][0];
        int n = (int)contours[i].size();
		area = contourArea(Mat(contours[i]));
		
		if(area < 1500.0) //lower bound
		{
			fillPoly( input_morph, &p, &n, 1, Scalar(0, 0, 0));
		} else if (area < 7500.0) {
        //if ((area > 1500.0)&&(area < 7500.0)) {
            fillPoly( out_single, &p, &n, 1, Scalar(255,255,255)); // move to result
            fillPoly( input_morph, &p, &n, 1, Scalar(0, 0, 0)); // remove from input
        }else{
			fillPoly( input_morph, &p, &n, 1, Scalar(255,255,255));
		}
	}
    
    Mat tmp(src.rows, src.cols, CV_8UC1);
    input_morph.convertTo(tmp, CV_8UC1);
    if(!imwrite("input_morph.jpg", tmp))
    {
		cout<<"error writing image"<<endl;
    }
    
    out_single.convertTo(tmp, CV_8UC1);
    if(!imwrite("out_single.jpg", tmp))
    {
		cout<<"error writing image"<<endl;
    }
   
    contours.clear();
    hierarchy.clear();

    Mat output_morph = Mat(input_morph.rows, input_morph.cols, CV_32FC1);
    bitwise_or(input_morph, out_single, output_morph);
    
    output_morph.convertTo(tmp, CV_8UC1);
    if(!imwrite("output_morph.jpg", tmp))
    {
		cout<<"error writing image"<<endl;
    }
   
   /* scanning cell */
    int nContour = 1;
    int prevContour = 0;
    int sameCount = 0;
    area = 0;
                                                                                                                                                                                                                                                                                                                                                                                                                                        0;

    
    while(nContour != 0)
    {
        input_morph.convertTo(tmp8UC1, CV_8UC1);

        findContours( tmp8UC1, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
        nContour = contours.size();
        
        if( nContour == 0){ break; }
        if( nContour == prevContour ){ 
            erode( input_morph, input_morph, Mat() );
            sameCount++;
        }else {
            sameCount = 0;
        }
        
        prevContour = nContour;
        
        for(size_t i = 0; i< contours.size(); i++)
        {
            const Point* p = &contours[i][0];
            int n = (int)contours[i].size();
            area = contourArea(Mat(contours[i]));
            
            if((area < 3000.0) || (sameCount > 10))
            {
                fillPoly( input_morph, &p, &n, 1, Scalar(0, 0, 0)); // remove from src 
                fillPoly( out_single, &p, &n, 1, Scalar(255, 255, 255)); 
            }
        }
    }
    
    input_morph.convertTo(tmp, CV_8UC1);
    if(!imwrite("input_morph-1.jpg", tmp))
    {
		cout<<"error writing image"<<endl;
    }
    
    out_single.convertTo(tmp, CV_8UC1);
    if(!imwrite("out_single-1.jpg", tmp))
    {
		cout<<"error writing image"<<endl;
    }
    
    contours.clear();
    src.release();
    out_single.release();
    input_morph.release();
    output_morph.release();
    tmp.release();
    tmp8UC1.release();
    
    return 0;
}








