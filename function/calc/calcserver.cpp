#include "soapH.h"
#include "calc.nsmap"

using namespace std;

int main(int argc, char **argv)
{ SOAP_SOCKET m, s; /* master and slave sockets */
  struct soap soap;
  soap_init(&soap);
  if (argc < 2)
    soap_serve(&soap);	/* serve as CGI application */
  else
  { m = soap_bind(&soap, NULL, atoi(argv[1]), 100);
    if (!soap_valid_socket(m))
    { soap_print_fault(&soap, stderr);
      exit(-1);
    }
    fprintf(stderr, "Socket connection successful: master socket = %d\n", m);
    for ( ; ; )
    { s = soap_accept(&soap);
      fprintf(stderr, "Socket connection successful: slave socket = %d\n", s);
      if (!soap_valid_socket(s))
      { soap_print_fault(&soap, stderr);
        exit(-1);
      } 
      soap_serve(&soap);
      soap_end(&soap);
    }
  }
  return 0;
} 

int ns__add(struct soap *soap, double a=10, double b=12, double *result=0)
{ 
	*result = a + b;
	return SOAP_OK;
} 

int ns__test(struct soap *soap, char* s=NULL, int i=10, char** t=NULL){
	if( *s != NULL )
		cerr<<"s ="<<*s<<endl;
	else
		cerr<<"s = NULL"<<endl;
	
	cerr<<"i = "<<i<<endl;
	*t = (char*)soap_malloc(soap, 20);
	*t = "Hello";
	return SOAP_OK;
}
	
