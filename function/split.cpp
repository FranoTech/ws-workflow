#include <iostream>
#include <fstream>
#include <cv.h>
#include <highgui.h>

using namespace std;
using namespace cv;

int main (int argc, char** argv){
   
    Mat src  = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    //src.convertTo(src, CV_8UC3);
    
    vector<Mat> splited;
    Mat RB (src.rows, src.cols, CV_32FC1);
    //Mat BR;
    cv::split(src, splited); 
    
    /* splited[0] = B
    * splited[1] = G
    * splited[2] = R
    */
    
    //R/B
    //cv::divide(splited[2], splited[0], RB, 1);

    
    for( int y = 0; y < splited[2].rows; y++ )
    {   for( int x = 0; x < splited[2].cols; x++ )
        {
            //cout<<RB.at<int>(y,x)<<" ";
            //if(splited[0].at<int>(y,x) != 0)
                //RB.at<int>(y,x) = splited[2].at<int>(y,x)/splited[0].at<int>(y,x);
            //else
                //RB.at<int>(y,x) = 12345;
                
            cout<<splited[2].at<int>(y,x)<<" ";
            
        }
        cout<<endl;
    }   
    
    //int c = 0;
    //int r = 0;
    
    for( int y = 0; y < RB.rows; y++ )
    {   for( int x = 0; x < RB.cols; x++ )
            cout<<RB.at<int>(y,x)<<" ";
        cout<<endl;
    }   
        
    namedWindow("src", CV_WINDOW_AUTOSIZE);
    imshow("src", splited[0]);
    waitKey(0);    
    
    namedWindow("src", CV_WINDOW_AUTOSIZE);
    imshow("src", splited[2]);
    waitKey(0);   
    
    
    //cout<<"c = "<<c<<endl<<"r = "<<r<<endl;
    src.release();
    splited.clear();
    RB.release();
    
    return 0;
}
    
