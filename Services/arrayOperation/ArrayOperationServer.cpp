#include "../headerfile.cpp"
#include "../myLog.h"
#include "../config.h"
#include "soapH.h"
#include "Array_Operation.nsmap"

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
        try{
            add(src1, src2, dst, noArray(), dtype_D);
        } catch( cv::Exception& e ) {
        Log(logERROR) << e.what() << std::endl;
        return soap_receiver_fault(soap, e.what(), NULL);
        }
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
        try{
             subtract(src1, src2, dst, noArray(), dtype_D);
        } catch( cv::Exception& e ) {
        Log(logERROR) << e.what() << std::endl;
        return soap_receiver_fault(soap, e.what(), NULL);
        }
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
    try{
        dst = abs(src);
    } catch( cv::Exception& e ) {
        Log(logERROR) << e.what() << std::endl;
        return soap_receiver_fault(soap, e.what(), NULL);
    }   	
		
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
    
    try{
        absdiff(src1, src2, dst);
    } catch( cv::Exception& e ) {
        Log(logERROR) << e.what() << std::endl;
        return soap_receiver_fault(soap, e.what(), NULL);
    }   	
	
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

    try{
        sqrt(src, dst);
    } catch( cv::Exception& e ) {
        Log(logERROR) << e.what() << std::endl;
        return soap_receiver_fault(soap, e.what(), NULL);
    }    
	
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
    
    try{
        bitwise_and(matSrc1, matSrc2, dst);
    } catch( cv::Exception& e ) {
        Log(logERROR) << e.what() << std::endl;
        return soap_receiver_fault(soap, e.what(), NULL);
    }   	
	
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
    
    try{
        bitwise_not(matSrc, matSrc);
    } catch( cv::Exception& e ) {
        Log(logERROR) << e.what() << std::endl;
        return soap_receiver_fault(soap, e.what(), NULL);
    }   	
	
    
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






