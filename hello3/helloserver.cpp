#include "soaphelloService.h"
#include "hello.nsmap"

int main(int argc, char **argv)
{
	helloService hello;
	if(argc < 2)
		hello.serve();
	else
	{ int port = atoi(argv[1]);
    	  if (!port)
    		{ fprintf(stderr, "Usage: <port>\n");
      		exit(0);
    		}
    	  if (hello.run(port))
    	 	{ hello.soap_stream_fault(std::cerr);
      		exit(-1);
    		}
  	}
  	return 0;
}

void helloService::h__hello(struct soap *soap, char *&s) 
{ s = "Hello World!"; 
  return SOAP_OK; }

