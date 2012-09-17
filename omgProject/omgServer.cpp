#include "headerfile.cpp"
#include "omg.nsmap"
#include "myLog.h"
#include "config.h"

#define FILENAME_SIZE 75
#define MAX_THREAD 4

using namespace cv;

/* helper function */
int saveMat( const std::string& filename, const Mat& M);
int readMat( const std::string& filename, Mat& M);
int getMatType (const std::string& typeName);
int getThresholdType (const std::string& typeName);
int getColorFlag(int colorflag);
int getMorphOperation ( const std::string& typeName);
int ByteArrayToANN( std::string& annfile, CvANN_MLP* ann);
void getOutputFilename (std::string& filename, std::string& toAppend);
void getMemoryUsage (double& vm_usage, double& resident_set);
void getConfig (bool &timeChecking, bool &memoryChecking);
int getBorderType(std::string& bdType);
int getMatDepth (const std::string& depth);
int getInterpolation (const std::string& inter);
int getContourMode (const std::string& mode);


/* Global Configuration */
std::string BASE_DIR = "/home/lluu/thesis/result/";
std::string ERROR_FILENAME = "";
std::string DEFAULTVAL = "";
std::string CONFIG_FILE = "/home/lluu/thesis/result/config.cfg";
double start, end; /* time checking */


int main(int argc, char **argv)
{
	LOG_FILENAME = "/home/lluu/thesis/result/SERVICE_LOG";
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
int ns__imRead (struct soap *soap,
                std::string InputMatFilename,
                int flag=0, std::string &OutputMatFilename=ERROR_FILENAME)
{	
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* load image data */
	Mat src;
    src = imread(InputMatFilename.c_str(), flag);
    if(src.empty()) {
        Log(logERROR) << "imgToMat :: can not load image" << std::endl;
        return soap_receiver_fault(soap, "imgToMat :: can not load image", NULL);
    }
    
    //~ if(types==ERROR_FILENAME) types = "CV_8UC1";
    
    int srcType = types == DEFAULTVAL ? CV_8UC1 : getMatType(types);

    /* convert Mat to required type */
    if(src.type()!= srcType)
    {
        try{
            src.convertTo(src,srcType);
        } catch( cv::Exception& e ) {
            Log(logERROR) << e.what() << std::endl;
            return soap_receiver_fault(soap, e.what(), NULL);
        }
    }

	/* generate output file name  and save to bin*/
	std::string toAppend = "_imgToMat";
	getOutputFilename(OutputMatFilename,toAppend);

    if(!saveMat(OutputMatFilename, src))
    {
        Log(logERROR) << "imgToMat :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "imgToMat :: can not save mat to binary file", NULL);
    }

    src.release();
	
	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "imgToMat :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "imgToMat :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}
	
    return SOAP_OK;
}


int ns__MatToJPG (struct soap *soap, std::string InputMatFilename,  
					std::string &OutputMatFilename=ERROR_FILENAME)
{
    bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    Mat src;
    if(!readMat(InputMatFilename, src))
    {
        Log(logERROR) << "MatToJPG :: can not read bin file" << std::endl;
        return soap_receiver_fault(soap, "MatToJPG :: can not read bin file", NULL);
    }

    /* check if it is not 8U then convert to 8UC(n) */
    int chan = src.channels();	
    if( src.depth() != CV_8U )
    {
		Log(logINFO) << "convert image from" << src.type() << " to " << CV_8UC(chan) << std::endl;
        try{
            src.convertTo(src, CV_8UC(chan));
        } catch( cv::Exception& e ) {
            Log(logERROR) << e.what() << std::endl;
            return soap_receiver_fault(soap, e.what(), NULL);
        }
    }

    /* generate output file name */
	std::string toAppend = ".jpg";
    getOutputFilename(OutputMatFilename, toAppend);

    if(!imwrite(OutputMatFilename.c_str(), src))
    {
        Log(logERROR)<< "MatToJPG :: can not save mat to jpg file" << std::endl;
        return soap_receiver_fault(soap, "MatToJPG :: can not save mat to jpg file", NULL);
    }

    src.release();
	
	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "MatToJPG :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "MatToJPG :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}
	
    return SOAP_OK;
}


int ns__convertTo( struct soap *soap, 
					std::string InputMatFilename,
					std::string types=DEFAULTVAL,
                    double alpha_D=1, double beta_D=0,
					std::string &OutputMatFilename=ERROR_FILENAME)
{
    bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    Mat src;
    if(!readMat(InputMatFilename, src))
    {
        Log(logERROR)<< "ConvertTo :: can not read bin file" << std::endl;
        return soap_receiver_fault(soap, "ConvertTo :: can not read bin file", NULL);
    }

    int MatType = types == DEFAULTVAL ? CV_32FC1 : getMatType(types);

    if( src.type() != MatType )
    {
        try{
        src.convertTo(src, MatType, alpha_D, beta_D);
        } catch( cv::Exception& e ) {
            Log(logERROR) << e.what() << std::endl;
            return soap_receiver_fault(soap, e.what(), NULL);
        }
    }

    /* generate output file name */
	std::string toAppend = "_ConvertTo";
    getOutputFilename(OutputMatFilename, toAppend);

	/* save to bin */
    if(!saveMat(OutputMatFilename, src))
    {
        Log(logERROR) <<"ConvertTo :: can not save mat to binary file" << std::endl;
		return soap_receiver_fault(soap, "ConvertTo :: can not save mat to binary file", NULL);
    }
	
	src.release();
	
	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "ConvertTo :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "ConvertTo :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}
	
    return SOAP_OK;
}


int ns__Threshold(struct soap *soap,
                        std::string InputMatFilename,
                        double thresholdValue=127.0,
                        double maxValue=255.0,
                        std::string thresholdType=DEFAULTVAL,
                        std::string &OutputMatFilename=ERROR_FILENAME)
{
    bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "Threshold :: can not read bin file" << std::endl;
        return soap_receiver_fault(soap, "Threshold :: can not read bin file", NULL);
    }

    int threstype = thresholdType==DEFAULTVAL ? THRESH_BINARY : getThresholdType(thresholdType);
    
    try{
        threshold(src, src, thresholdValue, maxValue, threstype);
    } catch( cv::Exception& e ) {
            Log(logERROR) << e.what() << std::endl;
            return soap_receiver_fault(soap, e.what(), NULL);
    }
    
    /* generate output file name and save to binary file */
	std::string toAppend = "_Threshold";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, src))
    {
        Log(logERROR) << "Threshold :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "Threshold :: can not save mat to binary file", NULL);
    }

    src.release();
	
	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "Threshold :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "Threshold :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}
	
    return SOAP_OK;
}

//~ void adaptiveThreshold(InputArray src, OutputArray dst, double maxValue, int adaptiveMethod, int thresholdType, int blockSize, double C)
int ns__adaptiveThreshold(struct soap *soap,
                        std::string InputMatFilename,
                        std::string adaptiveMethod,
                        double maxValue=255.0,
                        std::string thresholdType=DEFAULTVAL,
                        int blockSize=3, double C=1,
                        std::string &OutputMatFilename=ERROR_FILENAME)
{
    bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "adaptiveThreshold :: can not read bin file" << std::endl;
        return soap_receiver_fault(soap, "adaptiveThreshold :: can not read bin file", NULL);
    }

    Mat dst;
    int adapt;
    if (adaptiveMethod.compare("ADAPTIVE_THRESH_MEAN_C") == 0) {
        adapt = ADAPTIVE_THRESH_MEAN_C;
    } else if (adaptiveMethod.compare("ADAPTIVE_THRESH_GAUSSIAN_C") == 0) {
        adapt = ADAPTIVE_THRESH_GAUSSIAN_C;
    }
    int threstype = thresholdType==DEFAULTVAL ? THRESH_BINARY : getThresholdType(thresholdType);
    
    try{
        adaptiveThreshold(src, dst, maxValue, adapt, threstype, blockSize, C);
    } catch( cv::Exception& e ) {
            Log(logERROR) << e.what() << std::endl;
            return soap_receiver_fault(soap, e.what(), NULL);
    }
    
    /* generate output file name and save to binary file */
	std::string toAppend = "_adaptiveThreshold";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, src))
    {
        Log(logERROR) << "adaptiveThreshold :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "adaptiveThreshold :: can not save mat to binary file", NULL);
    }

    src.release();
	
	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "adaptiveThreshold :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "adaptiveThreshold :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}
	
    return SOAP_OK;
}

int ns__getStructuringElement(  struct soap *soap, 
                std::string StructuringShape=DEFAULTVAL,
                int seSizeW=3, int seSizeH=3, 
                int anchorX_D=-1, int anchorY_D=-1,
                std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat se;
    Size seSize(seSizeW, seSizeH);
    Point seAnc(anchorX_D, anchorY_D);
    int shape;
    
    if (StructuringShape == DEFAULTVAL) StructuringShape = "MORPH_ELLIPSE";
    
    if (StructuringShape.compare("MORPH_ELLIPSE") == 0)  shape = MORPH_ELLIPSE;
    else if (StructuringShape.compare("MORPH_RECT") == 0)  shape = MORPH_RECT;
    else if (StructuringShape.compare("MORPH_CROSS") == 0)  shape = MORPH_CROSS;
    else {
        Log(logERROR) << "MorgetStructuringElement :: Invalid Structuring element shape" << std::endl;
        return soap_receiver_fault(soap, "getStructuringElement :: Invalid Structuring element shape", NULL);
    }
    
    
    try{
        se = getStructuringElement(shape, seSize, seAnc);
    } catch( cv::Exception& e ) {
            Log(logERROR) << e.what() << std::endl;
            return soap_receiver_fault(soap, e.what(), NULL);
    }

	std::string toAppend = "_getStructuringElement";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, se))
    {
        Log(logERROR) << "getStructuringElement :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "getStructuringElement :: can not save mat to binary file", NULL);
    }

    se.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "getStructuringElement :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "getStructuringElement :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}

    return SOAP_OK;
}

int ns__MorphologyEx( struct soap *soap,
						std::string InputMatFilename,
						std::string morphOperation=DEFAULTVAL,
                        int anchorX_D=-1, int anchorY_D=-1,
                        std::string StructuringElementFname=ERROR_FILENAME,
                        std::string StructuringShape=DEFAULTVAL,
                        int seSizeW_D=3, int seSizeH_D=3, 
						std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "MorphologyEx :: can not read bin file" << std::endl;
        return soap_receiver_fault(soap, "MorphologyEx :: can not read bin file", NULL);
    }

    Mat dst(src.rows, src.cols, src.depth());

