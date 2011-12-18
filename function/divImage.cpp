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
    
    #pragma omp parallel shared(src) num_threads(2)
    {
        int numt = omp_get_num_threads();       // 2
        int tid = omp_get_thread_num();
        int colsOI = cols/numt; 
        int x = 0;
        int y = tid*(cols/2);
        Mat ROI = src(Rect(x, y, colsOI, rows));
        
        ROI.convertTo(ROI,CV_8UC1);
        
        //~ Mat img1,img2; //They are previously declared and of the same width & height
//~ 
//~ Mat imgResult(img1.rows,2*img1.cols,img1.type); // Your final image
//~ 
//~ Mat roiImgResult_Left = imgResult(Rect(0,0,img1.cols,img1.rows); //Img1 will be on the left part
//~ Mat roiImgResult_Right = imgResult(Rect(img1.cols,0,img2.cols,img2.rows); //Img2 will be on the right part, we shift the roi of img1.cols on the right
//~ 
//~ Mat roiImg1 = img1(Rect(0,0,img1.cols,img1.rows));
//~ Mat roiImg2 = img2(Rect(0,0,img2.cols,img2.rows));
//~ 
//~ roiImg1.copyTo(roiImgResult_Left); //Img1 will be on the left of imgResult
//~ roiImg2.copyTo(roiImgResult_Right); //Img2 will be on the right of imgResult
        
        //~ int numt = omp_get_num_threads();       // 2
        //~ int tid = omp_get_thread_num();         // 0,1
        //~ int start = tid*(src.rows/numt); //t0 = 0  t1 = 3
        //~ int end = (tid+1)*(src.rows/numt);// t0 = 3 t1 = 6
        //~ if( tid == (numt-1) )
        //~ {
            //~ end = src.rows;
        //~ }
//~ 
        //~ cout<<"tid = "<<tid<<endl
            //~ <<"start = "<<start<<endl
            //~ <<"end = "<<end<<endl
            //~ <<"num thread = "<<numt<<endl
            //~ <<"src.rows = "<<src.rows<<endl; 
            //~ 
        //~ Mat divSrc = src.rowRange(start, end);
        //~ Mat d = dst.rowRange(start,end);
        //~ 
        //~ divSrc.convertTo(d,CV_32FC1);
        
        //~ threshold(divSrc[tid], divSrc[tid], 127.0, 255.0, THRESH_BINARY);
        //~ threshold(divSrc, divSrc, 127.0, 255.0, THRESH_BINARY);
        
    }
    
    cout<<src.type();
    //~ cout<<dst.type();
    //~ src.convertTo(src, CV_8UC1);
    //~ if(!imwrite("divomp.jpg", src))
    //~ {
        //~ cout<<"write error"<<endl;
    //~ }
    
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
