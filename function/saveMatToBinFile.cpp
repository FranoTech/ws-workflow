#include <iostream>
#include <fstream>
//#include <cv.hpp>
#include <cv.h>
#include <highgui.h>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;
int saveMat( string& filename, const Mat& M);
int readMat( const string& filename, Mat& M);

int main (int argc, char** argv){
    
    Mat im_rgb  = imread(argv[1],0);
    Mat im_gray;
    //cvtColor( im_rgb, im_gray, CV_RGB2GRAY );
    
    threshold(im_rgb, im_gray, 127.0, 255.0, CV_THRESH_BINARY);
    
    string filename = "test";
    
    if(!saveMat(filename,im_gray))
    {
        cout<<"save error"<<endl;
    }
    
    Mat from_read;
    
    if(!readMat("test123",from_read))
    {
        cout<<"read error"<<endl;
    }
    
    namedWindow("result", CV_WINDOW_AUTOSIZE);
    imshow("result", from_read);
    waitKey(0);
    
    im_gray.release();
    im_rgb.release();
    from_read.release();

    return 0;
}

// Save matrix to binary file
int saveMat( string& filename, const Mat& M){
    
    filename = "test123";
    
    if (M.empty()){
       return 0;
    }
    ofstream out(filename.c_str(), ios::out|ios::binary);
    if (!out)
       return 0;

    int cols = M.cols;
    int rows = M.rows;
    int chan = M.channels();
    int eSiz = (M.dataend-M.datastart)/(cols*rows*chan);

    // Write header
    out.write((char*)&cols,sizeof(cols));
    out.write((char*)&rows,sizeof(rows));
    out.write((char*)&chan,sizeof(chan));
    out.write((char*)&eSiz,sizeof(eSiz));

    // Write data.
    if (M.isContinuous()){
       out.write((char *)M.data,cols*rows*chan*eSiz);
    }
    else{
       return 0;
    }
    out.close();
    return 1;
}

// Read matrix from binary file
int readMat( const string& filename, Mat& M)
{    
    ifstream in(filename.c_str(), ios::in|ios::binary);
    if (!in){
       M.data = NULL;
       return 0;
    }
    int cols;
    int rows;
    int chan;
    int eSiz;

    // Read header
    in.read((char*)&cols,sizeof(cols));
    in.read((char*)&rows,sizeof(rows));
    in.read((char*)&chan,sizeof(chan));
    in.read((char*)&eSiz,sizeof(eSiz));

    // Determine type of the matrix 
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

    // Alocate Matrix.
    M = Mat(rows,cols,type,Scalar(1));  

    // Read data.
    if (M.isContinuous()){
       in.read((char *)M.data,cols*rows*chan*eSiz);
    }
    else{
       return 0;
    }
    in.close();
    return 1;
} 
