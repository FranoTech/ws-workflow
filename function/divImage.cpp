#include <cv.h>
#include <highgui.h>
#include <omp.h>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    Mat src = imread(argv[1],0);
    
    //vector<Mat> result;
    Mat divSrc[4];
    Mat result[4];
    
    #pragma omp parallel num_threads(4)
    {
        int numt = omp_get_num_threads();       // 2
        int tid = omp_get_thread_num();         // 0,1
        int start;
        if(tid == 0) 
        {                                       //prevent duplicated data
            start = tid*(src.cols/numt);        // let's tid[0] start at col[0]
        } else {
            start = (tid*(src.cols/numt))+1;    //others start at col[x+1] 
        }
        int end = (tid+1)*(src.cols/numt);      //3
        
        
        cout<<"tid = "<<tid<<endl
            <<"start = "<<start<<endl
            <<"end = "<<end<<endl
            <<"num thread = "<<numt<<endl
            <<"src.cols = "<<src.cols<<endl; 
            
        divSrc[tid] = src.colRange(start, end);
        threshold(divSrc[tid], result[tid], 127.0, 255.0, THRESH_BINARY);
        
    }
    
    namedWindow("src1", CV_WINDOW_AUTOSIZE);
    imshow("src1", src);
    
    namedWindow("src2", CV_WINDOW_AUTOSIZE);
    imshow("src2", result[0]);

    namedWindow("src3", CV_WINDOW_AUTOSIZE);
    imshow("src3", result[1]);
    waitKey(0);
 
    return 0;
}
