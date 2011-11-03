#include <iostream>
#include <fstream>
#include <cv.h>
#include <highgui.h>

using namespace std;
using namespace cv;

int main (int argc, char** argv){
   
    Mat src  = imread(argv[1],1);
    src.convertTo(src, CV_32FC1);
    
    vector<Mat> splited;
    Mat RB (src.rows, src.cols, CV_32FC1);
    //Mat BR;
    cv::split(src, splited); 
    
    /* splited[0] = R
    * splited[1] = G
    * splited[2] = B
    */
    
    // R/B
    cv::divide(splited[0], splited[2], RB, 1);
    
    for( int y = 0; y < RB.rows; y++ )
    {   for( int x = 0; x < RB.cols; x++ )
        //    out<<RB.at<double>(y,x)<<" ";
        //cout<<endl;
        if(RB.at<int>(y,x)>0)
            RB.at<int>(y,x) = 0;
        else
            RB.at<int>(y,x) = 255;
    }   
        
    namedWindow("src", CV_WINDOW_AUTOSIZE);
    imshow("src", RB);
    waitKey(0);    
        
    src.release();
    splited.clear();
    RB.release();
    
    return 0;
}
    
