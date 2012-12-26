#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <fstream>


using namespace std;
using namespace cv;

int saveMat( const std::string& filename, const Mat& M);

int main(int argc, char **argv)
{
    Mat src = imread(argv[1],0);
    threshold(src,src,60.0,255.0,cv::THRESH_BINARY);
    std::string fname = "result";
    if(!saveMat(fname, src))
    {
        std::cout<<"save error"<<std::endl;
    }
    src.release();
 
    return 0;
}


int saveMat( const std::string& filename, const Mat& M){
    if (M.empty()){
       return 0;
    }
    std::ofstream out(filename.c_str(), std::ios::out|std::ios::binary);
    if (!out)
       return 0;

    int cols = M.cols;
    int rows = M.rows;
    int chan = M.channels();
    int eSiz = (M.dataend-M.datastart)/(cols*rows*chan);

    /* Write header */
    out.write((char*)&cols,sizeof(cols));
    out.write((char*)&rows,sizeof(rows));
    out.write((char*)&chan,sizeof(chan));
    out.write((char*)&eSiz,sizeof(eSiz));

    /* Write data. */
    if (M.isContinuous()){
       out.write((char *)M.data,cols*rows*chan*eSiz);
    }
    else{
        std::cout << "saveMat :: Mat is empty" << std::endl;
       return 0;
    }
    out.close();
    return 1;
}