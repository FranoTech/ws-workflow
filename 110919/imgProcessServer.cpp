//trying to transpost code to c++
//gsoap
#include "soapH.h"
#include "imgProcess.nsmap"
//opencv
#include "cv.h"
#include "highgui.h"
//STL
#include <sstream>
#include <iostream>
#include <string.h>
#include <cstring>
#include <fstream>
//system
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


//init variable
#define BASE_DIR "/home/lluu/dir/"
#define LOGNAME_SIZE 60
#define int64 long long
#define none "none"

using namespace std;
using namespace cv;
static timeval start_time, t;

//global function
//void writeToBin (char *&OutputFilename, Mat& M);
int saveMat( const char *filename, const Mat& M);
int readMat( const char *filename, Mat& M);
int getMatType (const Mat& M);

int main(int argc, char **argv)
{ 
    struct soap soap;
    soap_init(&soap);
    if (argc < 2)		// no args: assume this is a CGI application
    { 
        soap_serve(&soap);	// serve request
        soap_destroy(&soap);// cleanup class instances
        soap_end(&soap);	// cleanup
    }
    return 0;
}

/* Load image data to Mat, convert to 32FC1, save to bin */
int ns__loadMat (struct soap *soap,
                char *InputImageFilename,
                int loadparam=0,
                char **OutputMatFilename=NULL)
{
    gettimeofday(&start_time, NULL);
    Mat src;
    
	/* Determine type of the matrix */
	if(InputImageFilename){
        
        switch (loadparam){
			case 0:
                src  = imread(InputImageFilename,CV_LOAD_IMAGE_GRAYSCALE);
				break;
			case 1:
                src  = imread(InputImageFilename,CV_LOAD_IMAGE_COLOR);
				break;
			case -1:
				src  = imread(InputImageFilename,CV_LOAD_IMAGE_UNCHANGED);
				break;
			default :
				src  = imread(InputImageFilename,CV_LOAD_IMAGE_COLOR);
	    }
	    
	    if(src.empty()) {
			soap_fault(soap);
			cerr << "error :: can not load image" << endl;
			soap->fault->faultstring = "error :: can not load image";
			return SOAP_FAULT;
		}
		
    } else {
		soap_fault(soap);
		cerr << "param error" << endl;
		soap->fault->faultstring = " param error";
		return SOAP_FAULT;
	}
	
    /* convert to 32FC1 */
    Mat dst(src.rows, src.cols, CV_32FC1);
    src.convertTo(dst, CV_32FC1);
    
    
	/* generate output file name */
	*OutputMatFilename = (char*)soap_malloc(soap, 60);
    time_t now = time(0);
    strftime(*OutputMatFilename, sizeof(OutputMatFilename)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_LoadMat", localtime(&now));
	
	/* save to bin */
    if(!saveMat(*OutputMatFilename, dst))
    {
        soap_fault(soap);
        cerr << "error:: save mat to binary file" << endl;
		soap->fault->faultstring = "error:: save mat to binary file";
        return SOAP_FAULT;
    }
    
    gettimeofday(&t, NULL);
    cerr<<(int64) (t.tv_sec - start_time.tv_sec) + (t.tv_usec -start_time.tv_usec)/1000000.0<<" secs ::Ipl1ChToMat"<<endl;
    
    return SOAP_OK;
}

int ns__binaryThreshold(struct soap *soap, 
                        char *InputMatFilename, 
                        double thresholdValue=127.0, 
                        double maxValue=255.0,
                        char **OutputMatFilename=NULL)
{ 
    gettimeofday(&start_time, NULL);
	/* read from bin */
	Mat src;
	if(!readMat(InputMatFilename, src))
	    {
	        soap_fault(soap);
	        cerr << "error :: can not read bin file" << endl;
			soap->fault->faultstring = "error :: can not read bin file";
	        return SOAP_FAULT;
	    }
	
    Mat dst(src.rows, src.cols, src.depth());
    threshold(src, dst, thresholdValue, maxValue, CV_THRESH_BINARY);
    
    /* generate output file name */
	*OutputMatFilename = (char*)soap_malloc(soap, 60);
    time_t now = time(0);
    strftime(*OutputMatFilename, sizeof(OutputMatFilename)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_BinaryThreshold", localtime(&now));
	
	/* save to bin */
    if(!saveMat(*OutputMatFilename, dst))
    {
        soap_fault(soap);
        cerr << "error:: save mat to binary file" << endl;
		soap->fault->faultstring = "error:: save mat to binary file";
        return SOAP_FAULT;
    }
    
    src.release();
    dst.release();
    
    gettimeofday(&t, NULL);
    cerr<<(int64) (t.tv_sec - start_time.tv_sec) + (t.tv_usec -start_time.tv_usec)/1000000.0<<" secs ::Ipl1ChToMat"<<endl;
    
    return SOAP_OK;
}




int ns__morphOpen(  struct soap *soap, char *InputMatFilename, char **OutputMatFilename)
{ 
    gettimeofday(&start_time, NULL);
    /* read from bin */
    Mat src;
    if(!readMat(InputMatFilename, src))
        {
            soap_fault(soap);
            cerr << "error :: can not read bin file" << endl;
            soap->fault->faultstring = "error :: can not read bin file";
            return SOAP_FAULT;
        }
    
    Mat dst(src.rows, src.cols, src.depth());
    Mat se; 
    Size seSize(3, 3); 
    Point seAnc(1, 1);
    
    se = getStructuringElement(MORPH_ELLIPSE, seSize, seAnc);
    morphologyEx(src, dst, MORPH_OPEN, se, seAnc);
    
    if(src.empty()) {
			soap_fault(soap);
			cerr << "error :: morphologyEx" << endl;
			soap->fault->faultstring = "error :: morphologyEx";
			return SOAP_FAULT;
    }
    
    /* generate output file name */
    *OutputMatFilename = (char*)soap_malloc(soap, 60);
    time_t now = time(0);
    strftime(*OutputMatFilename, sizeof(OutputMatFilename)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_MorphOpen", localtime(&now));
    
    /* save to bin */
    if(!saveMat(*OutputMatFilename, src))
    {
        soap_fault(soap);
        cerr << "error:: save mat to binary file" << endl;
        soap->fault->faultstring = "error:: save mat to binary file";
        return SOAP_FAULT;
    }
    
    src.release();
    dst.release();
    se.release();
    
    gettimeofday(&t, NULL);
    cerr<<(int64) (t.tv_sec - start_time.tv_sec) + (t.tv_usec -start_time.tv_usec)/1000000.0<<" secs ::Ipl1ChToMat"<<endl;
    
    return SOAP_OK;
}

// save mat data to jpg file
// name: MatToJPG 
// @param char *InputMatFilename
// @return char *&OutputMatFilename


int ns__MatToJPG (struct soap *soap, char *InputMatFilename, char **OutputMatFilename)
{
    gettimeofday(&start_time, NULL);
    Mat src;
    if(!readMat(InputMatFilename, src))
    {
        soap_fault(soap);
        cerr << "error :: can not read bin file" << endl;
        soap->fault->faultstring = "error :: can not read bin file";
        return SOAP_FAULT;
    }
    
    int chan = src.channels();
    //convert to 8UC(n)
    if( src.type() != 0 || src.type() != 8 || src.type() != 16 )
    {
       src.convertTo(src, CV_8UC(chan));
    }
    
    /* generate output file name */
    *OutputMatFilename = (char*)soap_malloc(soap, 60);
    time_t now = time(0);
    strftime(*OutputMatFilename, sizeof(OutputMatFilename)*60, "/home/lluu/dir/%Y%m%d_%H%M%S.jpg", localtime(&now));
    
    if(!imwrite(*OutputMatFilename, src))
    {
        soap_fault(soap);
        cerr << "error :: can not save to jpg" << endl;
        soap->fault->faultstring = "error :: can not save to jpg";
        return SOAP_FAULT;
    }
    
    gettimeofday(&t, NULL);
    cerr<<(int64) (t.tv_sec - start_time.tv_sec) + (t.tv_usec -start_time.tv_usec)/1000000.0<<" secs ::Ipl1ChToMat"<<endl;
    
    return SOAP_OK;
}


// 
// name: findContoursAndFillPoly
// ** src image must be 8UC1 **
// @param	
//			-lowerbound พื้นที่น้อยสุดที่ใช้ fillPoly น้อยกว่านี้จะถูก remove
//			-InputMatFilename
// @return	
// 			-ns_FindContours out.smallerArea
//			-ns_FindContours out.biggerArea

int ns__findContoursAndFillpoly (struct soap *soap, 
						char *InputMatFilename,
						int lowerBound,
						ns__FindContours &out )
{
    
    Mat src;
    if(!readMat(InputMatFilename, src))
    {
        soap_fault(soap);
        cerr << "error :: can not read bin file" << endl;
        soap->fault->faultstring = "error :: can not read bin file";
        return SOAP_FAULT;
    }
    
    if(getMatType(src)!= CV_8UC1)
    {
        soap_fault(soap);
        cerr << "error :: FindContours support only 8uC1 images. Use convertTo function to convert image first." << endl;
        soap->fault->faultstring = "error :: FindContours support only 8uC1 images. Use convertTo function to convert image first.";
        return SOAP_FAULT;
    }
    
    
    Mat tmp = Mat(src.rows, src.cols, CV_32FC1);
    Mat outSingle = Mat::zeros(src.rows, src.cols, CV_32FC1);
	vector<vector<Point> > contours;
    findContours(	src, contours, CV_RETR_EXTERNAL, 
					CV_CHAIN_APPROX_SIMPLE, Point(0,0));
    for(size_t i = 0; i< contours.size(); i++)
    {
		const Point* p = &contours[i][0];
        int n = (int)contours[i].size();
		double area = contourArea(Mat(contours[i]));
		
		if(area < lowerBound) //lower bound
		{
			fillPoly( tmp, &p, &n, 1, Scalar(0, 0, 0)); // remove from src (put white area instead the old one)
			fillPoly(outSingle, &p, &n, 1, Scalar(255, 255, 255)); // keep small area here with black color
		}
		
	}

	contours.clear();

    /* generate output file name */
    out.smallerArea = (char*)soap_malloc(soap, 60);
    out.biggerArea = (char*)soap_malloc(soap, 60);

    time_t now = time(0);
    strftime(out.smallerArea, sizeof(out.smallerArea)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_smallerArea", localtime(&now));
    strftime(out.biggerArea, sizeof(out.biggerArea)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_biggerArea", localtime(&now));
    
    /* save to bin */
    if(!saveMat(out.smallerArea, outSingle))
    {
        soap_fault(soap);
        cerr << "error:: save mat to binary file" << endl;
        soap->fault->faultstring = "error:: save mat to binary file";
        return SOAP_FAULT;
    }
    
    if(!saveMat(out.biggerArea, tmp))
    {
        soap_fault(soap);
        cerr << "error:: save mat to binary file" << endl;
        soap->fault->faultstring = "error:: save mat to binary file";
        return SOAP_FAULT;
    }
    
    src.release();
    tmp.release();
    outSingle.release();
    
    return SOAP_OK;
}

// 
// name: ns__erode
// @param
//		- src Source image.
//		- element Structuring element used for erosion.
//		- iteration  Number of times erosion is applied.
// @return
// 		- OutputMatFilename


int ns__erode(  struct soap *soap, char *src,
				char *element,
				int iteration=1,
				char **OutputMatFilename=NULL)
{ 
	Mat matSrc;
    if(!readMat(src, matSrc))
    {
        soap_fault(soap);
        cerr << "error :: can not read bin file" << endl;
        soap->fault->faultstring = "error :: can not read bin file";
        return SOAP_FAULT;
    }
    
    Mat dst;
    Mat matElement;
    
    if(!readMat(element, matElement))
    {
		cerr<<"erode: use default element"<<endl;
        matElement.release();
        erode(matSrc, dst, Mat(), Point(-1, -1), iteration);
    } else {
		cerr<<"erode: use defined element"<<endl;
        erode(matSrc, dst, matElement, Point(-1, -1), iteration);
    }
    
    /* generate output file name */
    *OutputMatFilename = (char*)soap_malloc(soap, 60);
    time_t now = time(0);
    strftime(*OutputMatFilename, sizeof(OutputMatFilename)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_erode", localtime(&now));
    
    /* save to bin */
    if(!saveMat(*OutputMatFilename, matSrc))
    {
        soap_fault(soap);
        cerr << "error:: save mat to binary file" << endl;
        soap->fault->faultstring = "error:: save mat to binary file";
        return SOAP_FAULT;
    }
    
    matSrc.release();
    dst.release();
    matElement.release();
    
    return SOAP_OK;
}


// 
// name: ns__dilate
// @param
//		- src Source image.
//		- element Structuring element used for dilation.
//		- iteration  Number of times erosion is applied.
// @return
// 		- OutputMatFilename


int ns__dilate(  struct soap *soap, char *src,
				char *element,
				int iteration=1,
				char **OutputMatFilename=NULL)
{ 
	Mat matSrc;
    if(!readMat(src, matSrc))
    {
        soap_fault(soap);
        cerr << "error :: can not read bin file" << endl;
        soap->fault->faultstring = "error :: can not read bin file";
        return SOAP_FAULT;
    }
    
    Mat dst;
    Mat matElement;
    
    if(!readMat(element, matElement))
    {
		cerr<<"erode: use default element"<<endl;
        matElement.release();
        dilate(matSrc, dst, Mat(), Point(-1, -1), iteration);
    } else {
		cerr<<"erode: use defined element"<<endl;
        dilate(matSrc, dst, matElement, Point(-1, -1), iteration);
    }
    
    /* generate output file name */
    *OutputMatFilename = (char*)soap_malloc(soap, 60);
    time_t now = time(0);
    strftime(*OutputMatFilename, sizeof(OutputMatFilename)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_dilate", localtime(&now));
    
    /* save to bin */
    if(!saveMat(*OutputMatFilename, matSrc))
    {
        soap_fault(soap);
        cerr << "error:: save mat to binary file" << endl;
        soap->fault->faultstring = "error:: save mat to binary file";
        return SOAP_FAULT;
    }
    
    matSrc.release();
    dst.release();
    matElement.release();
    
    return SOAP_OK;
}



int ns__Or(  struct soap *soap, char *src1,
				char *src2,
				char **OutputMatFilename)
{ 
	Mat matSrc1;
    if(!readMat(src1, matSrc1))
    {
        soap_fault(soap);
        cerr << "error :: can not read bin file" << endl;
        soap->fault->faultstring = "error :: can not read bin file";
        return SOAP_FAULT;
    }

    Mat matSrc2; 
    if(!readMat(src2, matSrc2))
    {
		soap_fault(soap);
        cerr << "error :: can not read bin file" << endl;
        soap->fault->faultstring = "error :: can not read bin file";
    }
    
    if(matSrc1.type() != matSrc2.type()){
		matSrc2.convertTo(matSrc2, matSrc1.type());
	}
    
    Mat dst;
    bitwise_or(matSrc1, matSrc2, dst);
    
    /* generate output file name */
    *OutputMatFilename = (char*)soap_malloc(soap, 60);
    time_t now = time(0);
    strftime(*OutputMatFilename, sizeof(OutputMatFilename)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_or", localtime(&now));
    
    /* save to bin */
    if(!saveMat(*OutputMatFilename, dst))
    {
        soap_fault(soap);
        cerr << "error:: save mat to binary file" << endl;
        soap->fault->faultstring = "error:: save mat to binary file";
        return SOAP_FAULT;
    }
    
    matSrc1.release();
    matSrc2.release();
    dst.release();
    
    return SOAP_OK;
}




int ns__And(  struct soap *soap, char *src1,
				char *src2,
				char **OutputMatFilename)
{ 
	Mat matSrc1;
    if(!readMat(src1, matSrc1))
    {
        soap_fault(soap);
        cerr << "error :: can not read bin file" << endl;
        soap->fault->faultstring = "error :: can not read bin file";
        return SOAP_FAULT;
    }

    Mat matSrc2; 
    if(!readMat(src2, matSrc2))
    {
		soap_fault(soap);
        cerr << "error :: can not read bin file" << endl;
        soap->fault->faultstring = "error :: can not read bin file";
    }
    
    if(matSrc1.type() != matSrc2.type()){
		matSrc2.convertTo(matSrc2, matSrc1.type());
	}
    
    Mat dst;
    bitwise_and(matSrc1, matSrc2, dst);
    
    /* generate output file name */
    *OutputMatFilename = (char*)soap_malloc(soap, 60);
    time_t now = time(0);
    strftime(*OutputMatFilename, sizeof(OutputMatFilename)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_and", localtime(&now));
    
    /* save to bin */
    if(!saveMat(*OutputMatFilename, dst))
    {
        soap_fault(soap);
        cerr << "error:: save mat to binary file" << endl;
        soap->fault->faultstring = "error:: save mat to binary file";
        return SOAP_FAULT;
    }
    
    matSrc1.release();
    matSrc2.release();
    dst.release();
    
    return SOAP_OK;
}



int ns__Not(  struct soap *soap, char *src,
			  char **OutputMatFilename)
{ 
	Mat matSrc;
    if(!readMat(src, matSrc))
    {
        soap_fault(soap);
        cerr << "error :: can not read bin file" << endl;
        soap->fault->faultstring = "error :: can not read bin file";
        return SOAP_FAULT;
    }
    
    Mat dst;
    bitwise_not(matSrc, dst);
    
    /* generate output file name */
    *OutputMatFilename = (char*)soap_malloc(soap, 60);
    time_t now = time(0);
    strftime(*OutputMatFilename, sizeof(OutputMatFilename)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_not", localtime(&now));
    
    /* save to bin */
    if(!saveMat(*OutputMatFilename, dst))
    {
        soap_fault(soap);
        cerr << "error:: save mat to binary file" << endl;
        soap->fault->faultstring = "error:: save mat to binary file";
        return SOAP_FAULT;
    }
    
    matSrc.release();
    dst.release();
    
    
    return SOAP_OK;
}


// src must be binary image

int ns__removeSmallCell(struct soap *soap, 
						char *inputMatFilename,
						ns__RemoveSmallCell &out)
{ 
    gettimeofday(&start_time, NULL);
    //src type must be 8UC1
	Mat src;
    if(!readMat(inputMatFilename, src))
    {
        soap_fault(soap);
        cerr << "error :: can not read bin file" << endl;
        soap->fault->faultstring = "error :: can not read bin file";
        return SOAP_FAULT;
    }
    
    Mat tmp = Mat(src.rows, src.cols, CV_32FC1);
    //src.convertTo(tmp, CV_32FC1);
    
    if( src.type() != CV_8UC1)
    {
        src.convertTo(src, CV_8UC1);
    }

    Mat outSingle = Mat::zeros(src.rows, src.cols, CV_32FC1); //black plain
	vector<vector<Point> > contours;
    //findContours(	src, contours, CV_RETR_EXTERNAL, 
					//CV_CHAIN_APPROX_SIMPLE, Point(0,0));
                    
    vector<Vec4i> hierarchy;
    double area = 0;
    findContours( src, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);                
                    
    for(size_t i = 0; i< contours.size(); i++)
    {
		const Point* p = &contours[i][0];
        int n = (int)contours[i].size();
		area = contourArea(Mat(contours[i]));
		
		if(area < 1500.0) //lower bound
		{
			fillPoly( tmp, &p, &n, 1, Scalar(255, 255, 255)); // remove from src (put black area instead the old one)
			
		} else if (area < 7500.0) {
			fillPoly(outSingle, &p, &n, 1, Scalar(255, 255, 255)); // keep small area here with white color
			fillPoly( tmp, &p, &n, 1, Scalar(255, 255, 255)); // remove from src
			
		} else {
			fillPoly( tmp, &p, &n, 1, Scalar(0, 0, 0)); //left the bigger area in src
			
		}
	}

	contours.clear();
    hierarchy.clear();
	
	/* generate output file name */
    out.keepedArea = (char*)soap_malloc(soap, 60);
    out.biggerArea = (char*)soap_malloc(soap, 60);

    time_t now = time(0);
    strftime(out.keepedArea, sizeof(out.keepedArea)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_keepedArea", localtime(&now));
    strftime(out.biggerArea, sizeof(out.biggerArea)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_biggerArea", localtime(&now));
    
    /* save to bin */
    if(!saveMat(out.keepedArea, outSingle))
    {
        soap_fault(soap);
        cerr << "error:: save mat to binary file" << endl;
        soap->fault->faultstring = "error:: save mat to binary file";
        return SOAP_FAULT;
    }
    
    if(!saveMat(out.biggerArea, tmp))
    {
        soap_fault(soap);
        cerr << "error:: save mat to binary file" << endl;
        soap->fault->faultstring = "error:: save mat to binary file";
        return SOAP_FAULT;
    }
    
    gettimeofday(&t, NULL);
    cerr<<(int64) (t.tv_sec - start_time.tv_sec) + (t.tv_usec -start_time.tv_usec)/1000000.0<<" secs ::Ipl1ChToMat"<<endl;
    return SOAP_OK;
}


//call after removeSmallCell
//input is *Bigger area*

int ns__scanningCell(struct soap *soap, 
						char *inputMatFilename,
						char **outputMatFilename)
{ 
    gettimeofday(&start_time, NULL);
	Mat src;
    if(!readMat(inputMatFilename, src))
    {
        soap_fault(soap);
        cerr << "error :: can not read bin file" << endl;
        soap->fault->faultstring = "error :: can not read bin file";
        return SOAP_FAULT;
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

	/* generate output file name */
    *outputMatFilename = (char*)soap_malloc(soap, 60);

    time_t now = time(0);
    strftime(*outputMatFilename, sizeof(outputMatFilename)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_scaningCell", localtime(&now));
    
    /* save to bin */
    if(!saveMat(*outputMatFilename, output))
    {
        soap_fault(soap);
        cerr << "error:: save mat to binary file" << endl;
        soap->fault->faultstring = "error:: save mat to binary file";
        return SOAP_FAULT;
    }
    
    gettimeofday(&t, NULL);
    cerr<<(int64) (t.tv_sec - start_time.tv_sec) + (t.tv_usec -start_time.tv_usec)/1000000.0<<" secs ::Ipl1ChToMat"<<endl;
    
    return SOAP_OK;
}

/*to do list 
int ns__convertTo( struct soap *soap, char *inputMatFilename, 
                    char **outputMatFilename)
{

}

*/


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



