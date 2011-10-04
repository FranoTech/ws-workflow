#include <iostream>
#include <fstream>
#include <cv.h>
#include <highgui.h>

using namespace std;
using namespace cv;

int main (int argc, char** argv){
	
	Mat src  = imread(argv[1],0);
	//Mat src2 = Mat::zeros(src.rows, src.cols, CV_8UC1);
	Mat dst = Mat(src.rows, src.cols, CV_8UC1);
	//Mat elem = cv::noArray();
	
	//for(int i = 0; i < 10; i++)
	//{
		//erode(src, src, src);
		//i++;
	//}
	
	//erode(src, dst, src2);
	erode(src, dst, Mat());
	
	namedWindow("src", CV_WINDOW_AUTOSIZE);
    imshow("src", src);
    waitKey(0);
    
	namedWindow("result", CV_WINDOW_AUTOSIZE);
    imshow("result", dst);
    waitKey(0);
    
    src.release();
    dst.release();
    
    return 0;
    
}

