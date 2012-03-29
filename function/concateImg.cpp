#include <iostream>
#include <fstream>
#include <cv.h>
#include <ml.h>

using namespace std;
using namespace cv;

int main (int argc, char** argv)
{
    Mat lu = imread(argv[1],0);
    Mat ru = imread(argv[2],0);
    Mat ld = imread(argv[3],0);
    Mat rd = imread(argv[4],0);
    
    int sum_rows = lu.rows*2;
    int sum_cols = lu.cols*2;
     
    Mat sum(sum_rows, sum_cols, lu.type());
    
    Mat roi1(sum,Rect(0, 0, lu.cols, lu.rows));
    Mat roi2(sum,Rect(lu.cols, 0, ru.cols, ru.rows));
    Mat roi3(sum,Rect(0, lu.rows, ld.cols, ld.rows));
    Mat roi4(sum,Rect(ld.cols, ru.rows, rd.cols, rd.rows));
    
    lu.copyTo(roi1);
    ru.copyTo(roi2);
    ld.copyTo(roi3);
    rd.copyTo(roi4);
    
    imshow("sum", sum);
    
    waitKey(0);
    
    return 0;
}
