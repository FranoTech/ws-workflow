#include <iostream>
#include <omp.h>
#include "soapH.h"
#include "fhasai.nsmap"

using namespace std;
#define BASE_DIR "/home/lluu/dir/"

void editHello (char **h, const char*a);

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

int ns__SayHello(struct soap *soap, char* name, char **hello)
{
    *hello = (char*)soap_malloc(soap, 60);
    editHello(hello);
    return SOAP_OK  ;
    
 }    


//*OutputMatFilename = (char*)soap_malloc(soap, FILENAME_SIZE);
//time_t now = time(0);
//strftime(*OutputMatFilename, sizeof(OutputMatFilename)*FILENAME_SIZE, "/home/lluu/dir/%Y%m%d_%H%M%S_LoadMat", localtime(&now));
	

void editHello (char **h, const char *a=NULL)
{
    
    time_t now = time(0);
    strftime(*h, sizeof(h)*60, BASE_DIR"%Y%m%d_%H%M%S_Hello", localtime(&now));
    //strcat (*h,"_newnew");
    if(*a!= 0)
        strcat (*h,a);
}
