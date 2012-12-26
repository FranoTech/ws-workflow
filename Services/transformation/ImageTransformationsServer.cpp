#include "../headerfile.cpp"
#include "../myLog.h"
#include "../config.h"
#include "soapH.h"
#include "Image_Transformations.nsmap"

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

int getThresholdType (const std::string& typeName);



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

