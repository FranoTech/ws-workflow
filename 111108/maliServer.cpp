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
#include <sys/stat.h> //time_t fstat
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
//omp
#include <omp.h>


//init variable
#define BASE_DIR "/home/lluu/dir/"
#define FILENAME_SIZE 60
#define int64 long long

//namespace
using namespace std;
using namespace cv;

//helper function
int saveMat( const char *filename, const Mat& M);
int readMat( const char *filename, Mat& M);
int getMatType (const char *typeName);
int getThresholdType ( const char *typeName);
int getColorFlag(int colorflag);


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


/* Load image data to Mat, save to binary file */
int ns__loadMat (struct soap *soap,
                char *InputImageFilename,
                int colorflag=0,
                char *types="CV_32FC1",
                char **OutputMatFilename=NULL)
{
    double start, end; 
    start = omp_get_wtime();

    Mat src;
    /* load image data */
	if(InputImageFilename){
	    
        src = imread(InputImageFilename,getColorFlag(colorflag));
	    if(src.empty()) {
			soap_fault(soap);
			cerr<<"loadMat:: can not load image" << endl;
			soap->fault->faultstring = "error :: can not load image";
			return SOAP_FAULT;
		}
        
        if(src.type()!= getMatType(types))
        {
            src.convertTo(src,getMatType(types));
        }
    } else {
		soap_fault(soap);
		cerr<<"loadMat:: InputImageFilename error" << endl;
		soap->fault->faultstring = "loadMat:: InputImageFilename error";
		return SOAP_FAULT;
	}
    
	/* generate output file name */
	*OutputMatFilename = (char*)soap_malloc(soap, FILENAME_SIZE);
    time_t now = time(0);
    strftime(*OutputMatFilename, sizeof(OutputMatFilename)*FILENAME_SIZE, "/home/lluu/dir/%Y%m%d_%H%M%S_LoadMat", localtime(&now));
	
	/* save to bin */
    if(!saveMat(*OutputMatFilename, src))
    {
        soap_fault(soap);
        cerr<<"loadMat:: can not save mat to binary file" << endl;
		soap->fault->faultstring = "error:: can not save mat to binary file";
        return SOAP_FAULT;
    }
    
    src.release();
    
    end = omp_get_wtime();
    cerr<<"ns__loadMat "<<"time elapsed "<<end-start<<endl;
    
    return SOAP_OK;
}


// 
// name: MatToJPG
// - convert nat to 8U and save as JPG
// @param char *InputMatFilename
// @return char **OutputMatFilename

int ns__MatToJPG (struct soap *soap, char *InputMatFilename, char **OutputMatFilename)
{
    double start, end; 
    start = omp_get_wtime();
    
    Mat src;
    if(!readMat(InputMatFilename, src))
    {
        soap_fault(soap);
        cerr<< "MatToJPG:: can not read bin file" << endl;
        soap->fault->faultstring = "error :: can not read bin file";
        return SOAP_FAULT;
    }
    
    //get chan of src image
    int chan = src.channels();
    
    //check if it is not 8U then convert to 8UC(n)
    if( src.type() != 0 || src.type() != 8 || src.type() != 16 )
    {
       src.convertTo(src, CV_8UC(chan));
    }
    
    /* generate output file name */
    *OutputMatFilename = (char*)soap_malloc(soap, FILENAME_SIZE);
    time_t now = time(0);
    strftime(*OutputMatFilename, sizeof(OutputMatFilename)*FILENAME_SIZE, "/home/lluu/dir/%Y%m%d_%H%M%S.jpg", localtime(&now));
    
    if(!imwrite(*OutputMatFilename, src))
    {
        soap_fault(soap);
        cerr<< "MatToJPG:: can not save mat to jpg file" << endl;
        soap->fault->faultstring = "MatToJPG:: can not mat save to jpg file";
        return SOAP_FAULT;
    }
    
    src.release();
    
    end = omp_get_wtime();
    cerr<<"ns__MatToJPG "<<"time elapsed "<<end-start<<endl;
    
    return SOAP_OK;
}


