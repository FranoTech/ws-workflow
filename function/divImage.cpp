#include <cv.h>
#include <highgui.h>
#include <omp.h>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    Mat src = imread(argv[1],0);
    
    Mat result[2];
    
    
    #pragma omp parallel num_threads(2)
    {
        int numt = omp_get_num_threads(); // 2
        int tid = omp_get_thread_num(); // 0,1
        int start = tid*(src.cols/numt);  //0
        int end = (tid+1)*(src.cols/numt); //3
        
        
        //cout<<"tid = "<<tid<<endl
            //<<"start = "<<start<<endl
            //<<"end = "<<end<<endl
            //<<"num thread = "<<numt<<endl
            //<<"src.cols = "<<src.cols<<endl; 

        result[tid] = src.colRange(start, end);
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
