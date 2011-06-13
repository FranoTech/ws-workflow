#include "soaphelloService.h"
#include "hello.nsmap" 
#include <cstring>
#include <string>
#include <sstream>
#include <cstdlib>
#include <unistd.h>
using namespace std;

int main(int argc, char **argv)
{ helloService hello;
  if (argc < 2)
    hello.serve();       /* serve as CGI application */
  else
  { int port = atoi(argv[1]);
    if (!port)
    { fprintf(stderr, "Usage: <port>\n");
      exit(0);
    }
    /* run iterative server on port until fatal error */
    if (hello.run(port))
    { hello.soap_stream_fault(std::cerr);
      exit(-1);
    }   
  }
  return 0;
} 
/*
int helloService::hello(struct soap *soap, char*&s)
{
	s = new char[256];
  	cerr<<"test:" <<endl;
 	string tmp;
  	tmp = "hello world ";
    strcat(s,tmp.c_str());
	fork();
	for (int i =0 ; i< 10 ; i++){
		sleep(20);
	}	
    return SOAP_OK;
} 
*/


int helloService::hello(struct soap *soap, char*&s)
{
	s = new char[256];
  	cerr<<"test:" <<endl;
 	string tmp;
  	tmp = "hello world ";
        strcat(s,tmp.c_str());
	fork();
	for (int i =0 ; i< 10 ; i++){
		sleep(20);
	}	
    return SOAP_OK;
} 
