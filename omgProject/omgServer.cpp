/* *** TO-DO *** */
//~ *** redirect cerr to file -> macro

/* *** NOTE *** */
//~ omg is  a bit faster than mali (loadMat) 

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
int ns__loadMat (struct soap *soap,
                std::string InputImageFilename,
                int colorflag=0,
                std::string types="CV_32FC1",
                std::string &OutputMatFilename=ERROR_FILENAME)
{	
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	//~ if(timeChecking){
		double start, end;
		start = omp_get_wtime();
	//~ }
	
    Mat src;
	
    /* load image data */
    src = imread(InputImageFilename.c_str(), getColorFlag(colorflag));
    if(src.empty()) {
        Log(logERROR) << "loadMat:: can not load image" << std::endl;
        return soap_receiver_fault(soap, "loadMat :: can not load image", NULL);
    }

    /* convert Mat to required type */
    if(src.type()!= getMatType(types))
    {
        src.convertTo(src,getMatType(types));
    }

	/* generate output file name  and save to bin*/
	std::string toAppend = "_loadMat";
	getOutputFilename(OutputMatFilename,toAppend);

    if(!saveMat(OutputMatFilename, src))
    {
        Log(logERROR) << "loadMat:: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "loadMat:: can not save mat to binary file", NULL);
    }

    src.release();
	
	//~ if(timeChecking) 
	//~ { 
		end = omp_get_wtime();
		Log(logINFO) << "ns__loadMat " << "time elapsed " << end-start << std::endl;
	//~ }
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO) << "ns__loadMat VM usage :" << vm << std::endl << "Resident set size :" << rss << std::endl;
	}
	
    return SOAP_OK;
}


/* helper function */
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

/* cleared */
void getOutputFilename (std::string& filename, std::string& toAppend)
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
	