//~ morphOperation="MORPH_OPEN"
//~ StructuringShape="MORPH_ELLIPSE",

    int morphOpt = morphOperation == DEFAULTVAL ? MORPH_OPEN : getMorphOperation(morphOperation);
    int shape;
    Mat se;
    Size seSize(seSizeW_D, seSizeH_D);
    Point seAnc(anchorX_D, anchorY_D);
    if (StructuringShape == DEFAULTVAL) StructuringShape = "MORPH_ELLIPSE";
    if(StructuringElementFname.compare(ERROR_FILENAME)==0){
        
        if (StructuringShape.compare("MORPH_ELLIPSE") == 0)  shape = MORPH_ELLIPSE;
        else if (StructuringShape.compare("MORPH_RECT") == 0)  shape = MORPH_RECT;
        else if (StructuringShape.compare("MORPH_CROSS") == 0)  shape = MORPH_CROSS;
        else {
            Log(logERROR) << "MorphologyEx :: Invalid Structuring element shape" << std::endl;
            return soap_receiver_fault(soap, "MorphologyEx :: Invalid Structuring element shape", NULL);
        }
        
        try{
        se = getStructuringElement(shape, seSize, seAnc);
        } catch( cv::Exception& e ) {
            Log(logERROR) << e.what() << std::endl;
            return soap_receiver_fault(soap, e.what(), NULL);
        }
    } else {
            if(!readMat(StructuringElementFname, se))
            {
                Log(logERROR) << "MorphologyEx :: can not read bin file for Structuring element" << std::endl;
                return soap_receiver_fault(soap, "MorphologyEx :: can not read bin file for Structuring element", NULL);
            }
    }

    try{
        morphologyEx(src, dst, morphOpt, se, seAnc);
    } catch( cv::Exception& e ) {
            Log(logERROR) << e.what() << std::endl;
            return soap_receiver_fault(soap, e.what(), NULL);
    }
    
    if(src.empty()) {
			Log(logERROR) << "MorphologyEx :: something's wrong" << std::endl;
            return soap_receiver_fault(soap, "MorphologyEx:: something's wrong", NULL);
    }

    std::string toAppend = "_MorphologyEx";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, src))
    {
        Log(logERROR) << "MorphologyEx :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "MorphologyEx :: can not save mat to binary file", NULL);
    }

    src.release();
	se.release();
	dst.release();
	
	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "MorphologyEx :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "MorphologyEx :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}
	
    return SOAP_OK;
}


int ns__erode(  struct soap *soap, 
				std::string InputMatFilename,
				std::string StructuringElementFilename=ERROR_FILENAME,
				int iteration_D=1, int anchorX_D=-1, int anchorY_D=-1, std::string borderType_D=DEFAULTVAL,
				std::string &OutputMatFilename=ERROR_FILENAME)
{
    bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "erode :: can not read bin file" << std::endl;
        return soap_receiver_fault(soap, "erode :: can not read bin file", NULL);
    }


    Mat dst;
    Mat element;
    
    int border = borderType_D == DEFAULTVAL ? BORDER_CONSTANT : getBorderType(borderType_D);
    
    if(!readMat(StructuringElementFilename, element))
    {
		Log(logINFO) << "erode: use default element" << std::endl;
        element.release();
            erode(src, dst, Mat(), Point(anchorX_D, anchorY_D), iteration_D, border);
    } else {
		Log(logINFO) << "erode: use defined element" << std::endl;
        try{
            erode(src, dst, element, Point(anchorX_D, anchorY_D), iteration_D, border);
        } catch( cv::Exception& e ) {
            Log(logERROR) << e.what() << std::endl;
            return soap_receiver_fault(soap, e.what(), NULL);
        }
        element.release();
    }

    std::string toAppend = "_erode";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "erode :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "erode :: can not save mat to binary file", NULL);
    }

    src.release();
	dst.release();
	
	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "erode :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "erode :: VM usage :" << vm << std::endl 
					<< "Residente set size :" << rss << std::endl;
	}
	
    return SOAP_OK;
}

//~ dilate(InputArray src, OutputArray dst, InputArray kernel, Point anchor=Point(-1,-1), int iterations=1, int borderType=BORDER_CONSTANT, const Scalar& borderValue=morphologyDefaultBorderValue()
int ns__dilate(  struct soap *soap, 
				std::string InputMatFilename,
				std::string StructuringElementFilename,
				int iteration_D=1, int anchorX_D=-1, int anchorY_D=-1,
                std::string borderType_D=DEFAULTVAL,
				std::string &OutputMatFilename=ERROR_FILENAME)
{
    bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "dilate :: can not read bin file" << std::endl;
        return soap_receiver_fault(soap, "dilate :: can not read bin file", NULL);
    }


    Mat dst;
    Mat element;
    
    int border = borderType_D == DEFAULTVAL ? BORDER_CONSTANT : getBorderType(borderType_D);

    if(!readMat(StructuringElementFilename, element))
    {
		Log(logINFO) << "dilate: use default element" << std::endl;
        element.release();
        
            dilate(src, dst, Mat(), Point(anchorX_D, anchorY_D), iteration_D, border);

        
    } else {
        
		Log(logINFO) << "dilate: use defined element" << std::endl;
        
        try{
            dilate(src, dst, element, Point(anchorX_D, anchorY_D), iteration_D, border);
        } catch( cv::Exception& e ) {
            Log(logERROR) << e.what() << std::endl;
            return soap_receiver_fault(soap, e.what(), NULL);
        }
        
		element.release();
    }

    std::string toAppend = "_dilate";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "dilate :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "dilate :: can not save mat to binary file", NULL);
    }

    src.release();
	dst.release();
	
	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "dilate :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "dilate :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}
	
    return SOAP_OK;
}


int ns__Or(  struct soap *soap, 
			std::string src1,
			std::string src2,
			std::string &OutputMatFilename=ERROR_FILENAME)
{
    bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat matSrc1;
	if(!readMat(src1, matSrc1))
    {
		Log(logERROR) << "Or :: can not read bin file for src1" << std::endl;
        return soap_receiver_fault(soap, "Or :: can not read bin file for src1", NULL);
    }


    Mat matSrc2;
    if(!readMat(src2, matSrc2))
    {
        Log(logERROR) << "Or :: can not read bin file for src2" << std::endl;
        return soap_receiver_fault(soap, "Or :: can not read bin file for src2", NULL);
    }

    int srcType1 = matSrc1.type();
    int srcType2 = matSrc2.type();

    if(srcType1 != srcType2)
    {
        try{
            matSrc2.convertTo(matSrc2, srcType1);
        } catch( cv::Exception& e ) {
            Log(logERROR) << e.what() << std::endl;
            return soap_receiver_fault(soap, e.what(), NULL);
        }
	}

    Mat dst;
    
    try{
        bitwise_or(matSrc1, matSrc2, dst);
    } catch( cv::Exception& e ) {
            Log(logERROR) << e.what() << std::endl;
            return soap_receiver_fault(soap, e.what(), NULL);
    }
    
    std::string toAppend = "_or";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "or :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "or :: can not save mat to binary file", NULL);
    }

    matSrc1.release();
    matSrc2.release();
    dst.release();
	
	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "or :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "or :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}
	
    return SOAP_OK;
}


int ns__And(  struct soap *soap, 
			std::string src1,
			std::string src2,
			std::string &OutputMatFilename=ERROR_FILENAME)
{
    bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat matSrc1;
	if(!readMat(src1, matSrc1))
    {
		Log(logERROR) << "And :: can not read bin file for src1" << std::endl;
        return soap_receiver_fault(soap, "Or :: can not read bin file for src1", NULL);
    }


    Mat matSrc2;
    if(!readMat(src2, matSrc2))
    {
        Log(logERROR) << "And :: can not read bin file for src2" << std::endl;
        return soap_receiver_fault(soap, "And :: can not read bin file for src2", NULL);
    }

    int srcType1 = matSrc1.type();
    int srcType2 = matSrc2.type();

    if(srcType1 != srcType2)
    {
        try{
            matSrc2.convertTo(matSrc2, srcType1);
        } catch( cv::Exception& e ) {
            Log(logERROR) << e.what() << std::endl;
            return soap_receiver_fault(soap, e.what(), NULL);
        }
    }

    Mat dst;
    bitwise_and(matSrc1, matSrc2, dst);

    std::string toAppend = "_and";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "And :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "And :: can not save mat to binary file", NULL);
    }

    matSrc1.release();
    matSrc2.release();
    dst.release();
	
	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "And :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "And :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}
	
    return SOAP_OK;
}

int ns__Xor(  struct soap *soap, 
			std::string src1,
			std::string src2,
			std::string &OutputMatFilename=ERROR_FILENAME)
{
    bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat matSrc1;
	if(!readMat(src1, matSrc1))
    {
		Log(logERROR) << "Xor :: can not read bin file for src1" << std::endl;
        return soap_receiver_fault(soap, "Xor :: can not read bin file for src1", NULL);
    }


    Mat matSrc2;
    if(!readMat(src2, matSrc2))
    {
        Log(logERROR) << "Xor :: can not read bin file for src2" << std::endl;
        return soap_receiver_fault(soap, "Xor :: can not read bin file for src2", NULL);
    }

    int srcType1 = matSrc1.type();
    int srcType2 = matSrc2.type();

    if(srcType1 != srcType2)
    {
        try{
            matSrc2.convertTo(matSrc2, srcType1);
        } catch( cv::Exception& e ) {
                Log(logERROR) << e.what() << std::endl;
                return soap_receiver_fault(soap, e.what(), NULL);
        }
	}

    Mat dst;
    
    try{
        bitwise_xor(matSrc1, matSrc2, dst);
    } catch( cv::Exception& e ) {
            Log(logERROR) << e.what() << std::endl;
            return soap_receiver_fault(soap, e.what(), NULL);
    }

    std::string toAppend = "_xor";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "Xor :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "Xor :: can not save mat to binary file", NULL);
    }

    matSrc1.release();
    matSrc2.release();
    dst.release();
	
	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "Xor :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "Xor :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}
	
    return SOAP_OK;
}


int ns__Not(  struct soap *soap, 
			std::string src,
			std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat matSrc;
	if(!readMat(src, matSrc))
    {
		Log(logERROR) << "Not :: can not read bin file for src" << std::endl;
        return soap_receiver_fault(soap, "Not :: can not read bin file for src", NULL);
    }
    
        bitwise_not(matSrc, matSrc);

    
	std::string toAppend = "_not";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, matSrc))
    {
        Log(logERROR) << "Not :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "Not :: can not save mat to binary file", NULL);
    }

    matSrc.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "Not :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "Not :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}

    return SOAP_OK;
}

