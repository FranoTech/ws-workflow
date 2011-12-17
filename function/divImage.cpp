#include <cv.h>
#include <highgui.h>
#include <omp.h>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    Mat src = imread(argv[1],0);
    
    //~ Mat divSrc[4];
    #pragma omp parallel shared(src) num_threads(2)
    {
        int numt = omp_get_num_threads();       // 2
        int tid = omp_get_thread_num();         // 0,1
        int start = tid*(src.cols/numt); //t0 = 0  t1 = 3
        int end = (tid+1)*(src.cols/numt);// t0 = 3 t1 = 6
        if( tid == (numt-1) )
        {
            end = src.cols;
        }

        cout<<"tid = "<<tid<<endl
            <<"start = "<<start<<endl
            <<"end = "<<end<<endl
            <<"num thread = "<<numt<<endl
            <<"src.cols = "<<src.cols<<endl; 
            
        Mat divSrc = src.colRange(start, end);
        
        //~ threshold(divSrc[tid], divSrc[tid], 127.0, 255.0, THRESH_BINARY);
        threshold(divSrc, divSrc, 127.0, 255.0, THRESH_BINARY);
        
    }
    src.convertTo(src, CV_8UC1);
    if(!imwrite("divomp.jpg", src))
    {
        cout<<"write error"<<endl;
    }
    
    //~ namedWindow("src1", CV_WINDOW_AUTOSIZE);
    //~ imshow("src1", src);
    
    //~ namedWindow("src2", CV_WINDOW_AUTOSIZE);
    //~ imshow("src2", result[0]);
//~ 
    //~ namedWindow("src3", CV_WINDOW_AUTOSIZE);
    //~ imshow("src3", result[1]);
    
    src.release();
 
    return 0;
}
