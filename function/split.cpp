#include <iostream>
#include <fstream>
#include <cv.h>
#include <highgui.h>

using namespace std;
using namespace cv;

int main (int argc, char** argv){
   
    Mat src  = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    src.convertTo(src, CV_32FC3);
    vector<Mat> splited;
    
    cv::split(src, splited); 
    
    /* splited[0] = B
    * splited[1] = G
    * splited[2] = R
    */
    
    Mat RB (splited[0].rows, splited[0].cols, CV_32FC1);
    Mat BR (splited[0].rows, splited[0].cols, CV_32FC1);
    Mat result = Mat::zeros(splited[0].rows, splited[0].cols, CV_32FC1);
    
    /* find R:B */
    cv::divide(splited[2], splited[0], RB, 1);
    
    /* find B:R */
    cv::divide(splited[0], splited[2], BR, 1);

/* Find POS Cell */
    for( int y = 0; y < RB.rows; y++ )
    {   for( int x = 0; x < RB.cols; x++ ){ 
            //if(splited[0].at<float>(y,x) != 0 && (splited[2].at<float>(y,x)/splited[0].at<float>(y,x) >= 1))
            if(RB.at<float>(y,x) >= 1 && BR.at<float>(y,x) < 0.9)
                result.at<float>(y,x) = 0;   // pos cell is black
            else
                result.at<float>(y,x) = 255;
            //cout<<(float)RB.at<uchar>(y,x)<<" ";
        }
        //cout<<endl;
    }   
        
    namedWindow("RB", CV_WINDOW_AUTOSIZE);
    imshow("RB", result);
    waitKey(0);   
    
    
    //cout<<"c = "<<c<<endl<<"r = "<<r<<endl;
    src.release();
    splited.clear();
    RB.release();    
    BR.release();
    result.release();
    
    return 0;
}
    