int ns__Inverse(  struct soap *soap, 
			std::string InputMatFilename,
            std::string InvMethod_D=DEFAULTVAL,
			std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	Mat dst;
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "Inv:: can not read bin file for src" << std::endl;
        return soap_receiver_fault(soap, "Inv :: can not read bin file for src", NULL);
    }
    
    
    int method;
    if(InvMethod_D == DEFAULTVAL) InvMethod_D = "DECOMP_LU";
    
    if(InvMethod_D.compare("DECOMP_LU")==0) method = DECOMP_LU;
    else if(InvMethod_D.compare("DECOMP_CHOLESKY")==0) method = DECOMP_CHOLESKY;
    else if(InvMethod_D.compare("DECOMP_SVD")==0) method = DECOMP_SVD;

    try{
        dst = src.inv(method);
    } catch( cv::Exception& e ) {
        Log(logERROR) << e.what() << std::endl;
        return soap_receiver_fault(soap, e.what(), NULL);
    }

	std::string toAppend = "_Inv";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "Inv :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "Inv :: can not save mat to binary file", NULL);
    }

    src.release();
	dst.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "Inv :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "Inv :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}

    return SOAP_OK;
}

int ns__mul(  struct soap *soap, 
			std::string InputMatFilename,
			std::string AnotherMatFilename,
			double scale_D=1,
			std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	Mat dst;
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "mul :: can not read bin file for src1" << std::endl;
        return soap_receiver_fault(soap, "mul :: can not read bin file for src1", NULL);
    }
	
	Mat anotherMat;
	if(!readMat(AnotherMatFilename, anotherMat))
    {
		Log(logERROR) << "mul:: can not read bin file for src2" << std::endl;
        return soap_receiver_fault(soap, "mul :: can not read bin file for src2", NULL);
    }
	
    dst = src.mul(anotherMat,scale_D);

	std::string toAppend = "_mul";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "mul :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "mul :: can not save mat to binary file", NULL);
    }

    src.release();
    dst.release();
    anotherMat.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "mul :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "mul :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}

    return SOAP_OK;
}

/* Computes a cross-product of two 3-element vectors.  */
int ns__cross(  struct soap *soap, 
			std::string InputMatFilename,
			std::string AnotherMatFilename,
			std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	Mat dst;
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "cross :: can not read bin file for src1" << std::endl;
        return soap_receiver_fault(soap, "cross :: can not read bin file for src1", NULL);
    }
	
	Mat anotherMat;
	if(!readMat(AnotherMatFilename, anotherMat))
    {
		Log(logERROR) << "cross:: can not read bin file for src2" << std::endl;
        return soap_receiver_fault(soap, "cross :: can not read bin file for src2", NULL);
    }
	
    dst = src.cross(anotherMat);

	std::string toAppend = "_cross";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "cross :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "cross :: can not save mat to binary file", NULL);
    }

    src.release();
    dst.release();
    anotherMat.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "cross :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "mul :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}

    return SOAP_OK;
}

/* Computes a dot-product of two vectors.  */
int ns__dot(  struct soap *soap, 
			std::string InputMatFilename,
			std::string AnotherMatFilename,
			std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	Mat dst;
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "dot :: can not read bin file for src1" << std::endl;
        return soap_receiver_fault(soap, "dot :: can not read bin file for src1", NULL);
    }
	
	Mat anotherMat;
	if(!readMat(AnotherMatFilename, anotherMat))
    {
		Log(logERROR) << "dot:: can not read bin file for src2" << std::endl;
        return soap_receiver_fault(soap, "dot :: can not read bin file for src2", NULL);
    }
	
    dst = src.dot(anotherMat);

	std::string toAppend = "_dot";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "dot :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "dot :: can not save mat to binary file", NULL);
    }

    src.release();
    dst.release();
    anotherMat.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "dot :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "dot :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}

    return SOAP_OK;
}


/* Returns a zero array of the specified size and type.  */
/* choose only rows&&cols or size  */
int ns__zeros(  struct soap *soap, 
			int rows=0, int cols=0,
			std::string type=DEFAULTVAL,
			std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}
	Mat src;
	int matType = type == DEFAULTVAL ? CV_32F : getMatDepth(type);
	if(rows != 0 && cols != 0)
		src = Mat::zeros(rows, cols, matType);
	else {
		Log(logERROR) << "zeros :: Invalid input, please enter rows or cols again" << std::endl;
        return soap_receiver_fault(soap, "zeros :: Invalid input, please enter rows or cols again", NULL);
	}
	
	std::string toAppend = "_zeros";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, src))
    {
        Log(logERROR) << "zeros :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "zeros :: can not save mat to binary file", NULL);
    }

    src.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "zeros :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "zeros :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}

    return SOAP_OK;
}

/* Returns an array of all 1’s of the specified size and type.  */
int ns__ones(  struct soap *soap, 
			int rows=0, int cols=0,
            std::string type=DEFAULTVAL,
			std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}
	Mat src;
	int matType = type == DEFAULTVAL ? CV_32F : getMatDepth(type);
	if(rows != 0 && cols != 0){
        try{            
            src = Mat::ones(rows, cols, matType);
        } catch( cv::Exception& e ) {
            Log(logERROR) << e.what() << std::endl;
            return soap_receiver_fault(soap, e.what(), NULL);
        }
    }else {
		Log(logERROR) << "ones :: Invalid input, please enter rows or cols again" << std::endl;
        return soap_receiver_fault(soap, "ones :: Invalid input, please enter rows or cols again)", NULL);
	}
	
	std::string toAppend = "_ones";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, src))
    {
        Log(logERROR) << "ones :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "ones :: can not save mat to binary file", NULL);
    }

    src.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "ones :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "ones :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}

    return SOAP_OK;
}

int ns__createMat(  struct soap *soap, 
			int rows=0, int cols=0,
			std::string type=DEFAULTVAL,
			std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;	
	int matType = type == DEFAULTVAL? CV_32F : getMatDepth(type);
	if(rows != 0 && cols != 0)
		try{
            src.create(rows, cols, matType);
        } catch( cv::Exception& e ) {
            Log(logERROR) << e.what() << std::endl;
            return soap_receiver_fault(soap, e.what(), NULL);
        }
	else {
		Log(logERROR) << "createMat :: Invalid input, please enter rows or cols again." << std::endl;
        return soap_receiver_fault(soap, "createMat :: Invalid input, please enter rows or cols again.", NULL);
	}
	
	std::string toAppend = "_createMat";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, src))
    {
        Log(logERROR) << "createMat :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "createMat :: can not save mat to binary file", NULL);
    }

    src.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "createMat :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "createMat :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}

    return SOAP_OK;
}

/* Creates a matrix header for the specified row span.  */
int ns__colRange(  struct soap *soap, 
			std::string InputMatFilename,
			int startCol=0, int endCol=0, 
			std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	Mat dst;
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "colRange:: can not read bin file for src" << std::endl;
        return soap_receiver_fault(soap, "colRange :: can not read bin file for src", NULL);
    }
    
    try{    
        dst = src.colRange(startCol, endCol);
    } catch( cv::Exception& e ) {
        Log(logERROR) << e.what() << std::endl;
        return soap_receiver_fault(soap, e.what(), NULL);
    }

	std::string toAppend = "_colRange";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "colRange :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "colRange :: can not save mat to binary file", NULL);
    }

    src.release();
	dst.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "colRange :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "colRange :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}

    return SOAP_OK;
}

/* Creates a matrix header for the specified row span.  */
int ns__rowRange(  struct soap *soap, 
			std::string InputMatFilename,
			int startCol=0, int endCol=0, 
			std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	Mat dst;
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "rowRange:: can not read bin file for src" << std::endl;
        return soap_receiver_fault(soap, "rowRange :: can not read bin file for src", NULL);
    }
    
    try{
        dst = src.rowRange(startCol, endCol);
    } catch( cv::Exception& e ) {
        Log(logERROR) << e.what() << std::endl;
        return soap_receiver_fault(soap, e.what(), NULL);
    }

	std::string toAppend = "_rowRange";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "rowRange :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "rowRange :: can not save mat to binary file", NULL);
    }

    src.release();
	dst.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "rowRange :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "rowRange :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}

    return SOAP_OK;
}


int ns__getMatDetail(  struct soap *soap, 
			std::string InputMatFilename,
			ns__MatDetail &detail)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "rowRange:: can not read bin file for src" << std::endl;
        return soap_receiver_fault(soap, "rowRange :: can not read bin file for src", NULL);
    }
	
	detail.columns = src.cols;
	detail.rows = src.rows;

/*	
CV_8U - 8-bit unsigned integers ( 0..255 )
CV_8S - 8-bit signed integers ( -128..127 )
CV_16U - 16-bit unsigned integers ( 0..65535 )
CV_16S - 16-bit signed integers ( -32768..32767 )
CV_32S - 32-bit signed integers ( -2147483648..2147483647 )
CV_32F - 32-bit floating-point numbers ( -FLT_MAX..FLT_MAX, INF, NAN )
CV_64F - 64-bit floating-point numbers ( -DBL_MAX..DBL_MAX, INF, NAN )
*/
	int d = src.depth();
	if(d == CV_8U)
        detail.depth = "CV_8U";
	else if(d == CV_8S)
        detail.depth = "CV_8S";
	else if(d == CV_16U)
        detail.depth = "CV_16U";
	else if(d == CV_16S)
        detail.depth = "CV_16S";
	else if(d == CV_32S)
        detail.depth = "CV_32S";
    else if(d == CV_32F)
        detail.depth = "CV_32F";
	else if(d == CV_64F)
        detail.depth = "CV_64F";
	else
        detail.depth = "unknown type";

	
	int t = src.type();
	if(t == CV_8UC1)
        detail.type = "CV_8UC1";
    else if(t == CV_8UC2)
        detail.type = "CV_8UC2";
	else if(t == CV_8UC3)
        detail.type = "CV_8UC3";
    else if(t == CV_32FC1)
        detail.type = "CV_32FC1";
	else if(t == CV_32FC2)
        detail.type = "CV_32FC2";
    else if(t == CV_32FC3)
        detail.type = "CV_32FC3";
	else
		detail.type = "unknown type";
	
	detail.channel = src.channels();
	detail.empty = src.empty();
	
    src.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "rowRange :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "rowRange :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}

    return SOAP_OK;
}

//~ void Sobel(InputArray src, OutputArray dst, int ddepth, int dx, int dy, int ksize=3, double scale=1, double delta=0, int borderType=BORDER_DEFAULT )
int ns__Sobel(  struct soap *soap, 
			std::string InputMatFilename, std::string ddepth=DEFAULTVAL, 
            int kSize_D=3, double scale_D=1, double delta_D=0, 
            int dx=0, int dy=0, std::string borderType_D=DEFAULTVAL,
			std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	Mat dst;
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "Sobel :: can not read bin file for src" << std::endl;
        return soap_receiver_fault(soap, "Sobel :: can not read bin file for src", NULL);
    }
    
    int border = borderType_D == DEFAULTVAL ? BORDER_CONSTANT : getBorderType(borderType_D);
    int d = ddepth == DEFAULTVAL ? CV_8U : getMatDepth(ddepth);
    
    try{
        Sobel(src, dst, d, dx, dy, kSize_D, scale_D, delta_D, border);
    } catch( cv::Exception& e ) {
        Log(logERROR) << e.what() << std::endl;
        return soap_receiver_fault(soap, e.what(), NULL);
    }

	std::string toAppend = "_Sobel";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "Sobel :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "Sobel :: can not save mat to binary file", NULL);
    }

    src.release();
	dst.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "Sobel :: " << "time elapsed " << end-start << std::endl;
	}
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "Sobel :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}
    return SOAP_OK;
}


