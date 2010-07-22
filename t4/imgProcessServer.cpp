#include "soapH.h"
#include "imgProcess.nsmap"
#include <iostream>
#include "cv.h"
#include "highgui.h"

using namespace std;
#define MAX_FILE_SIZE (10000)	// Max. file size

int main(int argc, char **argv)
{ struct soap soap;
  soap_init(&soap);
  if (argc < 2)		// no args: assume this is a CGI application
  { soap_serve(&soap);	// serve request
    soap_destroy(&soap);// cleanup class instances
    soap_end(&soap);	// cleanup
  }
  return 0;
}

int ns__getImage(struct soap *soap, char *name, ns__base64Binary &image)
{ if (name)
  { 
    char *dest = "img2.jpg";
	IplImage* img = 0;
	img = cvLoadImage(name,0);

    if (!img)
    { 	soap_fault(soap);
      	cerr<<"Can not open file"<<endl;
      	soap->fault->faultstring = "Cannot open file";
      	return SOAP_FAULT;
    }

	if(!cvSaveImage(dest, img))
    { 	soap_fault(soap);
      	cerr<<"Can not save to new image"<<endl;
      	soap->fault->faultstring = "Cannot save to new image";
      	return SOAP_FAULT;
    }
	
    FILE *fd = fopen(dest, "r");
    int i, c;

    image.__ptr = (unsigned char*)soap_malloc(soap, MAX_FILE_SIZE);
    for (i = 0; i < MAX_FILE_SIZE; i++)
    { if ((c = fgetc(fd)) == EOF)
        break;
      image.__ptr[i] = c;
    }
    image.__size = i;
  }
  else
  { 
    cerr<<"Name require"<<endl;
    soap_fault(soap);
    soap->fault->faultstring = "Name required";
    return SOAP_FAULT;
  }
  return SOAP_OK;
}
