#include "../headerfile.cpp"
#include "../myLog.h"
#include "../config.h"
#include "soapH.h"
#include "Basic_Structures.nsmap"

#define FILENAME_SIZE 75
#define MAX_THREAD 4

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


int ns__createMat(  struct soap *soap, 
			int rows=0, int cols=0,
			std::string type=DEFAULTVAL,
            int scalar_=-1,
			std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;	
	int matType = type == DEFAULTVAL? CV_8U : getMatDepth(type);

    
	if(rows != 0 && cols != 0)
    {
        
        if( scalar_ != -1){
            try{
                src = Mat(Size(rows, cols), matType, cv::Scalar(scalar_));
            } catch( cv::Exception& e ) {
            Log(logERROR) << e.what() << std::endl;
            return soap_receiver_fault(soap, e.what(), NULL);
            }
        } else {
            try{
                src.create(rows, cols, matType);
            } catch( cv::Exception& e ) {
                Log(logERROR) << e.what() << std::endl;
                return soap_receiver_fault(soap, e.what(), NULL);
            }
		}
        
	}else {
		Log(logERROR) << "createMat :: Invalid input, please enter rows or cols again." << std::endl;
        return soap_receiver_fault(soap, "createMat :: Invalid input, please enter rows or cols again.", NULL);
	}
	
	std::string toAppend = "_createMat";
    getOutputFilename(OutputMatFilename, toAppend);
    Log(logDEBUG)<< "OutputMatFilename :"<<OutputMatFilename<<std::endl;
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
		Log(logERROR) << "getMatDetail :: can not read bin file for src" << std::endl;
        return soap_receiver_fault(soap, "getMatDetail :: can not read bin file for src", NULL);
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
		Log(logINFO) << "getMatDetail :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "getMatDetail :: VM usage :" << vm << std::endl 
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
	
    Mat dst = Mat(src.size(), src.type());
    Log(logDEBUG) << "src type :" << src.type() << std::endl;
    Log(logDEBUG) << "Another mat type :" << anotherMat.type() << std::endl;
    Log(logDEBUG) << "dst type :" << dst.type() << std::endl;
    
    try{
        dst = src.mul(anotherMat,scale_D);
    } catch( cv::Exception& e ) {
        Log(logERROR) << e.what() << std::endl;
        return soap_receiver_fault(soap, e.what(), NULL);
    }
    
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
	try{
        dst = src.cross(anotherMat);
    } catch( cv::Exception& e ) {
        Log(logERROR) << e.what() << std::endl;
        return soap_receiver_fault(soap, e.what(), NULL);
    }
    
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
	
    try{
        dst = src.dot(anotherMat);
    } catch( cv::Exception& e ) {
        Log(logERROR) << e.what() << std::endl;
        return soap_receiver_fault(soap, e.what(), NULL);
    }
    
    

	std::string toAppend = "_dot";
    getOutputFilename(OutputMatFilename, toAppend);
    
    if(dst.empty()){
        Log(logERROR) << "dot :: Dot product is retrun empty result" << std::endl;
        return soap_receiver_fault(soap, "dot :: Dot product is retrun empty result", NULL);
    }
    
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
        try{
            src = Mat::zeros(rows, cols, matType);
        } catch( cv::Exception& e ) {
            Log(logERROR) << e.what() << std::endl;
            return soap_receiver_fault(soap, e.what(), NULL);
        }
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
		Log(logERROR) << "printAllMatValue :: can not read bin file for src" << std::endl;
        return soap_receiver_fault(soap, "printAllMatValue :: can not read bin file for src", NULL);
    }
    
    std::stringstream ss;    
    ss << src;
    OutputMat = ss.str();
    
    src.release();
    
    if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "printAllMatValue :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "printAllMatValue :: VM usage :" << vm << std::endl 
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
        Log(logERROR) << "saveMat :: Mat is empty" << std::endl;
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








