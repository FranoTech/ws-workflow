#include "../headerfile.cpp"
#include "../myLog.h"
#include "../config.h"
#include "soapH.h"
#include "highGUI.nsmap"

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
        Log(logERROR) << "imRead :: can not load image" << std::endl;
        return soap_receiver_fault(soap, "imRead :: can not load image", NULL);
    }

	/* generate output file name  and save to bin*/
	std::string toAppend = "_imRead";
	getOutputFilename(OutputMatFilename,toAppend);

    if(!saveMat(OutputMatFilename, src))
    {
        Log(logERROR) << "imRead :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "imRead :: can not save mat to binary file", NULL);
    }

    src.release();
	
	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "imRead :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "imRead :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}
	
    return SOAP_OK;
}


int ns__imWrite (struct soap *soap, std::string InputMatFilename, std::string fileExtension=DEFAULTVAL, 
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
    
    if(fileExtension == DEFAULTVAL) fileExtension = ".jpg" ;

    /* generate output file name */
    getOutputFilename(OutputMatFilename, fileExtension);

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