// 
// name: convertTo
// @param char *inputMatFilename
// @return 
//      char *types="CV_32FC1",
//      char **outputMatFilename
int ns__ConvertTo( struct soap *soap, char *InputMatFilename,
                    char *types="CV_32FC1",
                    char **OutputMatFilename=NULL)
{
    double start, end; 
    start = omp_get_wtime();
    
	    
    Mat src;
    if(!readMat(InputMatFilename, src))
    {
        soap_fault(soap);
        cerr<< "ConvertTo:: can not read bin file" << endl;
        soap->fault->faultstring = "ConvertTo :: can not read bin file";
        return SOAP_FAULT;
    }
    
    if(src.type()!= getMatType(types))
    {
        src.convertTo(src,getMatType(types));
    }

    
    /* generate output file name */
	*OutputMatFilename = (char*)soap_malloc(soap, FILENAME_SIZE);
    time_t now = time(0);
    strftime(*OutputMatFilename, sizeof(OutputMatFilename)*FILENAME_SIZE, "/home/lluu/dir/%Y%m%d_%H%M%S_ConvertTo", localtime(&now));
	
	/* save to bin */
    if(!saveMat(*OutputMatFilename, src))
    {
        soap_fault(soap);
        cerr<<"ConvertTo:: can not save mat to binary file" << endl;
		soap->fault->faultstring = "ConvertTo:: can not save mat to binary file";
        return SOAP_FAULT;
    }
    
    src.release();
    
    end = omp_get_wtime();
    cerr<<"ns__ConvertTo "<<"time elapsed "<<end-start<<endl;
    return SOAP_OK;
}


// 
// name: Threshold
// @param
// @return

int ns__Threshold(struct soap *soap, 
                        char *InputMatFilename, 
                        double thresholdValue=127.0, 
                        double maxValue=255.0,
                        char *thresholdType="THRESH_BINARY",
                        char **OutputMatFilename=NULL)
{ 
    double start, end; 
    start = omp_get_wtime();
	
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
    threshold(src, dst, thresholdValue, maxValue, getThresholdType (thresholdType));
    
    /* generate output file name */
	*OutputMatFilename = (char*)soap_malloc(soap, FILENAME_SIZE);
    time_t now = time(0);
    strftime(*OutputMatFilename, sizeof(OutputMatFilename)*FILENAME_SIZE, "/home/lluu/dir/%Y%m%d_%H%M%S_BinaryThreshold", localtime(&now));
	
	/* save to bin */
    if(!saveMat(*OutputMatFilename, dst))
    {
        soap_fault(soap);
        cerr << "Threshold:: can not save mat to binary file" << endl;
		soap->fault->faultstring = "Threshold:: can not save mat to binary file";
        return SOAP_FAULT;
    }
    
    src.release();
    dst.release();
    
    end = omp_get_wtime();
    cerr<<"ns__Threshold "<<"time elapsed "<<end-start<<endl;
    return SOAP_OK;
}


// 
// name: ns__MorphologyEx
// @param
//      char *InputMatFilename,
//      char *morphOperation="MORPH_OPEN",
// @return
//      char **OutputMatFilename=NULL