/* void blur(InputArray src, OutputArray dst, Size ksize, Point anchor=Point(-1,-1), int borderType=BORDER_DEFAULT ) */

int ns__blur(  struct soap *soap, 
			std::string InputMatFilename, int rows=0, int cols=0, 
            int anchorX_D=-1, int anchorY_D=-1, std::string borderType_D=DEFAULTVAL,
			std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	Mat dst;
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "blur :: can not read bin file for src" << std::endl;
        return soap_receiver_fault(soap, "blur :: can not read bin file for src", NULL);
    }
    
    int border = borderType_D == DEFAULTVAL ? BORDER_CONSTANT : getBorderType(borderType_D);
    
    if(rows != 0 && cols != 0)
        blur(src, dst, Size(cols, rows), Point(anchorX_D, anchorY_D), border); 

	std::string toAppend = "_blur";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "blur :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "blur :: can not save mat to binary file", NULL);
    }

    src.release();
	dst.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "blur :: " << "time elapsed " << end-start << std::endl;
	}
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "blur :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}
    return SOAP_OK;
}


/* void GaussianBlur(InputArray src, OutputArray dst, Size ksize, double sigmaX, double sigmaY=0, int borderType=BORDER_DEFAULT ) */
int ns__GaussianBlur(  struct soap *soap, 
			std::string InputMatFilename, int rows=0, int cols=0,
            double sigmaX=0, double sigmaY_D=0, std::string borderType_D=DEFAULTVAL,
			std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	Mat dst;
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "GaussianBlur :: can not read bin file for src" << std::endl;
        return soap_receiver_fault(soap, "GaussianBlur :: can not read bin file for src", NULL);
    }
    
    int border = borderType_D == DEFAULTVAL ? BORDER_DEFAULT : getBorderType(borderType_D);
    
    try{
        GaussianBlur(src, dst, Size(cols, rows), sigmaX, sigmaY_D, border); 
    } catch( cv::Exception& e ) {
        Log(logERROR) << e.what() << std::endl;
        return soap_receiver_fault(soap, e.what(), NULL);
    }

	std::string toAppend = "_blur";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "GaussianBlur :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "GaussianBlur :: can not save mat to binary file", NULL);
    }

    src.release();
	dst.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "GaussianBlur :: " << "time elapsed " << end-start << std::endl;
	}
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "GaussianBlur :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}
    return SOAP_OK;
}

//~ void cvtColor(InputArray src, OutputArray dst, int code, int dstCn=0 )
int ns__cvtColor(  struct soap *soap, 
			std::string InputMatFilename, std::string code, int dstChannel_D=0,
			std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	Mat dst;
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "cvtColor :: can not read bin file for src" << std::endl;
        return soap_receiver_fault(soap, "cvtColor :: can not read bin file for src", NULL);
    }
    
    int colorCode;
    if (code.compare("CV_RGB2GRAY") == 0)  colorCode = CV_RGB2GRAY;
    else if (code.compare("CV_BGR2XYZ") == 0)  colorCode = CV_BGR2XYZ;
    else if (code.compare("CV_RGB2XYZ") == 0)  colorCode = CV_RGB2XYZ;
    else if (code.compare("CV_XYZ2BGR") == 0)  colorCode = CV_XYZ2BGR;
    else if (code.compare("CV_XYZ2RGB") == 0)  colorCode = CV_XYZ2RGB;
    else if (code.compare("CV_BGR2YCrCb") == 0)  colorCode = CV_BGR2YCrCb;
    else if (code.compare("CV_RGB2YCrCb") == 0)  colorCode = CV_RGB2YCrCb;
    else if (code.compare("CV_YCrCb2BGR") == 0)  colorCode = CV_YCrCb2BGR;
    else if (code.compare("CV_YCrCb2RGB") == 0)  colorCode = CV_YCrCb2RGB;
    else if (code.compare("CV_BGR2HSV") == 0)  colorCode = CV_BGR2HSV;
    else if (code.compare("CV_RGB2HSV") == 0)  colorCode = CV_RGB2HSV;
    else if (code.compare("CV_HSV2BGR") == 0)  colorCode = CV_HSV2BGR;
    else if (code.compare("CV_HSV2RGB") == 0)  colorCode = CV_HSV2RGB;
    else if (code.compare("CV_BGR2HLS") == 0)  colorCode = CV_BGR2HLS;
    else if (code.compare("CV_RGB2HLS") == 0)  colorCode = CV_RGB2HLS;
    else if (code.compare("CV_HLS2BGR") == 0)  colorCode = CV_HLS2BGR;
    else if (code.compare("CV_HLS2RGB") == 0)  colorCode = CV_HLS2RGB;
    else if (code.compare("CV_BGR2Lab") == 0)  colorCode = CV_BGR2Lab;
    else if (code.compare("CV_RGB2Lab") == 0)  colorCode = CV_RGB2Lab;
    else if (code.compare("CV_Lab2BGR") == 0)  colorCode = CV_Lab2BGR;
    else if (code.compare("CV_Lab2RGB") == 0)  colorCode = CV_Lab2RGB;
    else if (code.compare("CV_BGR2Luv") == 0)  colorCode = CV_BGR2Luv;
    else if (code.compare("CV_RGB2Luv") == 0)  colorCode = CV_RGB2Luv;
    else if (code.compare("CV_Luv2BGR") == 0)  colorCode = CV_Luv2BGR;
    else if (code.compare("CV_Luv2RGB") == 0)  colorCode = CV_Luv2RGB;
    else if (code.compare("CV_BayerBG2BGR") == 0)  colorCode = CV_BayerBG2BGR;
    else if (code.compare("CV_BayerGB2BGR") == 0)  colorCode = CV_BayerGB2BGR;
    else if (code.compare("CV_BayerRG2BGR") == 0)  colorCode = CV_BayerRG2BGR;
    else if (code.compare("CV_BayerBG2RGB") == 0)  colorCode = CV_BayerBG2RGB;
    else if (code.compare("CV_BayerGR2BGR") == 0)  colorCode = CV_BayerGR2BGR;
    else if (code.compare("CV_BayerGB2RGB") == 0)  colorCode = CV_BayerGB2RGB;
    else if (code.compare("CV_BayerRG2RGB") == 0)  colorCode = CV_BayerRG2RGB;
    else if (code.compare("CV_BayerGR2RGB") == 0)  colorCode = CV_BayerGR2RGB;
    else {
        Log(logERROR) << "cvtColor :: Invalid Color Code to convert" << std::endl;
        return soap_receiver_fault(soap, "cvtColor :: Invalid Color Code to convert", NULL);
    }
    
    try{
        cvtColor(src, dst, colorCode, dstChannel_D); 
    } catch( cv::Exception& e ) {
        Log(logERROR) << e.what() << std::endl;
        return soap_receiver_fault(soap, e.what(), NULL);
    }

	std::string toAppend = "_cvtColor";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "cvtColor :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "cvtColor :: can not save mat to binary file", NULL);
    }

    src.release();
	dst.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "cvtColor :: " << "time elapsed " << end-start << std::endl;
	}
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "cvtColor :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}
    return SOAP_OK;
}


int ns__integral(  struct soap *soap, 
			std::string InputMatFilename, int sdepth_D=-1,
			std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	Mat dst;
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "integral :: can not read bin file for src" << std::endl;
        return soap_receiver_fault(soap, "integral :: can not read bin file for src", NULL);
    }
    
    try{
        integral(src, dst, sdepth_D); 
    } catch( cv::Exception& e ) {
        Log(logERROR) << e.what() << std::endl;
        return soap_receiver_fault(soap, e.what(), NULL);
    }

	std::string toAppend = "_integral";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "integral :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "integral :: can not save mat to binary file", NULL);
    }

    src.release();
	dst.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "integral :: " << "time elapsed " << end-start << std::endl;
	}
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "integral :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}
    return SOAP_OK;
}

int ns__CIAremoveSmallCell(struct soap *soap,
						std::string InputMatFilename,
						ns__RemoveSmallCell &out)
{
    bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "removeSmallCell :: can not read bin file for src" << std::endl;
        return soap_receiver_fault(soap, "removeSmallCell :: can not read bin file for src", NULL);
    }

    Mat tmp = Mat(src.rows, src.cols, CV_32FC1);

    if( src.type() != CV_8UC1)
    {
        src.convertTo(src, CV_8UC1);
    }

    Mat outSingle = Mat::zeros(src.rows, src.cols, CV_32FC1);
	vector<vector<cv::Point> > contours;
    double area = 0;
    const cv::Point* p;
    int n = 0;
    
    try{
        findContours(src, contours, CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE, Point(0,0));
	} catch (std::exception& e) { 
        Log(logERROR) << "removeSmallCell :: "<< e.what()<< std::endl;
        return soap_receiver_fault(soap, e.what() , NULL);
	}

    for(size_t i = 0; i< contours.size(); i++)
    {
		p = &contours[i][0];
        n = (int)contours[i].size();
		area = fabs(contourArea(Mat(contours[i])));

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

    /* save to bin */    
    std::string toAppend = "_keepedArea";
    getOutputFilename(out.keepedArea, toAppend);
    if(!saveMat(out.keepedArea, outSingle))
    {
        Log(logERROR) << "removeSmallCell :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "removeSmallCell :: can not save mat to binary file", NULL);
    }

    toAppend = "_unkeepArea";
    getOutputFilename(out.biggerArea, toAppend);
    if(!saveMat(out.biggerArea, tmp))
    {
        Log(logERROR) << "removeSmallCell :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "removeSmallCell :: can not save mat to binary file", NULL);
    }

    src.release();
    tmp.release();
    outSingle.release();
    
	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "removeSmallCell :: " << "time elapsed " << end-start << std::endl;
	}
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "removeSmallCell :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}
    
    return SOAP_OK;
}

