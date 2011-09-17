#include <iostream>
#include <fstream>
#include <cv.h>
#include <highgui.h>

using namespace std;
using namespace cv;
int saveMat( string& filename, const Mat& M);
int readMat( const string& filename, Mat& M);

int main (int argc, char** argv){
    
    Mat src  = imread(argv[1],0);
    Mat gray;
    Mat result();
    threshold(src, gray, 127.0, 255.0, CV_THRESH_BINARY);
    
    vector<vector<Point> > contours;
    findContours(gray, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0,0));
    for(size_t i = 0; i< contours.size(); i++)
    {
		//const Point* ppt[1] = {Point(contours[0])}; // fail
		const Point* p = &contours[i][0];
        int n = (int)contours[i].size();
		double area = contourArea(Mat(contours[i]));
		
		if(area < 100.0)
		{
			fillPoly( result, &p, &n, 1, Scalar(255,255,255));
			cout<<"***************passed************"<<endl;
		 //} else if (area < 1500.0) {
            //fillPoly(gray, contours, contours.size(), 1, Scalar(0,0,255)); // move to single
             //// remove from input
        //}else{
			//fillPoly(gray, contours, contours.size(), 1, Scalar(255,0,0));
		}
	}
	
    
    namedWindow("result", CV_WINDOW_AUTOSIZE);
    imshow("result", src);
    waitKey(0);
    
    namedWindow("result", CV_WINDOW_AUTOSIZE);
    imshow("result", result);
    waitKey(0);
    
    src.release();
    gray.release();
    
    return 0;
}


/* Save matrix to binary file */
int saveMat( const char *filename, const Mat& M){
    if (M.empty()){
       return 0;
    }
    ofstream out(filename, ios::out|ios::binary);
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
       return 0;
    }
    out.close();
    return 1;
}



/* Read matrix from binary file */
int readMat( const char *filename, Mat& M)
{    
    ifstream in(filename, ios::in|ios::binary);
    if (!in){
       M.data = NULL;
       return 0;
    }
    int cols;
    int rows;
    int chan;
    int eSiz;

    /* Read header */
    in.read((char*)&cols,sizeof(cols));
    in.read((char*)&rows,sizeof(rows));
    in.read((char*)&chan,sizeof(chan));
    in.read((char*)&eSiz,sizeof(eSiz));

    /* Determine type of the matrix */
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

    /* Alocate Matrix. */
    M = Mat(rows,cols,type,Scalar(1));  

    /* Read data. */
    if (M.isContinuous()){
       in.read((char *)M.data,cols*rows*chan*eSiz);
    }
    else{
       return 0;
    }
    in.close();
    return 1;
} 


