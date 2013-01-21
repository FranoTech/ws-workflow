#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <fstream>


using namespace std;
using namespace cv;

int saveMat( const std::string& filename, const Mat& M);

int main(int argc, char **argv)
{
    Mat smile = Mat(300, 300, CV_8UC1 ,Scalar::all(255));
    circle(smile, Point(75,75), 40, Scalar(0,0,0),-1);
    circle(smile, Point(225,75), 40, Scalar(0,0,0),-1);
    ellipse(smile, Point(150,220), Size(120,60), 0, 0, 360, Scalar(0,0,0),-1); 
    // ellipse(smile, Point(150,200), Size(120,40), 0, 0, 360, Scalar(255),-1); 

/*    ellipse( img,
           Point( w/2.0, w/2.0 ),
           Size( w/4.0, w/16.0 ),
           angle,
           0,
           360,
           Scalar( 255, 0, 0 ),
           thickness,
           lineType );*/

    namedWindow("smiley", CV_WINDOW_AUTOSIZE);
    imshow("smiley", smile);
    waitKey(0); 
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