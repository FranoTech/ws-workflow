#include "soaphelloService.h"
#include "hello.nsmap" 
#include <cstring>
#include <string>
#include <omp.h>
#include <sstream>
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

int helloService::hello(struct soap *soap, char*&s)
{
	//static int a=0;
	s = new char[256];
	//char a [256]="123456";
	//s = a;
	//memset(a,0,256);
	//strcpy(s,"test test");
#pragma omp parallel 
{
  	cerr<<"test:" <<endl;
 	string tmp;
  	tmp = "hello from thread id: ";
  	ostringstream os;
  	os << omp_get_thread_num(); //<<" call num : "<<a++;
  	tmp = tmp+os.str()+" end ";
    strcat(s,tmp.c_str());
}


 return SOAP_OK;
} 
