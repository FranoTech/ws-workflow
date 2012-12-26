#include "../headerfile.cpp"
#include "../myLog.h"
#include "../config.h"
#include "soapH.h"
#include "Image_Filtering.nsmap"

using namespace cv;

/* helper function */
int saveMat( const std::string& filename, const Mat& M);
int readMat( const std::string& filename, Mat& M);
int getMatType (const std::string& typeName);
int getColorFlag(int colorflag);
void getOutputFilename (std::string& filename, std::string& toAppend);
void getMemoryUsage (double& vm_usage, double& resident_set);
void getConfig (bool &timeChecking, bool &memoryChecking);
int getMatDepth (const std::string& depth);
bool fileExists(const std::string& filename)
{
    struct stat buf;
    if (stat(filename.c_str(), &buf) != -1)
    {
        return true;
    }
    return false;
}

template <typename T>
std::string NumberToString ( T Number )
{
	std::stringstream ss;
	ss << Number;
	return ss.str();
}

int getMorphOperation ( const std::string& typeName);
int getBorderType(std::string& bdType);
int getInterpolation (const std::string& inter);

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

//~ void morphologyEx(InputArray src, OutputArray dst, int op, InputArray kernel, Point anchor=Point(-1,-1), int iterations=1, int borderType=BORDER_CONSTANT, const Scalar& borderValue=morphologyDefaultBorderValue() )¶

int ns__MorphologyEx( struct soap *soap,
						std::string InputMatFilename,
						std::string morphOperation=DEFAULTVAL,
                        std::string StructuringElementFname=ERROR_FILENAME,
                        int iteration_D=1, 
                        int anchorX_D=-1, int anchorY_D=-1,
                        //~ std::string borderType_D=DEFAULTVAL,
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

    int morphOpt = morphOperation == DEFAULTVAL ? MORPH_OPEN : getMorphOperation(morphOperation);
    Point seAnc(anchorX_D, anchorY_D);
    
    if(StructuringElementFname.compare(ERROR_FILENAME)==0)
    { 
        Log(logERROR) << "MorphologyEx :: Please enter kernel filename" << std::endl;
        return soap_receiver_fault(soap, "MorphologyEx :: Please enter kernel filename", NULL);
        
    } else {
            Mat se;
            if(!readMat(StructuringElementFname, se))
            {
                Log(logERROR) << "MorphologyEx :: can not read bin file for Structuring element" << std::endl;
                return soap_receiver_fault(soap, "MorphologyEx :: can not read bin file for Structuring element", NULL);
            }

            try{
                morphologyEx(src, dst, morphOpt, se, seAnc, iteration_D);
            } catch( cv::Exception& e ) {
            Log(logERROR) << e.what() << std::endl;
            return soap_receiver_fault(soap, e.what(), NULL);
            }

    }

    std::string toAppend = "_MorphologyEx";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "MorphologyEx :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "MorphologyEx :: can not save mat to binary file", NULL);
    }

    src.release();
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
        
        try{
            erode(src, dst, Mat(), Point(anchorX_D, anchorY_D), iteration_D, border);
        } catch( cv::Exception& e ) {
        Log(logERROR) << e.what() << std::endl;
        return soap_receiver_fault(soap, e.what(), NULL);
        }
        
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
        try{
            dilate(src, dst, Mat(), Point(anchorX_D, anchorY_D), iteration_D, border);
        } catch( cv::Exception& e ) {
            Log(logERROR) << e.what() << std::endl;
            return soap_receiver_fault(soap, e.what(), NULL);
        }
        
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

int ns__medianBlur(  struct soap *soap, 
			std::string InputMatFilename, int kSize=3,
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
    try{
    pyrUp(src, dst, Size(rows,cols), border);
    } catch( cv::Exception& e ) {
        Log(logERROR) << e.what() << std::endl;
        return soap_receiver_fault(soap, e.what(), NULL);
    }

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

/* void blur(InputArray src, OutputArray dst, Size ksize, Point anchor=Point(-1,-1), int borderType=BORDER_DEFAULT ) */

int ns__blur(  struct soap *soap, 
			std::string InputMatFilename, int kernelRows=1, int kernelCols=1, 
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
    
    int border = borderType_D == DEFAULTVAL ? BORDER_DEFAULT : getBorderType(borderType_D);
    
    Size kSize(kernelRows, kernelCols);
    Log(logDEBUG)<< "kSize " << kernelRows << "   " << kernelCols <<std::endl;
    Log(logDEBUG)<< "anchorX_D, anchorY_D " << anchorX_D << " " << anchorY_D <<std::endl;
    
    
    try{
        blur(src, dst, kSize, Point(anchorX_D, anchorY_D), border); 
    } catch( cv::Exception& e ) {
        Log(logERROR) << e.what() << std::endl;
        return soap_receiver_fault(soap, e.what(), NULL);
    }
    
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
    int border = borderType_D == DEFAULTVAL ? BORDER_DEFAULT : getBorderType(borderType_D);
    
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

//~ void Sobel(InputArray src, OutputArray dst, int ddepth, int dx, int dy, int ksize=3, double scale=1, double delta=0, int borderType=BORDER_DEFAULT )
int ns__Sobel(  struct soap *soap, 
			std::string InputMatFilename, std::string ddepth=DEFAULTVAL, 
            int kSize_D=3, double scale_D=1, double delta_D=0, 
            int dx=1, int dy=0, std::string borderType_D=DEFAULTVAL,
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
    
    int border = borderType_D == DEFAULTVAL ? BORDER_DEFAULT : getBorderType(borderType_D);
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


void getOutputFilename (std::string& filename, std::string& toAppend=ERROR_FILENAME)
{
	char tmp[60] = {0};
    time_t now = time(0);
    strftime(tmp, sizeof(tmp),"%Y%m%d_%H%M%S", localtime(&now));
	filename = BASE_DIR + tmp + toAppend;
    if(fileExists(filename)){
        filename += NumberToString(rand() % 10);
    }
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
    
    if(borderType_D.compare("BORDER_DEFAULT")==0) return BORDER_DEFAULT;
    else if(borderType_D.compare("BORDER_CONSTANT")==0) return BORDER_CONSTANT;
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



