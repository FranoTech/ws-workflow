#include <iostream>
#include <fstream>
#include <cv.h>
#include <highgui.h>

using namespace std;
using namespace cv;
int saveMat( string& filename, const Mat& M);
int readMat( const string& filename, Mat& M);

int main (int argc, char** argv){
    
    Mat src  = imread(argv[1],0);
    Mat gray;
    
    Mat result = Mat::zeros(src.rows,src.cols, CV_32FC1);
    threshold(src, gray, 127.0, 255.0, CV_THRESH_BINARY);
    
    vector<vector<Point> > contours;
    vector<double> area;
    findContours(	gray, contours, CV_RETR_EXTERNAL, 
					CV_CHAIN_APPROX_SIMPLE, Point(0,0));
    for(size_t i = 0; i< contours.size(); i++)
    {
		const Point* p = &contours[i][0];
        int n = (int)contours[i].size();
		area[i] = contourArea(Mat(contours[i]));
		
	}
	
    
    
    namedWindow("result", CV_WINDOW_AUTOSIZE);
    imshow("result", src);
    waitKey(0);
    
    namedWindow("result", CV_WINDOW_AUTOSIZE);
    imshow("result", result);
    waitKey(0);
    
    contours.clear();
    src.release();
    gray.release();
    
    return 0;
}

void write ( vector<double> &area)
{
        std::ofstream output_file("example");
        std::ostream_iterator<std::string> output_iterator(output_file, "\n");
        std::copy(example.begin(), example.end(), output_iterator);
}
