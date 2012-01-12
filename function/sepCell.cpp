#include <iostream>
#include <fstream>
#include <cv.h>
#include <highgui.h>
#include <time.h>   

using namespace std;
using namespace cv;

int readMat( const char *filename, Mat& M);

int main (int argc, char** argv){
    
    Mat outSingle; //out_single
    if(!readMat("outSingle", outSingle))
    {
        cerr << "sep :: can not read bin file" << endl;
    }
    
    if( outSingle.type() != CV_8UC1)
    {
        outSingle.convertTo(outSingle, CV_8UC1);
    }
    
    Mat tmp;
    int count = 1;
	vector<vector<Point> > contours;
    findContours(	outSingle, contours, CV_RETR_EXTERNAL,
					CV_CHAIN_APPROX_SIMPLE, Point(0,0));
    
    for(size_t i = 0; i< contours.size(); i++)
    {
		const Point* p = &contours[i][0];
        int n = (int)contours[i].size();
        int c = ((count+1)%254)+1;
        fillPoly( tmp, &p, &n, 1, Scalar::all(((count+1)%254)+1)); 
	}
	contours.clear();

    Mat cell; //output_morph
    if(!readMat("outputMorph", cell))
    {
        cerr << "sepl :: can not read bin file" << endl;
    }
    
    Mat inwater = Mat(outSingle.rows, outSingle.cols, CV_8UC3);
    Mat outwater(outSingle.size(),CV_32SC1,outSingle.data);  //Is it correct?
    
    Mat tmp8UC1;
    cell.convertTo(tmp8UC1,CV_8UC1);

    vector<Mat> water;
    tmp8UC1.copyTo(water[0]);
    tmp8UC1.copyTo(water[1]);
    tmp8UC1.copyTo(water[2]);
    
    merge(water, inwater);
    watershed(inwater, outwater);
    erode(outSingle, outSingle, NULL, 2);
    cell.convertTo(tmp8UC1,CV_8UC1);
    subtract(cell, outSingle, cell, tmp8UC1);
    
    if(!imwrite("result_sepCell.jpg", cell))
    {
        cerr<< "can not save mat to jpg file" << endl;
    }
    
    
    tmp8UC1.release();
    cell.release();
    outSingle.release();
    
    return 0;
}

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
