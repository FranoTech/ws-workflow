#include "soapH.h"
#include "name.nsmap"
#include <string>
#include <stdio.h>
#include <time.h>
#include <iostream>

using namespace std;

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

int ns__genName(struct soap *soap, char *InputFilename, char *&OutputFilename)
{ 
    //OutputFilename = new char[50];
    //*a = (char*)soap_malloc(soap, 11); 
    *&OutputFilename = (char*)soap_malloc(soap, 60); 
    if(InputFilename){
        cerr<<"1"<<endl;
        time_t now = time(0);
        strftime(OutputFilename, sizeof(OutputFilename)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_biThreshold.jpg", localtime(&now));
        cerr<<OutputFilename<<endl;
    }else{ 
        cerr<<"File Name require"<<endl;
        soap_fault(soap);
        soap->fault->faultstring = "Name required";
        return SOAP_FAULT;
    }
    return SOAP_OK;
}

int ns__genName2(struct soap *soap, char *InputFilename, char **OutputFilename)
{ 
    //OutputFilename = new char[50];
    //*a = (char*)soap_malloc(soap, 11); 
    *OutputFilename = (char*)soap_malloc(soap, 60); 
    if(InputFilename){
        cerr<<"1"<<endl;
        time_t now = time(0);
        strftime(*OutputFilename, sizeof(OutputFilename)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_biThreshold.jpg", localtime(&now));
        cerr<<*OutputFilename<<endl;
    }else{ 
        cerr<<"File Name require"<<endl;
        soap_fault(soap);
        soap->fault->faultstring = "Name required";
        return SOAP_FAULT;
    }
    return SOAP_OK;
}

//worked

int ns__genName3(struct soap *soap, char *InputFilename, ns__Output &out)
{ 
	out.outputFilename = (char*)soap_malloc(soap, 60);
	out.anotherOutputFilename = (char*)soap_malloc(soap, 60); 
    if(InputFilename){
        cerr<<"1"<<endl;
        time_t now = time(0);
        strftime(out.outputFilename, sizeof(out.outputFilename)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_biThreshold.jpg", localtime(&now));
        cerr<<out.outputFilename<<endl;
        
        now = time(0);
        strftime(out.anotherOutputFilename, sizeof(out.anotherOutputFilename)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_biThreshold.jpg", localtime(&now));
        cerr<<out.anotherOutputFilename<<endl;
    }else{ 
        cerr<<"File Name require"<<endl;
        soap_fault(soap);
        soap->fault->faultstring = "Name required";
        return SOAP_FAULT;
    }
    return SOAP_OK;
}

// not worked
//int ns__genName4(struct soap *soap, char *InputFilename, char *OutputFilename)
//{ 
    ////OutputFilename = new char[50];
    ////*a = (char*)soap_malloc(soap, 11); 
    //OutputFilename = (char*)soap_malloc(soap, 60); 
    //if(InputFilename){
        //cerr<<"1"<<endl;
        //time_t now = time(0);
        //strftime(OutputFilename, sizeof(OutputFilename)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_biThreshold.jpg", localtime(&now));
        //cerr<<*OutputFilename<<endl;
    //}else{ 
        //cerr<<"File Name require"<<endl;
        //soap_fault(soap);
        //soap->fault->faultstring = "Name required";
        //return SOAP_FAULT;
    //}
    //return SOAP_OK;
//}

