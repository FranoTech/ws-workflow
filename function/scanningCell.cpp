#include <iostream>
#include <fstream>
#include <cv.h>
#include <highgui.h>

using namespace std;
using namespace cv;
int saveMat( const char *filename, const Mat& M);
int readMat( const char *filename, Mat& M);
int getMatType (const Mat& M);


int main (int argc, char** argv){
    
    Mat src;
	if(!readMat(argv[1], src)){
			cout<<"can't read image"<<endl;
    }
    
    if( src.type() != 0){
		src.convertTo(src, CV_8UC1);
	}

    Mat srcTmp;
    Mat src32FC1;
    src.convertTo(src32FC1, CV_32FC1);
    Mat output = Mat::zeros(src.rows,src.cols, CV_32FC1);
    
    int nContour = 1;
    int prevContour = 0;
    int sameCount = 0;
    double area = 0;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    
    
    while(nContour != 0)
    {
        src32FC1.convertTo(srcTmp, CV_8UC1);

        findContours( srcTmp, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
        nContour = contours.size();
        
        if( nContour == 0){ break; }
        if( nContour == prevContour ){ 
            erode( src32FC1, src32FC1, Mat() );
            sameCount++;
        }else {
            sameCount = 0;
        }
        
        prevContour = nContour;
        
        for(size_t i = 0; i< contours.size(); i++)
        {
            const Point* p = &contours[i][0];
            int n = (int)contours[i].size();
            area = contourArea(Mat(contours[i]));
            
            if((area < 3000.0) || (sameCount > 10))
            {
                fillPoly( src32FC1, &p, &n, 1, Scalar(0, 0, 0)); // remove from src 
                fillPoly( output, &p, &n, 1, Scalar(255, 255, 255)); 
            }
        }
    }
    
    if(!saveMat("src32FC1", src32FC1)){
		cout<<"can not save mat"<<endl;
	}
	
	if(!saveMat("output_scan", output)){
		cout<<"can not save mat"<<endl;
	}
    
	contours.clear();
    hierarchy.clear();
    src.release();
    srcTmp.release();
    src32FC1.release();
    output.release();
    
    
    return 0;
}


/* helper function */
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

int getMatType ( const Mat& M)
{
	int type = 0;
    int chan = M.channels();
    int eSiz = (M.dataend-M.datastart)/(M.cols*M.rows*chan);
    
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
    
    return type;
}