int ns__MorphologyEx( struct soap *soap, 
                    char *InputMatFilename,
                    char *morphOperation="MORPH_OPEN",
                    char **OutputMatFilename=NULL)
{     
    double start, end; 
    start = omp_get_wtime();
    /* read from bin */
    Mat src;
    if(!readMat(InputMatFilename, src))
        {
            soap_fault(soap);
            cerr << "MorphologyEx:: can not read bin file" << endl;
            soap->fault->faultstring = "MorphologyEx :: can not read bin file";
            return SOAP_FAULT;
        }
    
    Mat dst(src.rows, src.cols, src.depth());
    Mat se; 
    Size seSize(3, 3); 
    Point seAnc(1, 1);
    
    se = getStructuringElement(MORPH_ELLIPSE, seSize, seAnc);
    morphologyEx(src, dst, getMorphOperation(morphOperation), se, seAnc);
    
    if(src.empty()) {
			soap_fault(soap);
			cerr << "MorphologyEx :: something wrong" << endl;
			soap->fault->faultstring = "MorphologyEx :: something wrong";
			return SOAP_FAULT;
    }
    
    /* generate output file name */
    *OutputMatFilename = (char*)soap_malloc(soap, FILENAME_SIZE);
    time_t now = time(0);
    strftime(*OutputMatFilename, sizeof(OutputMatFilename)*FILENAME_SIZE, "/home/lluu/dir/%Y%m%d_%H%M%S_MorphOpen", localtime(&now));
    
    /* save to bin */
    if(!saveMat(*OutputMatFilename, dst))
    {
        soap_fault(soap);
        cerr << "MorphologyEx:: save mat to binary file" << endl;
        soap->fault->faultstring = "MorphologyEx:: save mat to binary file";
        return SOAP_FAULT;
    }
    
    src.release();
    dst.release();
    se.release();
    
    end = omp_get_wtime();
    cerr<<"ns__MorphologyEx"<<"time elapsed "<<end-start<<endl;
    
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


int ns__erode(  struct soap *soap, char *InputMatFilename,
				char *elementFilename,
				int iteration=1,
				char **OutputMatFilename=NULL)
{ 
    double start, end; 
    start = omp_get_wtime();
    
	Mat src;
    if(!readMat(InputMatFilename, src))
    {
        soap_fault(soap);
        cerr << "erode :: can not read bin file" << endl;
        soap->fault->faultstring = "erode :: can not read bin file";
        return SOAP_FAULT;
    }
    
    Mat dst;
    Mat element;
    
    if(!readMat(elementFilename, element))
    {
		cerr<<"erode: use default element"<<endl;
        element.release();
        erode(src, dst, Mat(), Point(-1, -1), iteration);
    } else {
		cerr<<"erode: use defined element"<<endl;
        erode(src, dst, element, Point(-1, -1), iteration);
    }
    
    /* generate output file name */
    *OutputMatFilename = (char*)soap_malloc(soap, 60);
    time_t now = time(0);
    strftime(*OutputMatFilename, sizeof(OutputMatFilename)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_erode", localtime(&now));
    
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
    element.release();
    
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


int ns__dilate(  struct soap *soap, char *InputMatFilename,
				char *elementFilename,
				int iteration=1,
				char **OutputMatFilename=NULL)
{ 
    double start, end; 
    start = omp_get_wtime();
    
	Mat src;
    if(!readMat(InputMatFilename, src))
    {
        soap_fault(soap);
        cerr << "dilate :: can not read bin file" << endl;
        soap->fault->faultstring = "dilate :: can not read bin file";
        return SOAP_FAULT;
    }
    
    Mat dst;
    Mat element;
    
    if(!readMat(elementFilename, element))
    {
		cerr<<"dilate :: use default element"<<endl;
        element.release();
        dilate(src, dst, Mat(), Point(-1, -1), iteration);
    } else {
		cerr<<"dilate :: use defined element"<<endl;
        dilate(src, dst, element, Point(-1, -1), iteration);
    }
    
    /* generate output file name */
    *OutputMatFilename = (char*)soap_malloc(soap, 60);
    time_t now = time(0);
    strftime(*OutputMatFilename, sizeof(OutputMatFilename)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_dilate", localtime(&now));
    
    /* save to bin */
    if(!saveMat(*OutputMatFilename, dst))
    {
        soap_fault(soap);
        cerr << "dilate :: save mat to binary file" << endl;
        soap->fault->faultstring = "dilate :: save mat to binary file";
        return SOAP_FAULT;
    }
    
    src.release();
    dst.release();
    element.release();
    
    return SOAP_OK;
}



// 
// name: removeSmallCell
// @param
// @return
// 

int ns__removeSmallCell(struct soap *soap, 
						char *inputMatFilename,
						ns__RemoveSmallCell &out)
{ 
    double start, end; 
    start = omp_get_wtime();

	Mat src;
    if(!readMat(inputMatFilename, src))
    {
        soap_fault(soap);
        cerr << "removeSmallCell :: can not read bin file" << endl;
        soap->fault->faultstring = "removeSmallCell :: can not read bin file";
        return SOAP_FAULT;
    }
    
    Mat tmp = Mat(src.rows, src.cols, CV_32FC1);
    
    if( src.type() != CV_8UC1)
    {
        src.convertTo(src, CV_8UC1);
    }

    Mat outSingle = Mat::zeros(src.rows, src.cols, CV_32FC1);
	vector<vector<Point> > contours;
    double area = 0;
    findContours(	src, contours, CV_RETR_EXTERNAL, 
					CV_CHAIN_APPROX_SIMPLE, Point(0,0));

    for(size_t i = 0; i< contours.size(); i++)
    {
		const Point* p = &contours[i][0];
        int n = (int)contours[i].size();
		area = contourArea(Mat(contours[i]));
		
		if(area < 1500.0) //lower bound
		{
			fillPoly( tmp, &p, &n, 1, Scalar(0, 0, 0)); // remove from src (put black area instead the old one)
			
		} else if (area < 7500.0) {
			fillPoly(outSingle, &p, &n, 1, Scalar(255, 255, 255)); // keep small area here with white color
			fillPoly( tmp, &p, &n, 1, Scalar(0, 0, 0)); // remove from src
			
		} else {
			fillPoly( tmp, &p, &n, 1, Scalar(255, 255, 255)); //left the bigger area in src
			
		}
	}

	contours.clear();
	
	/* generate output file name */
    out.keepedArea = (char*)soap_malloc(soap, FILENAME_SIZE);
    out.biggerArea = (char*)soap_malloc(soap, FILENAME_SIZE);

    time_t now = time(0);
    strftime(out.keepedArea, sizeof(out.keepedArea)*FILENAME_SIZE, "/home/lluu/dir/%Y%m%d_%H%M%S_keepedArea", localtime(&now));
    strftime(out.biggerArea, sizeof(out.biggerArea)*FILENAME_SIZE, "/home/lluu/dir/%Y%m%d_%H%M%S_biggerArea", localtime(&now));
    
    /* save to bin */
    if(!saveMat(out.keepedArea, outSingle))
    {
        soap_fault(soap);
        cerr << "removeSmallCell:: save mat to binary file" << endl;
        soap->fault->faultstring = "error:: save mat to binary file";
        return SOAP_FAULT;
    }
    
    if(!saveMat(out.biggerArea, tmp))
    {
        soap_fault(soap);
        cerr << "removeSmallCell:: save mat to binary file" << endl;
        soap->fault->faultstring = "error:: save mat to binary file";
        return SOAP_FAULT;
    }
    
    src.release();
    tmp.release();
    outSingle.release();
    
    end = omp_get_wtime();
    cerr<<"ns__removeSmallCell"<<"time elapsed "<<end-start<<endl;
    return SOAP_OK;
}

// 
// name: ns__scanningCell
// @param char *inputMatFilename
// @return char **outputMatFilename
// 

int ns__scanningCell(struct soap *soap, 
						char *inputMatFilename,
						char **outputMatFilename)
{ 
    double start, end; 
    start = omp_get_wtime();
    
	Mat src;
    if(!readMat(inputMatFilename, src))
    {
        soap_fault(soap);
        cerr << "scanningCell :: can not read bin file" << endl;
        soap->fault->faultstring = "scanningCell :: can not read bin file";
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
    
    while(nContour != 0)
    {
        src32FC1.convertTo(srcTmp, CV_8UC1);

        findContours( srcTmp, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0,0));
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
                fillPoly( src3d2FC1, &p, &n, 1, Scalar(0, 0, 0)); // remove from src 
                fillPoly( output, &p, &n, 1, Scalar(255, 255, 255)); 
            }
        }
    }

	/* generate output file name */
    *outputMatFilename = (char*)soap_malloc(soap, FILENAME_SIZE);

    time_t now = time(0);
    strftime(*outputMatFilename, sizeof(outputMatFilename)*FILENAME_SIZE, "/home/lluu/dir/%Y%m%d_%H%M%S_scaningCell", localtime(&now));
    
    /* save to bin */
    if(!saveMat(*outputMatFilename, output))
    {
        soap_fault(soap);
        cerr << "scanningCell:: save mat to binary file" << endl;
        soap->fault->faultstring = "scanningCell:: save mat to binary file";
        return SOAP_FAULT;
    }
    
    src.release();
    srcTmp.release();
    src32FC1.release();
    output.release();
    
    end = omp_get_wtime();
    cerr<<"ns__scanningCell"<<"time elapsed "<<end-start<<endl;
    
    return SOAP_OK;
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

int getMatType ( const char *typeName)
{
    if(strcmp("CV_8UC1", typeName) == 0)
        return 0;
    else if(strcmp("CV_8UC2", typeName) == 0)
        return 8;
    else if(strcmp("CV_8UC3", typeName) == 0)
        return 16;
    else if(strcmp("CV_32FC1", typeName) == 0)
        return 5;
    else if(strcmp("CV_32FC2", typeName) == 0)
        return 13;
    else if(strcmp("CV_32FC3", typeName) == 0)
        return 21;
}


int getThresholdType ( const char *typeName)
{
    if(strcmp("THRESH_BINARY", typeName) == 0)
        return THRESH_BINARY;
    else if(strcmp("THRESH_BINARY_INV", typeName) == 0)
        return THRESH_BINARY_INV;
    else if(strcmp("THRESH_TRUNC", typeName) == 0)
        return THRESH_TRUNC;
    else if(strcmp("THRESH_TOZERO", typeName) == 0)
        return THRESH_TOZERO;
    else if(strcmp("THRESH_TOZERO_INV", typeName) == 0)
        return THRESH_TOZERO_INV;
}


int getColorFlag(int colorflag)
{
    switch (colorflag){
			case 0:
                return CV_LOAD_IMAGE_GRAYSCALE;
				break;
			case 1:
                return CV_LOAD_IMAGE_COLOR;
				break;
			case -1:
				return CV_LOAD_IMAGE_UNCHANGED;
				break;
			default :
				return CV_LOAD_IMAGE_COLOR;
	    }
}

int getMorphOperation ( const char *typeName)
{
    if(strcmp("MORPH_OPEN", typeName) == 0)
        return MORPH_OPEN;
    else if(strcmp("MORPH_CLOSE", typeName) == 0)
        return MORPH_CLOSE;
    else if(strcmp("MORPH_GRADIENT", typeName) == 0)
        return MORPH_GRADIENT;
    else if(strcmp("MORPH_TOPHAT", typeName) == 0)
        return MORPH_TOPHAT;
    else if(strcmp("MORPH_BLACKHAT", typeName) == 0)
        return MORPH_BLACKHAT;
}        