int ns__CIAscanningCell(struct soap *soap,
						std::string biggerArea,
                        std::string keepArea,
						std::string &OutputMatFilename=ERROR_FILENAME)
{
    bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	if(!readMat(biggerArea, src))
    {
		Log(logERROR) << "scanningCell :: can not read bin file for src" << std::endl;
        return soap_receiver_fault(soap, "scanningCell :: can not read bin file for src", NULL);
    }
    
    Mat out_single;
    if(!readMat(keepArea, out_single))
    {
        Log(logERROR) << "scanningCell :: can not read bin file" << std::endl;
        return soap_receiver_fault(soap, "scanningCell :: can not read bin file", NULL);
    }
    
    
    Mat srcTmp;
    Mat src32FC1;
    src.convertTo(src32FC1, CV_32FC1);
    //~ Mat output = Mat::zeros(src.rows,src.cols, CV_32FC1);

    int nContour = 1;
    int prevContour = 0;
    int sameCount = 0;
    double area = 0;
    const Point* p;
    int n = 0;
    vector<vector<Point> > contours;

    while(nContour != 0)
    {
        src32FC1.convertTo(srcTmp, CV_8UC1); //cvConvert(input_morph, tmp8UC1);

        findContours( srcTmp, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0,0));
        nContour = contours.size();

        if( nContour == 0){ break; }
        if( nContour == prevContour ){
            erode( src32FC1, src32FC1, Mat());
            sameCount++;
        }else {
            sameCount = 0;
        }

        prevContour = nContour;

        for(size_t i = 0; i< contours.size(); i++)
        {
            p = &contours[i][0];
            n = (int)contours[i].size();
            area = fabs(contourArea(Mat(contours[i])));

            if((area < 3000.0) || (sameCount > 10))
            {
                fillPoly( src32FC1, &p, &n, 1, Scalar(0, 0, 0)); // remove from src
                fillPoly( out_single, &p, &n, 1, Scalar(255, 255, 255));
            }
        }
    }

	std::string toAppend = "_unkeepArea";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, out_single))
    {
        Log(logERROR) << "scanningCell :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "scanningCell :: can not save mat to binary file", NULL);
    }

    src.release();
    srcTmp.release();
    src32FC1.release();
    out_single.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "scanningCell :: " << "time elapsed " << end-start << std::endl;
	}
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "scanningCell :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}

    return SOAP_OK;
}

int ns__CIAseparateCell(struct soap *soap,
                        std::string outSingleCh,
                        std::string outputFormMorph,
						std::string &OutputMatFilename=ERROR_FILENAME)
{
    bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat outSingle;
	if(!readMat(outSingleCh, outSingle))
    {
		Log(logERROR) << "separateCell :: can not read bin file" << std::endl;
        return soap_receiver_fault(soap, "separateCell :: can not read bin file", NULL);
    }

    Mat tmp;
    outSingle.convertTo(tmp, CV_8UC1);
    
    int count = 1;
    int c = 0;
    int n = 0;
    const Point *p;
	vector<vector<Point> > contours;
    findContours(	tmp, contours, CV_RETR_EXTERNAL,
					CV_CHAIN_APPROX_SIMPLE, Point(0,0));

    for(size_t i = 0; i< contours.size(); i++)
    {
		p = &contours[i][0]; 
        n = (int)contours[i].size();
        c = ((count++)%254)+1;
        fillPoly( outSingle, &p, &n, 1, Scalar(c, c, c)); 
	}
	contours.clear();
    
    Mat inwater = Mat(outSingle.rows, outSingle.cols, CV_8UC3);
    //~ Mat outwater = Mat(outSingle.size(),CV_32SC1,outSingle.data);  //Is it correct?
    //Mat outwater;
    //outSingle.convertTo(outwater,CV_32SC1);
    outSingle.convertTo(outSingle,CV_32SC1);
    
    Mat cell; //output_morph
    if(!readMat(outputFormMorph, cell))
    {
        Log(logERROR) << "separateCell :: can not read bin file" << std::endl;
        return soap_receiver_fault(soap, "separateCell :: can not read bin file", NULL);
    }
    
    Mat tmp8UC1;
    cell.convertTo(tmp8UC1,CV_8UC1);
    
    vector<Mat> wt;
    wt.push_back(tmp8UC1);
    wt.push_back(tmp8UC1);
    wt.push_back(tmp8UC1);

    merge(wt, inwater);  
    watershed(inwater, outSingle);
    
    outSingle.convertTo(outSingle,CV_32FC1);
    erode(outSingle, outSingle, Mat(), Point(-1, -1), 2); 
    
    cell.convertTo(tmp8UC1,CV_8UC1);
    subtract(cell, outSingle, cell, tmp8UC1);

    //~ if(!imwrite("result_sepCell_3.jpg", cell))
    //~ {
        //~ Log(logERROR) << "scanningCell :: can not read bin file" << std::endl;
        //~ return soap_receiver_fault(soap, "scanningCell :: can not read bin file", NULL);
    //~ }

	/* generate output file name */
    std::string toAppend = "_separateCell";
    getOutputFilename(OutputMatFilename, toAppend);

    /* save to bin */
    if(!saveMat(OutputMatFilename, cell))
    {
        Log(logERROR) << "separateCell :: save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "separateCell :: save mat to binary file", NULL);
    }

    tmp8UC1.release();
    cell.release();
    outSingle.release();

    if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "separateCell :: " << "time elapsed " << end-start << std::endl;
	}
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "separateCell :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}

    return SOAP_OK;
    
}

int ns__CIAprepareResult(struct soap *soap,
						std::string InputMatFilename,
                        std::string afterthresNN,
						std::string &OutputMatFilename=ERROR_FILENAME)
{
    bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    Mat src;
    if(!readMat(InputMatFilename, src))
    {
        Log(logERROR) << "prepareResult :: can not read bin file" << std::endl;
        return soap_receiver_fault(soap, "prepareResult :: can not read bin file", NULL);
    }

    // convert src to CvMat to use an old-school function
    CvMat tmp = src;
    CV_Assert(tmp.cols == src.cols && tmp.rows == src.rows &&
        tmp.data.ptr == (uchar*)src.data && tmp.step == src.step);
    
    CvMat *output_morph = cvCreateMat(src.rows, src.cols, CV_32FC1);
    cvConvert(&tmp, output_morph);
    
    //***************************//
    Mat output1ChSrc;
    if(!readMat(afterthresNN, output1ChSrc))
    {
        Log(logERROR) << "output1Ch:: can not read bin file" << std::endl;
        return soap_receiver_fault(soap, "output1Ch :: can not read bin file", NULL);
    }

    // convert src to CvMat to use an old-school function
    CvMat tmp2 = output1ChSrc;
    CV_Assert(tmp2.cols == output1ChSrc.cols && tmp2.rows == output1ChSrc.rows &&
        tmp2.data.ptr == (uchar*)output1ChSrc.data && tmp2.step == output1ChSrc.step);
    
    CvMat *output1Ch = cvCreateMat(tmp2.rows, tmp2.cols, CV_32FC1);
    cvConvert(&tmp2, output1Ch);
    
    //**********************//
    
    
    IplImage *tmp8UC1 = cvCreateImage(cvGetSize(output_morph), IPL_DEPTH_8U, 1);
    cvConvertScale(output_morph, tmp8UC1);
    
    CvMemStorage *storage = cvCreateMemStorage();
	CvSeq *first_con = NULL;
	CvSeq *cur = NULL;
    
    cvFindContours(tmp8UC1, storage, &first_con, sizeof(CvContour), CV_RETR_EXTERNAL);
    
    IplImage *tmpImage = cvCreateImage(cvSize(tmp8UC1->width, tmp8UC1->height), IPL_DEPTH_8U, 3);
    cvSet(tmpImage, CV_RGB(0,0,255)); // Background, blue

    cvSetZero(tmp8UC1);
    CvScalar pixel;
    cur = first_con;
    //~ int ncell = 0; // total cells
    
    while (cur != NULL) {
        if ((cur->total > 2) && (fabs(cvContourArea(cur)) > 1500.0)) { // remove small area
            int npts = cur->total;
            CvPoint *p = new CvPoint[npts];
            cvCvtSeqToArray(cur, p);
            cvFillPoly(tmp8UC1, &p, &npts, 1, cvScalar(255)); // set mask
            pixel = cvAvg(output1Ch, tmp8UC1);
            cvFillPoly(tmp8UC1, &p, &npts, 1, cvScalar(0)); // clear mask
            if (pixel.val[0] > 0.5) { // Negative, green
                if (tmpImage != NULL)
                    cvFillPoly(tmpImage, &p, &npts, 1, CV_RGB(0,255,0));
                    
            } else if (pixel.val[0] > -0.5) { // Positive, red
                if (tmpImage != NULL)
                    cvFillPoly(tmpImage, &p, &npts, 1, CV_RGB(255,0,0));
            }
            delete[] p;
        }
        cur = cur->h_next;
    }
    
    Mat result = cvarrToMat(tmpImage, false);

	/* generate output file name */
    std::string toAppend = "_result";
    getOutputFilename(OutputMatFilename, toAppend);

    /* save to bin */
    if(!saveMat(OutputMatFilename, result))
    {
        Log(logERROR) << "result:: save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "result:: save mat to binary file", NULL);
    }

    src.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "result :: " << "time elapsed " << end-start << std::endl;
	}
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "result :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}

    return SOAP_OK;
}

int ns__CIAtrainANN(struct soap *soap,
                std::string InputMatFilename,
                std::string neuralFile,
                std::string &OutputMatFilename=ERROR_FILENAME)
{
    bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

	Mat src; //must be 3ch image
    if(!readMat(InputMatFilename, src))
    {
        Log(logERROR) << "trainANN :: can not read bin file" << std::endl;
        return soap_receiver_fault(soap, "trainANN :: can not read bin file", NULL);
    }

    // convert src to CvMat to use an old-school function
    CvMat tmp = src;
    CV_Assert(tmp.cols == src.cols && tmp.rows == src.rows &&
        tmp.data.ptr == (uchar*)src.data && tmp.step == src.step);

    CvMat *input3Ch = cvCreateMat(src.rows, src.cols, CV_32FC3);
    cvConvert(&tmp, input3Ch);
    CvMat *output1Ch = cvCreateMat(src.rows, src.cols, CV_32FC1);

    CvANN_MLP* neuron = NULL ;
    if (neuron == NULL )
        neuron = new CvANN_MLP();
	else
        neuron->clear();

    if(!ByteArrayToANN(neuralFile, neuron)){
        Log(logERROR) << "trainANN :: can not load byte array to neural" << std::endl;
        return soap_receiver_fault(soap, "trainANN :: can not load byte array to neural", NULL);
    }

    CvMat input_nn = cvMat(input3Ch->height*input3Ch->width, 3, CV_32FC1, input3Ch->data.fl);
    CvMat output_nn = cvMat(output1Ch->height*output1Ch->width, 1, CV_32FC1, output1Ch->data.fl);
    neuron->predict(&input_nn, &output_nn);

    Mat resultNN = cvarrToMat(output1Ch, false);

    /* generate output file name */
    std::string toAppend = "_trainANN";
    getOutputFilename(OutputMatFilename, toAppend);

    /* save to bin */
    if(!saveMat(OutputMatFilename, resultNN))
    {
        Log(logERROR) << "trainANN :: save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "trainANN :: save mat to binary file", NULL);
    }

    src.release();
    resultNN.release();
    cvReleaseMat(&output1Ch);

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "trainANN :: " << "time elapsed " << end-start << std::endl;
	}
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "trainANN :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}

    return SOAP_OK;
}


