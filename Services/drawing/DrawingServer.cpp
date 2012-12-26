#include "../headerfile.cpp"
#include "../myLog.h"
#include "../config.h"
#include "soapH.h"
#include "Drawing.nsmap"

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
int getBorderType(std::string& bdType);
int getMatDepth (const std::string& depth);
int getInterpolation (const std::string& inter);
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



