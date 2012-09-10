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

/* Global Configuration */
std::string BASE_DIR = "/home/lluu/thesis/result/";
std::string ERROR_FILENAME = "";
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
int ns__imgToMat (struct soap *soap,
                std::string InputMatFilename,
                int colorflag=0,
                std::string types="CV_8UC1",
                std::string &OutputMatFilename=ERROR_FILENAME)
{	
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* load image data */
	Mat src;
    src = imread(InputMatFilename.c_str(), getColorFlag(colorflag));
    if(src.empty()) {
        Log(logERROR) << "imgToMat :: can not load image" << std::endl;
        return soap_receiver_fault(soap, "imgToMat :: can not load image", NULL);
    }

    /* convert Mat to required type */
    if(src.type()!= getMatType(types))
    {
        src.convertTo(src,getMatType(types));
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
	Log(logDEBUG) << "MatToJPG :: Image has been loaded" << std::endl;

    /* check if it is not 8U then convert to 8UC(n) */
    int chan = src.channels();
	Log(logDEBUG) << "MatToJPG :: Image channel = " << chan << std::endl;
	Log(logDEBUG) << "MatToJPG :: Image type = " << src.type() << std::endl;
	
    if( src.type() != CV_8UC1|| src.type() != CV_8UC2 || src.type() != CV_8UC3 )
    {
		Log(logINFO) << "convert image from" << src.type() << " to " << CV_8UC(chan) << std::endl;
		src.convertTo(src, CV_8UC(chan));
		
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


int ns__ConvertTo( struct soap *soap, 
					std::string InputMatFilename,
					std::string types="CV_32FC1",
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

    int MatType = getMatType(types);
    int cols = src.cols ;

    if( src.type() != MatType )
    {
        src.convertTo(src, MatType);
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
                        std::string thresholdType="THRESH_BINARY",
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

    int threstype = getThresholdType (thresholdType);
    threshold(src, src, thresholdValue, maxValue, threstype);

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

int ns__MorphologyEx( struct soap *soap,
						std::string InputMatFilename,
						std::string morphOperation="MORPH_OPEN",
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
    Mat se;
    Size seSize(3, 3);
    Point seAnc(1, 1);
    int opt = getMorphOperation(morphOperation);

    se = getStructuringElement(MORPH_ELLIPSE, seSize, seAnc);
    morphologyEx(src, dst, opt, se, seAnc);

    if(src.empty()) {
			cerr << "MorphologyEx :: something's wrong" << endl;
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
				std::string elementFilename,
				int iteration=1,
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

    if(!readMat(elementFilename, element))
    {
		Log(logINFO) << "erode: use default element" << std::endl;
        element.release();
        erode(src, dst, Mat(), Point(-1, -1), iteration);
    } else {
		Log(logINFO) << "erode: use defined element" << std::endl;
        erode(src, dst, element, Point(-1, -1), iteration);
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

int ns__dilate(  struct soap *soap, 
				std::string InputMatFilename,
				std::string elementFilename,
				int iteration=1,
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

    if(!readMat(elementFilename, element))
    {
		Log(logINFO) << "dilate: use default element" << std::endl;
        element.release();
        dilate(src, dst, Mat(), Point(-1, -1), iteration);
    } else {
		Log(logINFO) << "dilate: use defined element" << std::endl;
        dilate(src, dst, element, Point(-1, -1), iteration);
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
        matSrc2.convertTo(matSrc2, srcType1);
	}

    Mat dst;
    bitwise_or(matSrc1, matSrc2, dst);

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
        matSrc2.convertTo(matSrc2, srcType1);
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
        matSrc2.convertTo(matSrc2, srcType1);
	}

    Mat dst;
    bitwise_xor(matSrc1, matSrc2, dst);

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
		Log(logERROR) << "Not :: can not read bin file for src1" << std::endl;
        return soap_receiver_fault(soap, "Not :: can not read bin file for src1", NULL);
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
		Log(logERROR) << "Inv:: can not read bin file for src1" << std::endl;
        return soap_receiver_fault(soap, "Inv :: can not read bin file for src1", NULL);
    }

    dst = src.inv();

	std::string toAppend = "_inv";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "Inv :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "Inv :: can not save mat to binary file", NULL);
    }

    matSrc.release();

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
		Log(logERROR) << "mul:: can not read bin file for src1" << std::endl;
        return soap_receiver_fault(soap, "mul :: can not read bin file for src1", NULL);
    }
	
    dst = src.mul(anotherMat);

	std::string toAppend = "_mul";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "mul :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "mul :: can not save mat to binary file", NULL);
    }

    matSrc.release();

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
        return 0;
    else if(typeName.compare("CV_8UC2") == 0)
        return 8;
    else if(typeName.compare("CV_8UC3") == 0)
        return 16;
    else if(typeName.compare("CV_32FC1") == 0)
        return 5;
    else if(typeName.compare("CV_32FC2") == 0)
        return 13;
    else if(typeName.compare("CV_32FC3") == 0)
        return 21;
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
    else if (typeName.compare("MORPH_TOPHAT") == 0)
        return MORPH_BLACKHAT;
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
	