int ns__adjustBrighnessAndContrast(struct soap *soap,
                        std::string InputMatFilename,
						double alpha, int beta,
						std::string &OutputMatFilename=ERROR_FILENAME)
{
    bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "adjustBrighnessAndContrast :: can not read bin file for src" << std::endl;
        return soap_receiver_fault(soap, "adjustBrighnessAndContrast :: can not read bin file for src", NULL);
    }

    Mat dst = Mat::zeros( src.size(), src.type() );
    
    for( int y = 0; y < src.rows; y++ )
    {   for( int x = 0; x < src.cols; x++ )
        {   for( int c = 0; c < 3; c++ )
            {
                dst.at<Vec3b>(y,x)[c] =
                saturate_cast<uchar>( alpha*( src.at<Vec3b>(y,x)[c] ) + beta );
            }
        }
    }
    
    std::string toAppend = "_adjustBrighnessAndContrast";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "adjustBrighnessAndContrast :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "adjustBrighnessAndContrast :: can not save mat to binary file", NULL);
    }

    src.release();
	dst.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "adjustBrighnessAndContrast :: " << "time elapsed " << end-start << std::endl;
	}
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "adjustBrighnessAndContrast :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}
    return SOAP_OK;

}

int ns__viewImage(  struct soap *soap, 
                    std::string InputMatFilename, 
                    ns__base64Binary &image)
{
    bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    Mat src;
    if(!readMat(InputMatFilename, src))
    {
        Log(logERROR) << "viewImage:: can not read bin file" << std::endl;
        return soap_receiver_fault(soap, "viewImage:: can not read bin file", NULL);
    }

    /* check if it is not 8U then convert to 8UC(n) */
    int chan = src.channels();
    if( src.type() != 0 || src.type() != 8 || src.type() != 16 )
    {
        try{
           src.convertTo(src, CV_8UC(chan));
        } catch( cv::Exception& e ) {
            Log(logERROR) << e.what() << std::endl;
            return soap_receiver_fault(soap, e.what(), NULL);
        }
    }
    
    if(!imwrite("/home/lluu/thesis/result/output.jpg", src))
    {
        Log(logERROR) << "viewImage:: can not save mat to jpg file" << std::endl;
        return soap_receiver_fault(soap, "viewImage:: can not save image to file", NULL);
    }

    FILE *fd = fopen("/home/lluu/thesis/result/output.jpg", "r");
    if(fd){
        int i =0, c = 0;
        fseek(fd,0,SEEK_END); // seek to end of file
        int size = ftell(fd); // get current file pointer
        fseek(fd, 0, SEEK_SET); // seek back to beginning of file
        
        image.__ptr = (unsigned char*)soap_malloc(soap, size);
        for (i = 0; i < size; i++)
        { if ((c = fgetc(fd)) == EOF)
            break;
          image.__ptr[i] = c;
        }
        image.__size = i;
    } else {
        Log(logERROR) <<"viewImage:: image file read error"<<std::endl;
    }
    
    return SOAP_OK;
}


int ns__medianBlur(  struct soap *soap, 
			std::string InputMatFilename, int kSize=1,
			std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	Mat dst;
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "medianBlur :: can not read bin file for src" << std::endl;
        return soap_receiver_fault(soap, "medianBlur :: can not read bin file for src", NULL);
    }
    
    if(kSize%2 == 0 || kSize <=1){
        Log(logERROR) << "medianBlur :: ksize (Aperture linear size) must be odd and greater than 1, for example: 3, 5, 7 ..." << std::endl;
        return soap_receiver_fault(soap, "medianBlur :: ksize (Aperture linear size) must be odd and greater than 1, for example: 3, 5, 7 ...", NULL);
    }
    
    try{
        medianBlur(src, dst, kSize); 
    } catch( cv::Exception& e ) {
        Log(logERROR) << e.what() << std::endl;
        return soap_receiver_fault(soap, e.what(), NULL);
    }
	
    std::string toAppend = "_medianBlur";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "medianBlur :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "medianBlur :: can not save mat to binary file", NULL);
    }

    src.release();
	dst.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "medianBlur :: " << "time elapsed " << end-start << std::endl;
	}
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "medianBlur :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}
    return SOAP_OK;
}

//~ C++: void Laplacian(InputArray src, OutputArray dst, int ddepth, int ksize=1, double scale=1, double delta=0, int borderType=BORDER_DEFAULT )
int ns__Laplacian(  struct soap *soap, 
			std::string InputMatFilename, std::string ddepth=DEFAULTVAL, 
            int kSize_D=1, double scale_D=1, double delta_D=0, 
            std::string borderType_D=DEFAULTVAL,
			std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	Mat dst;
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "Laplacian :: can not read bin file for src" << std::endl;
        return soap_receiver_fault(soap, "Laplacian :: can not read bin file for src", NULL);
    }
    
    int d = ddepth == DEFAULTVAL ? CV_8U : getMatDepth(ddepth);
    int border =  borderType_D == DEFAULTVAL ? BORDER_DEFAULT : getBorderType(borderType_D);
    
    
    if(kSize_D%2 == 0 || kSize_D <=0){
        Log(logERROR) << "Laplacian :: kSize must be positive and odd" << std::endl;
        return soap_receiver_fault(soap, "kSize must be positive and odd", NULL);
    }

    try{
        Laplacian(src, dst, d, kSize_D ,scale_D , delta_D , border);
    } catch( cv::Exception& e ) {
        Log(logERROR) << e.what() << std::endl;
        return soap_receiver_fault(soap, e.what(), NULL);
    }

	std::string toAppend = "_Laplacian";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "Laplacian :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "Laplacian :: can not save mat to binary file", NULL);
    }

    src.release();
	dst.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "Laplacian :: " << "time elapsed " << end-start << std::endl;
	}
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "Laplacian :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}
    return SOAP_OK;
}

//~ pyrDown(InputArray src, OutputArray dst, const Size& dstsize=Size(), int borderType=BORDER_DEFAULT )
int ns__pyrDown(  struct soap *soap, 
			std::string InputMatFilename, int rows=0, int cols=0, 
            std::string borderType_D=DEFAULTVAL,
			std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	Mat dst;
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "pyrDown :: can not read bin file for src" << std::endl;
        return soap_receiver_fault(soap, "pyrDown :: can not read bin file for src", NULL);
    }
    
    int border = borderType_D == DEFAULTVAL ? BORDER_CONSTANT : getBorderType(borderType_D);
    
    try{
       pyrDown(src, dst, Size(rows,cols), border );
    } catch( cv::Exception& e ) {
        Log(logERROR) << e.what() << std::endl;
        return soap_receiver_fault(soap, e.what(), NULL);
    }

	std::string toAppend = "_pyrDown";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "pyrDown :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "pyrDown :: can not save mat to binary file", NULL);
    }

    src.release();
	dst.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "pyrDown :: " << "time elapsed " << end-start << std::endl;
	}
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "pyrDown :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}
    return SOAP_OK;
}

int ns__pyrUp(  struct soap *soap, 
			std::string InputMatFilename, int rows=0, int cols=0, 
            std::string borderType_D=DEFAULTVAL,
			std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	Mat dst;
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "pyrUp :: can not read bin file for src" << std::endl;
        return soap_receiver_fault(soap, "pyrUp :: can not read bin file for src", NULL);
    }
    
    int border = borderType_D == DEFAULTVAL ? BORDER_CONSTANT : getBorderType(borderType_D);
    
    pyrUp(src, dst, Size(rows,cols), border);

	std::string toAppend = "_pyrUp";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "pyrUp :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "pyrUp :: can not save mat to binary file", NULL);
    }

    src.release();
	dst.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "pyrUp :: " << "time elapsed " << end-start << std::endl;
	}
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "pyrUp :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}
    return SOAP_OK;
}


//~ void addWeighted(InputArray src1, double alpha, InputArray src2, double beta, double gamma, OutputArray dst, int dtype=-1)
int ns__addWeighted(  struct soap *soap, 
			std::string InputMatFilename1, double alpha, 
            std::string InputMatFilename2 , double beta, 
            double gamma, int dtype_D=-1,
			std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src1;
    Mat src2;
	Mat dst;
	if(!readMat(InputMatFilename1, src1))
    {
		Log(logERROR) << "addWeighted :: can not read bin file for src1" << std::endl;
        return soap_receiver_fault(soap, "addWeighted :: can not read bin file for src1", NULL);
    }
    
    if(!readMat(InputMatFilename2, src2))
    {
		Log(logERROR) << "addWeighted :: can not read bin file for src2" << std::endl;
        return soap_receiver_fault(soap, "addWeighted :: can not read bin file for src2", NULL);
    }
    
    try{
        addWeighted(src1, alpha, src2, beta, gamma, dst, dtype_D);
    } catch( cv::Exception& e ) {
        Log(logERROR) << e.what() << std::endl;
        return soap_receiver_fault(soap, e.what(), NULL);
    }
    
	std::string toAppend = "_addWeighted";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "addWeighted :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "addWeighted :: can not save mat to binary file", NULL);
    }

    src1.release();
    src2.release();
	dst.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "addWeighted :: " << "time elapsed " << end-start << std::endl;
	}
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "addWeighted :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}
    return SOAP_OK;
}

//~ void add(InputArray src1, InputArray src2, OutputArray dst, InputArray mask=noArray(), int dtype=-1)
int ns__add(  struct soap *soap, 
			std::string InputMatFilename1, std::string InputMatFilename2 ,
            std::string maskFilename_D=ERROR_FILENAME , int dtype_D=-1,
			std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src1;
    Mat src2;
	Mat dst;
	if(!readMat(InputMatFilename1, src1))
    {
		Log(logERROR) << "add :: can not read bin file for src1" << std::endl;
        return soap_receiver_fault(soap, "add :: can not read bin file for src1", NULL);
    }
    
    if(!readMat(InputMatFilename2, src2))
    {
		Log(logERROR) << "add :: can not read bin file for src2" << std::endl;
        return soap_receiver_fault(soap, "add :: can not read bin file for src2", NULL);
    }
    
    Mat mask;
    if(maskFilename_D.compare(ERROR_FILENAME)==0){
        add(src1, src2, dst, noArray(), dtype_D);
        
    } else {
        if(!readMat(maskFilename_D, mask))
        {
            Log(logERROR) << "add :: can not read bin file for mask" << std::endl;
            return soap_receiver_fault(soap, "add :: can not read bin file for mask", NULL);
        }
        
        try{
            add(src1, src2, dst, mask, dtype_D);
        } catch( cv::Exception& e ) {
            Log(logERROR) << e.what() << std::endl;
            return soap_receiver_fault(soap, e.what(), NULL);
        }
    }

	std::string toAppend = "_add";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "add :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "add :: can not save mat to binary file", NULL);
    }

    src1.release();
    src2.release();
	dst.release();
    mask.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "add :: " << "time elapsed " << end-start << std::endl;
	}
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "add :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}
    return SOAP_OK;
}

