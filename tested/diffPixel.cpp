#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <fstream>


using namespace std;
using namespace cv;

int readMat( const char *filename, Mat& M);
int count_diff_pixels( Mat in1, Mat in2);

int main(int argc, char **argv)
{
    // Mat fromExe = imread(argv[1],0);
    Mat fromExe;
    Mat fromWS;

    if(!readMat(argv[1], fromExe))
    {
		std::cout<<"Can not open image file to test"<<std::endl;
    }

    if(!readMat(argv[2], fromWS))
    {
		std::cout<<"Can not open image file to test"<<std::endl;
    }

    if(count_diff_pixels(fromExe, fromWS) == (fromExe.rows * fromExe.cols))
    	std::cout<<"two images are similar"<<std::endl;
    else
    	std::cout<<"two images are different"<<std::endl;

    return 0;
}


int count_diff_pixels( Mat in1, Mat in2) {
    Mat diff;
    cv::compare(in1, in2, diff, cv::CMP_EQ);
    return cv::countNonZero(diff);
}

/* Read matrix from binary file */
int readMat( const char *filename, Mat& M)
{
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if (!in){
       M.data = NULL;
       return 0;
    }
    int cols;
    int rows;
    int chan;
    int eSiz;

    /* Read header */
    in.read((char*)&cols,sizeof(cols));
    in.read((char*)&rows,sizeof(rows));
    in.read((char*)&chan,sizeof(chan));
    in.read((char*)&eSiz,sizeof(eSiz));

    /* Determine type of the matrix */
    int type = 0;
    switch (eSiz){
    case sizeof(char):
         type = CV_8UC(chan);
         break;
    case sizeof(float):
         type = CV_32FC(chan);
         break;
    case sizeof(double):
         type = CV_64FC(chan);
         break;
    }

    /* Alocate Matrix. */
    M = Mat(rows,cols,type,Scalar(1));

    /* Read data. */
    if (M.isContinuous()){
       in.read((char *)M.data,cols*rows*chan*eSiz);
    }
    else{
       return 0;
    }
    in.close();
    return 1;
}