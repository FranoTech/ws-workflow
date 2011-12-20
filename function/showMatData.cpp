#include <iostream>
#include <fstream>
#include <cv.h>
#include <highgui.h>

using namespace std;
using namespace cv;

int main (int argc, char** argv){
    
    Mat src  = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    cout << "src = " << endl << " " << src << endl << endl;
    
    src.release();
    return 0;
}
    