//~ void subtract(InputArray src1, InputArray src2, OutputArray dst, InputArray mask=noArray(), int dtype=-1)
int ns__subtract(  struct soap *soap, 
			std::string InputMatFilename1, std::string InputMatFilename2 ,
            std::string maskFilename_D=ERROR_FILENAME , int dtype_D=-1,
			std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src1;
    Mat src2;
	Mat dst;
	if(!readMat(InputMatFilename1, src1))
    {
		Log(logERROR) << "subtract :: can not read bin file for src1" << std::endl;
        return soap_receiver_fault(soap, "subtract :: can not read bin file for src1", NULL);
    }
    
    if(!readMat(InputMatFilename2, src2))
    {
		Log(logERROR) << "subtract :: can not read bin file for src2" << std::endl;
        return soap_receiver_fault(soap, "subtract :: can not read bin file for src2", NULL);
    }

    Mat mask;    
    if(maskFilename_D.compare(ERROR_FILENAME)==0){
         subtract(src1, src2, dst, noArray(), dtype_D);
    } else {
        if(!readMat(maskFilename_D, mask))
        {
            Log(logERROR) << "subtract :: can not read bin file for mask" << std::endl;
            return soap_receiver_fault(soap, "subtract :: can not read bin file for mask", NULL);
        }

        try{
            subtract(src1, src2, dst, mask, dtype_D);
        } catch( cv::Exception& e ) {
            Log(logERROR) << e.what() << std::endl;
            return soap_receiver_fault(soap, e.what(), NULL);
        }

     }


   

	std::string toAppend = "_subtract";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "subtract :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "subtract :: can not save mat to binary file", NULL);
    }

    src1.release();
    src2.release();
	dst.release();
    mask.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "subtract :: " << "time elapsed " << end-start << std::endl;
	}
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "subtract :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}
    return SOAP_OK;
}


//~ MatExpr abs(const Mat& m)
int ns__abs(  struct soap *soap, 
			std::string InputMatFilename,
			std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}
	Mat src;
    if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "abs :: can not read bin file for src" << std::endl;
        return soap_receiver_fault(soap, "abs :: can not read bin file for src", NULL);
    }
	
    Mat dst;
    dst = abs(src);
	
	std::string toAppend = "_abs";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "abs :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "abs :: can not save mat to binary file", NULL);
    }

    src.release();
    dst.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "abs :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "abs :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}

    return SOAP_OK;
}

//~ void absdiff(InputArray src1, InputArray src2, OutputArray dst)
int ns__absdiff(  struct soap *soap, 
			std::string InputMatFilename1, std::string InputMatFilename2,
			std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}
    
	Mat src1;
    Mat src2;
	Mat dst;
	if(!readMat(InputMatFilename1, src1))
    {
		Log(logERROR) << "absdiff :: can not read bin file for src1" << std::endl;
        return soap_receiver_fault(soap, "add :: can not read bin file for src1", NULL);
    }
    
    if(!readMat(InputMatFilename2, src2))
    {
		Log(logERROR) << "absdiff :: can not read bin file for src2" << std::endl;
        return soap_receiver_fault(soap, "add :: can not read bin file for src2", NULL);
    }
    
    absdiff(src1, src2, dst);
	
	std::string toAppend = "_absdiff";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "absdiff :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "absdiff :: can not save mat to binary file", NULL);
    }

    src1.release();
    src2.release();
    dst.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "absdiff :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "absdiff :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}

    return SOAP_OK;
}

//~ void sqrt(InputArray src, OutputArray dst)
int ns__sqrt(  struct soap *soap, 
			std::string InputMatFilename,
			std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
    Mat dst;
    
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "sqrt :: can not read bin file for src" << std::endl;
        return soap_receiver_fault(soap, "sqrt :: can not read bin file for src", NULL);
    }

    sqrt(src, dst);

	std::string toAppend = "_sqrt";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "sqrt :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "sqrt :: can not save mat to binary file", NULL);
    }

    src.release();
    dst.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "sqrt :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "sqrt :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}

    return SOAP_OK;
}

//~ void watershed(InputArray image, InputOutputArray markers)
int ns__watershed(  struct soap *soap, 
			std::string InputMatFilename,
            std::string MarkerMatFilename,
			std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat image;
    Mat marker;
    
	if(!readMat(InputMatFilename, image))
    {
		Log(logERROR) << "watershed :: can not read bin file for image" << std::endl;
        return soap_receiver_fault(soap, "watershed :: can not read bin file for image", NULL);
    }
    
    if(!readMat(InputMatFilename, marker))
    {
		Log(logERROR) << "watershed :: can not read bin file for marker" << std::endl;
        return soap_receiver_fault(soap, "watershed :: can not read bin file for marker", NULL);
    }
    
    try{
        watershed(image, marker);
    } catch( cv::Exception& e ) {
        Log(logERROR) << e.what() << std::endl;
        return soap_receiver_fault(soap, e.what(), NULL);
    }

	std::string toAppend = "_watershed";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, image))
    {
        Log(logERROR) << "watershed :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "watershed :: can not save mat to binary file", NULL);
    }

    image.release();
    marker.release();
    
	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "watershed :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "watershed :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}

    return SOAP_OK;
}

//~ void circle(Mat& img, Point center, int radius, const Scalar& color, int thickness=1, int lineType=8, int shift=0)
int ns__circle(  struct soap *soap, 
			std::string InputMatFilename, int centerX, int centerY, int radius, int scalarColor0, int scalarColor1, int scalarColor2, int thickness_D=1, int lineType_D=8, int shift_D=0, std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "circle :: can not read bin file for src" << std::endl;
        return soap_receiver_fault(soap, "circle :: can not read bin file for src", NULL);
    }
    try{
        circle(src, Point(centerX, centerY), radius, Scalar(scalarColor0, scalarColor1, scalarColor2), thickness_D, lineType_D, shift_D);
    } catch( cv::Exception& e ) {
        Log(logERROR) << e.what() << std::endl;
        return soap_receiver_fault(soap, e.what(), NULL);
    }

	std::string toAppend = "_circle";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, src))
    {
        Log(logERROR) << "circle :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "circle :: can not save mat to binary file", NULL);
    }

    src.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "circle :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "circle :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}

    return SOAP_OK;
}

//~ void ellipse(Mat& img, Point center, Size axes, double angle, double startAngle, double endAngle, const Scalar& color, int thickness=1, int lineType=8, int shift=0)
int ns__ellipse(  struct soap *soap, 
			std::string InputMatFilename, int centerX=10, int centerY=10, int axeX=1, int axeY=1, double angle=0.0, double startAngle=0.0, double endAngle=360.0, int scalarColor0=0, int scalarColor1=0, int scalarColor2=0, int thickness_D=1, int lineType_D=8, int shift_D=0, std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "ellipse :: can not read bin file for src" << std::endl;
        return soap_receiver_fault(soap, "ellipse :: can not read bin file for src", NULL);
    }

    try{
        ellipse(src, Point(centerX, centerY), Size(axeX, axeY), angle, startAngle, endAngle, Scalar(scalarColor0, scalarColor1, scalarColor2), thickness_D, lineType_D, shift_D);
    } catch( cv::Exception& e ) {
        Log(logERROR) << e.what() << std::endl;
        return soap_receiver_fault(soap, e.what(), NULL);
    }

	std::string toAppend = "_ellipse";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, src))
    {
        Log(logERROR) << "ellipse :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "ellipse :: can not save mat to binary file", NULL);
    }

    src.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "ellipse :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "ellipse :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}

    return SOAP_OK;
}


int ns__accessPixelValue(  struct soap *soap,
            std::string InputMatFilename,
            std::string returnType=DEFAULTVAL,
            int intToSet=0, float floatToSet=0,
            int pixelI =0, int pixelJ =0, int channel =0,
			std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "accessPixelValue :: can not read bin file for src" << std::endl;
        return soap_receiver_fault(soap, "accessPixelValue :: can not read bin file for src", NULL);
    }
    
    if(returnType == DEFAULTVAL) returnType = "uchar";
        
    if(returnType.compare("uchar")==0)
        src.at<uchar>(pixelJ,pixelI)= intToSet;
    else if(returnType.compare("float")==0)
        src.at<float>(pixelJ,pixelI)= floatToSet;
    else if(returnType.compare("int")==0)
        src.at<int>(pixelJ,pixelI)= intToSet;
    else if(returnType.compare("Vec3b")==0)
        src.at<Vec3b>(pixelJ,pixelI)[channel]= floatToSet;
    
        
    std::string toAppend = "_accessPixelValue";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, src))
    {
        Log(logERROR) << "accessPixelValue :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "accessPixelValue :: can not save mat to binary file", NULL);
    }

    src.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "accessPixelValue :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "accessPixelValue :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}

    return SOAP_OK;
}

int ns__printAllMatValue ( struct soap *soap, std::string InputMatFilename,
                            std::string &OutputMat=ERROR_FILENAME)
{
    bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "accessPixelValue :: can not read bin file for src" << std::endl;
        return soap_receiver_fault(soap, "accessPixelValue :: can not read bin file for src", NULL);
    }
    
    std::stringstream ss;    
    ss << src;
    OutputMat = ss.str();
    
    src.release();
    
    if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "accessPixelValue :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "accessPixelValue :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}

    return SOAP_OK;
}


//~ void filter2D(InputArray src, OutputArray dst, int ddepth, InputArray kernel, Point anchor=Point(-1,-1), double delta=0, int borderType=BORDER_DEFAULT )
int ns__filter2D( struct soap *soap, 
			std::string InputMatFilename,
            int ddepth, std::string kernelFname=ERROR_FILENAME, 
            int anchorX_D=-1, int anchorY_D=-1, 
            double delta_D=0, std::string borderType_D=DEFAULTVAL,
            std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "filter2D :: can not read bin file for src" << std::endl;
        return soap_receiver_fault(soap, "filter2D :: can not read bin file for src", NULL);
    }

    Mat kernel;
	if(!readMat(kernelFname, kernel))
    {
		Log(logERROR) << "filter2D :: can not read bin file for kernel" << std::endl;
        return soap_receiver_fault(soap, "filter2D :: can not read bin file for kernel", NULL);
    }
    
    Mat dst;
    int border = borderType_D == DEFAULTVAL ? BORDER_CONSTANT : getBorderType(borderType_D);
    
    try{
        filter2D(src, dst, ddepth, kernel, Point(anchorX_D, anchorY_D), delta_D, border);
    } catch( cv::Exception& e ) {
        Log(logERROR) << e.what() << std::endl;
        return soap_receiver_fault(soap, e.what(), NULL);
    }

	std::string toAppend = "_filter2D";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, src))
    {
        Log(logERROR) << "filter2D :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "filter2D :: can not save mat to binary file", NULL);
    }

    src.release();
    dst.release();
    kernel.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "filter2D :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "filter2D :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}

    return SOAP_OK;
}

 //~ void resize(InputArray src, OutputArray dst, Size dsize, double fx=0, double fy=0, int interpolation=INTER_LINEAR )

