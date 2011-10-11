//worked!!
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
    
    Mat src  = imread(argv[1],0);
    
    //Mat input3Ch(src.rows, src.cols, CV_32FC3);
    //Mat output1Ch;
    Mat input_morph(src.rows, src.cols, CV_32FC1);
    
    threshold(src, input_morph, 127.0, 255.0, CV_THRESH_BINARY);
    input_morph.convertTo(input_morph, CV_32FC1);
    
    Mat se; 
    Size seSize(3, 3);
    Point seAnc(1, 1);
    
    se = getStructuringElement(MORPH_ELLIPSE, seSize, seAnc);
    morphologyEx(input_morph, input_morph, MORPH_OPEN, se, seAnc);

    Mat out_single = Mat::zeros(input_morph.rows, input_morph.cols, CV_32FC1);
    Mat tmp8UC1(src.rows, src.cols, CV_8UC1);
    input_morph.convertTo(tmp8UC1, CV_8UC1);
    
    
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    double area = 0;
    findContours( tmp8UC1, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
    for(size_t i = 0; i< contours.size(); i++)
    {
		const Point* p = &contours[i][0];
        int n = (int)contours[i].size();
		area = contourArea(Mat(contours[i]));
		
		if(area < 1500.0) //lower bound
		{
			fillPoly( input_morph, &p, &n, 1, Scalar(0, 0, 0));
		} else if (area < 7500.0) {
            fillPoly( out_single, &p, &n, 1, Scalar(255,255,255)); // move to result
            fillPoly( input_morph, &p, &n, 1, Scalar(0, 0, 0)); // remove from input
        }else{
			fillPoly( input_morph, &p, &n, 1, Scalar(255,255,255));
		}
	}

   Mat output_morph = Mat(input_morph.rows, input_morph.cols, CV_32FC1);
   cout<<"input_morph = "<<input_morph.type()<<endl;
   cout<<"out_single = "<<out_single.type()<<endl;
   cout<<"output_morph = "<<output_morph.type()<<endl;
   bitwise_or(input_morph, out_single, output_morph);
   
    int nContour = 1;
    int prevContour = 0;
    int sameCount = 0;
    area = 0;                                                                                                                                                                                                                                                                                                                                                                                                                                    0;
    contours.clear();
    hierarchy.clear();
    
    while(nContour != 0)
    {
        input_morph.convertTo(tmp8UC1, CV_8UC1);

        findContours( tmp8UC1, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
        nContour = contours.size();
        
        if( nContour == 0){ break; }
        if( nContour == prevContour ){ 
            erode( input_morph, input_morph, Mat() );
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
                fillPoly( input_morph, &p, &n, 1, Scalar(0, 0, 0)); // remove from src 
                fillPoly( out_single, &p, &n, 1, Scalar(255, 255, 255)); 
            }
        }
    }
    
	if(!saveMat("keepArea", out_single)){
		cout<<"can not save mat"<<endl;
	}
	
	if(!saveMat("bigArea", input_morph)){
		cout<<"can not save mat"<<endl;
	}
    
	if(!saveMat("orArea", output_morph)){
		cout<<"can not save mat"<<endl;
	}
    
    contours.clear();
    src.release();
    out_single.release();
    input_morph.release();
    tmp8UC1.release();
    
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



