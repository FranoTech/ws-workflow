#include <cv.h>
#include <highgui.h>
#include <iostream>


using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    Mat src = imread(argv[1],0);
    std::cout<<src;
    
    src.release();
 
    return 0;
}
