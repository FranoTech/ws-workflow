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
    
    //R/B
    Mat RB (splited[0].rows, splited[0].cols, CV_32FC1);
    cv::divide(splited[2], splited[1], RB, 1);
    
    
    //for( int y = 0; y < splited[2].rows; y++ )
    //{   for( int x = 0; x < splited[2].cols; x++ )
        //{
            ////if(splited[0].at<int>(y,x) != 0)
                ////RB.at<int>(y,x) = splited[2].at<int>(y,x)/splited[0].at<int>(y,x);
            ////else
                ////RB.at<int>(y,x) = 12345;
                
            //cout<<(int)splited[2].at<uchar>(y,x)<<" ";
            
        //}
        //cout<<endl;
    //}   

    for( int y = 0; y < RB.rows; y++ )
    {   for( int x = 0; x < RB.cols; x++ ){ 
            if(splited[0].at<float>(y,x) != 0 && (splited[2].at<float>(y,x)/splited[0].at<float>(y,x) >= 1))
                RB.at<float>(y,x) = 255;
            else
                RB.at<float>(y,x) = 0;
            //cout<<(float)RB.at<uchar>(y,x)<<" ";
        }
        cout<<endl;
    }   
        
    namedWindow("RB", CV_WINDOW_AUTOSIZE);
    imshow("RB", RB);
    waitKey(0);   
    
    
    //cout<<"c = "<<c<<endl<<"r = "<<r<<endl;
    src.release();
    splited.clear();
    RB.release();
    
    return 0;
}
    