int ns__resize(  struct soap *soap, 
			std::string InputMatFilename, int dstRows=0, int dstCols=0,
            double fx_D=0, double fy_D=0, std::string interpolation_D=DEFAULTVAL,
			std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	Mat dst;
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "resize :: can not read bin file for src" << std::endl;
        return soap_receiver_fault(soap, "resize :: can not read bin file for src", NULL);
    }
    
    int inter = interpolation_D == DEFAULTVAL ? INTER_LINEAR : getInterpolation(interpolation_D);
    resize(src, dst, Size(dstRows, dstCols), fx_D, fy_D, inter);
    
	std::string toAppend = "_resize";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "resize :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "resize :: can not save mat to binary file", NULL);
    }

    src.release();
	dst.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "resize :: " << "time elapsed " << end-start << std::endl;
	}
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "resize :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}
    return SOAP_OK;
}

//~ void Canny(InputArray image, OutputArray edges, double threshold1, double threshold2, int apertureSize=3, bool L2gradient=false)
int ns__Canny(  struct soap *soap, 
			std::string InputMatFilename, double threshold1, double threshold2,
            int apertureSize=3, int L2gradient=0,
			std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	Mat dst;
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "Canny :: can not read bin file for src" << std::endl;
        return soap_receiver_fault(soap, "Canny :: can not read bin file for src", NULL);
    }
    
    Canny(src, dst, threshold1, threshold2, apertureSize, L2gradient);
    
	std::string toAppend = "_Canny";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "Canny :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "Canny :: can not save mat to binary file", NULL);
    }

    src.release();
	dst.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "Canny :: " << "time elapsed " << end-start << std::endl;
	}
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "Canny :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}
    return SOAP_OK;
}

//~ std::vector<std::vector<cv::Point>> contours;
	//~ cv::findContours(image, 
		//~ contours, // a vector of contours 
		//~ CV_RETR_EXTERNAL, // retrieve the external contours
		//~ CV_CHAIN_APPROX_NONE); // retrieve all pixels of each contours
//~ 
	//~ // Print contours' length
	//~ std::cout << "Contours: " << contours.size() << std::endl;
	//~ std::vector<std::vector<cv::Point>>::const_iterator itContours= contours.begin();
	//~ for ( ; itContours!=contours.end(); ++itContours) {
//~ 
		//~ std::cout << "Size: " << itContours->size() << std::endl;
	//~ }
//~ 
	//~ // draw black contours on white image
	//~ cv::Mat result(image.size(),CV_8U,cv::Scalar(255));
	//~ cv::drawContours(result,contours,
		//~ -1, // draw all contours
		//~ cv::Scalar(0), // in black
		//~ 2); // with a thickness of 2

//~ void findContours(InputOutputArray image, OutputArrayOfArrays contours, OutputArray hierarchy, int mode, int method, Point offset=Point())
int ns__findContours(  struct soap *soap, 
			std::string InputMatFilename, int mode, int method,
            int offsetX_D=0, int offsetY_D=0
			std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	Mat dst;
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "Canny :: can not read bin file for src" << std::endl;
        return soap_receiver_fault(soap, "Canny :: can not read bin file for src", NULL);
    }
    
    Canny(src, dst, threshold1, threshold2, apertureSize, L2gradient);
    
	std::string toAppend = "_Canny";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "Canny :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "Canny :: can not save mat to binary file", NULL);
    }

    src.release();
	dst.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "Canny :: " << "time elapsed " << end-start << std::endl;
	}
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "Canny :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}
    return SOAP_OK;
}



/* ########################################################### */
/* ###############         helper function        ############ */
/* ########################################################### */

/* Save matrix to binary file */
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
       return 0;
    }
    out.close();
    return 1;
}

/* Read matrix from binary file */
int readMat( const std::string& filename, Mat& M)
{
    std::ifstream in(filename.c_str(), std::ios::in | std::ios::binary);
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

int getMatType ( const std::string& typeName)
{
    if(typeName.compare("CV_8UC1") == 0)
        return CV_8UC1;
    else if(typeName.compare("CV_8UC2") == 0)
        return CV_8UC2;
    else if(typeName.compare("CV_8UC3") == 0)
        return CV_8UC3;
    else if(typeName.compare("CV_32FC1") == 0)
        return CV_32FC1;
    else if(typeName.compare("CV_32FC2") == 0)
        return CV_32FC2;
    else if(typeName.compare("CV_32FC3") == 0)
        return CV_32FC3;
    else return -1;

}

int getMatDepth (const std::string& typeName)
{
    if(typeName.compare("CV_8U") == 0) return CV_8U;	
	else if(typeName.compare("CV_8S") == 0) return CV_8S;
	else if(typeName.compare("CV_16U") == 0) return CV_16U;
	else if(typeName.compare("CV_16S") == 0) return CV_16S;
	else if(typeName.compare("CV_32S") == 0) return CV_32S;
	else if(typeName.compare("CV_32F") == 0) return CV_32F;
	else if(typeName.compare("CV_64F") == 0) return CV_64F;
    else return -1;
    
}

int getThresholdType ( const std::string& typeName)
{
	if (typeName.compare("THRESH_BINARY") == 0)
        return THRESH_BINARY;
    else if (typeName.compare("THRESH_BINARY_INV") == 0)
        return THRESH_BINARY_INV;
    else if (typeName.compare("THRESH_TRUNC") == 0)
        return THRESH_TRUNC;
    else if (typeName.compare("THRESH_TOZERO") == 0)
        return THRESH_TOZERO;
    else if (typeName.compare("THRESH_TOZERO_INV") == 0)
        return THRESH_TOZERO_INV;
    else return -1;
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

int getMorphOperation ( const std::string& typeName)
{
    if (typeName.compare("MORPH_OPEN") == 0)
        return MORPH_OPEN;
    else if (typeName.compare("MORPH_CLOSE") == 0)
        return MORPH_CLOSE;
    else if (typeName.compare("MORPH_GRADIENT") == 0)
        return MORPH_GRADIENT;
    else if (typeName.compare("MORPH_TOPHAT") == 0)
        return MORPH_TOPHAT;
    else if (typeName.compare("MORPH_BLACKHAT") == 0)
        return MORPH_BLACKHAT;
    else return -1;
}

int ByteArrayToANN(std::string& annfile, CvANN_MLP* ann)
{
    char *buffer;
    long size;
	std::ifstream file (annfile.c_str(), std::ios::in|std::ios::binary|std::ios::ate);
    if(!file){ return 0; }

    size = file.tellg();
    file.seekg (0, std::ios::beg);
    buffer = new char [size];
    file.read (buffer, size);
    file.close();

	CvFileStorage *cvfs = cvOpenFileStorage(annfile.c_str(), NULL, CV_STORAGE_READ);
	if (cvfs != NULL) {
		ann->read(cvfs, cvGetFileNodeByName(cvfs, NULL, "CIA_Neuron"));
		cvReleaseFileStorage(&cvfs);
	} else {
        return 0;
    }
}

void getOutputFilename (std::string& filename, std::string& toAppend=ERROR_FILENAME)
{
	char tmp[60] = {0};
    time_t now = time(0);
    strftime(tmp, sizeof(tmp),"%Y%m%d_%H%M%S", localtime(&now));
	filename = BASE_DIR + tmp + toAppend;
}

void getMemoryUsage (double& vm_usage, double& resident_set)
{
	/* virtual mamory usage */
	vm_usage     = 0.0;
	/* The resident set size is the portion of a process's memory that is held in RAM */
	resident_set = 0.0;

	std::ifstream stat_stream("/proc/self/stat",std::ios::in);
	std::string pid, comm, state, ppid, pgrp, session, tty_nr;
	std::string tpgid, flags, minflt, cminflt, majflt, cmajflt;
	std::string utime, stime, cutime, cstime, priority, nice;
	std::string O, itrealvalue, starttime;

	unsigned long vsize;
	long rss;

	stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr
			   >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt
			   >> utime >> stime >> cutime >> cstime >> priority >> nice
			   >> O >> itrealvalue >> starttime >> vsize >> rss;

	stat_stream.close();

	long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
	vm_usage     = vsize / 1024.0;
	resident_set = rss * page_size_kb;
}

void getConfig (bool &timeChecking, bool &memoryChecking)
{
	ConfigFile cfg( CONFIG_FILE.c_str() );
	timeChecking = cfg.getValueOfKey<bool>("timeChecking", false);
	memoryChecking = cfg.getValueOfKey<bool>("memoryChecking", false);
}

int getBorderType(std::string& borderType_D)
{
    if(borderType_D.compare("BORDER_CONSTANT")==0) return BORDER_CONSTANT;
    else if(borderType_D.compare("BORDER_REPLICATE")==0) return BORDER_REPLICATE;
    else if(borderType_D.compare("BORDER_ISOLATED")==0) return BORDER_ISOLATED;
    else if(borderType_D.compare("BORDER_REFLECT")==0) return BORDER_REFLECT;
    else if(borderType_D.compare("BORDER_REFLECT_101")==0) return BORDER_REFLECT_101;
    else if(borderType_D.compare("BORDER_WRAP")==0) return BORDER_WRAP;
    else return -1;
}

int getInterpolation (const std::string& inter)
{
    if(inter.compare("INTER_NEAREST")==0) return INTER_NEAREST;
    else if(inter.compare("INTER_LINEAR")==0) return INTER_LINEAR;
    else if(inter.compare("INTER_AREA")==0) return INTER_AREA;
    else if(inter.compare("INTER_CUBIC")==0) return INTER_CUBIC;
    else return -1;
}

int getContourMode (const std::string& mode)
{
    if(mode.compare("CV_RETR_EXTERNAL")==0) return CV_RETR_EXTERNAL;
    else if(mode.compare("CV_RETR_LIST")==0) return CV_RETR_LIST;
    else if(mode.compare("CV_RETR_CCOMP")==0) return CV_RETR_CCOMP;
    else if(mode.compare("CV_RETR_TREE")==0) return CV_RETR_TREE;
    else return -1;

}
