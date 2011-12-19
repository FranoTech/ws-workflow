#include <cv.h>
#include <highgui.h>
#include <omp.h>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    Mat src = imread(argv[1],0);
    //~ Mat dst = Mat(src.rows, src.cols, src.type());
    
    //~ Mat divSrc[4];
    int cols = src.cols;
    int rows = src.rows;
    Mat divSrc[2];
    Mat tmp[2];
    
    #pragma omp parallel shared(src) num_threads(2)
    {
        int numt = omp_get_num_threads();       // 2
        int tid = omp_get_thread_num();         // 0,1
        int start = tid*(src.rows/numt); //t0 = 0  t1 = 3
        int end = (tid+1)*(src.rows/numt);// t0 = 3 t1 = 6
        if( tid == (numt-1) )
        {
            end = src.rows;
        }
            
        divSrc[tid] = src.rowRange(start, end);
        tmp[tid] = src.rowRange(start, end);
        divSrc[tid].convertTo(divSrc[tid],CV_32FC1);
        tmp[tid] = divSrc[tid].clone();
        cout<<"tmp ["<<tid<<"] = "<<tmp[tid].type()<<endl;
        cout<<"divSrc ["<<tid<<"] = "<<divSrc[tid].type()<<endl;
        
        //~ threshold(divSrc[tid], divSrc[tid], 127.0, 255.0, THRESH_BINARY);
        //~ threshold(divSrc, divSrc, 127.0, 255.0, THRESH_BINARY);
        
    }

    cout<<"src = "<<src.type()<<endl;
    //~ cout<<dst.type();
    //~ src.convertTo(src, CV_8UC1);
    //~ if(!imwrite("divomp.jpg", src))
    //~ {
        //~ cout<<"write error"<<endl;
    //~ }
    
    //~ namedWindow("src1", CV_WINDOW_AUTOSIZE);
    //~ imshow("src1", src);
    //~ 
    //~ namedWindow("src2", CV_WINDOW_AUTOSIZE);
    //~ imshow("src2", result[0]);
//~ 
    //~ namedWindow("src3", CV_WINDOW_AUTOSIZE);
    //~ imshow("src3", result[1]);
    
    src.release();
 
    return 0;
}
