#include "soapH.h"
#include "dime.nsmap"
#include <iostream>

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
    cerr<<"In if"<<endl;
    FILE *fd = fopen(name, "r");
	
	fseek(fd,0,SEEK_END);
	int size = ftell(fd);
	fseek(fd,0,SEEK_SET);

    int i, c;
    if (!fd)
    { soap_fault(soap);
      cerr<<"Can not open file"<<endl;
      soap->fault->faultstring = "Cannot open file";
      return SOAP_FAULT;
    }
    image.__ptr = (unsigned char*)soap_malloc(soap, size);
    for (i = 0; i < size; i++)
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
