#include "soaphelloService.h"
#include "hello.nsmap" 
#include <cstring>
#include <string>
//#include <omp.h>

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
  //#pragma parallel 
{ 
  string tmp;
  strcpy(s,"Hello World123");
  ostringstream os;
//  os << omp_get_thread_num();
  tmp = os.str();
  strcpy(s,tmp.c_str());

  strcpy(s,"\n");
}
 return SOAP_OK;
} 
