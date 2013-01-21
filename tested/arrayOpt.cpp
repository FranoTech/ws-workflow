// /home/lluu/thesis/result/20121230_155237_add

#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <fstream>
#include <string.h>


using namespace std;
using namespace cv;

int saveMat( const std::string& filename, const Mat& M);

int main(int argc, char **argv)
{

	Mat input1;
    Mat input2;
    Mat dst;

    input1 = imread(argv[1],0);
    input2 = imread(argv[2],0);

    if(!input1.data)
    {
		std::cout<<"Can not open image file to test"<<std::endl;
    }

    if(!input2.data)
    {
		std::cout<<"Can not open image file to test"<<std::endl;
    }


    try{
    		add(input2, input1, dst);

    } catch( cv::Exception& e ) {
        std::cout << e.what() << std::endl;
    }

    namedWindow("RB", CV_WINDOW_AUTOSIZE);
    imshow("RB", dst);
    waitKey(0); 	
	
	std::string fname = "arrayOpt_result";
    if(!saveMat(fname, dst))
    {
        std::cout<<"save error"<<std::endl;
    }
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