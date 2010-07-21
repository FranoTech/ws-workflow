#include "soapH.h"
#include "dime.nsmap"
#include <iostream>
//#include <pthread.h>

using namespace std;
#define BACKLOG (100)	// Max. request backlog
#define MAX_FILE_SIZE (10000)	// Max. file size

//void *process_request(void*);

int main(int argc, char **argv)
{ struct soap soap;
  soap_init(&soap);
  if (argc < 2)		// no args: assume this is a CGI application
  { soap_serve(&soap);	// serve request
    soap_destroy(&soap);// cleanup class instances
    soap_end(&soap);	// cleanup
  }/*
  else
  { struct soap *tsoap;
    pthread_t tid;
    int port;
    int m, s, i;
    port = atoi(argv[2]);
    m = soap_bind(&soap, NULL, port, BACKLOG);
    if (m < 0)
      exit(-1);
    fprintf(stderr, "Socket connection successful %d\n", m);
    for (i = 1; ; i++)
    { s = soap_accept(&soap);
      if (s < 0)
        break;
      fprintf(stderr, "Thread %d accepts socket %d connection from IP %d.%d.%d.%d\n", i, s, (int)(soap.ip>>24)&0xFF, (int)(soap.ip>>16)&0xFF, (int)(soap.ip>>8)&0xFF, (int)soap.ip&0xFF);
      tsoap = soap_new();
      tsoap->socket = s;
      pthread_create(&tid, NULL, (void*(*)(void*))process_request, (void*)tsoap);
    }
  }*/
  return 0;
}
/*
void *process_request(void *soap)
{ pthread_detach(pthread_self());
  soap_serve((struct soap*)soap);
  soap_destroy((struct soap*)soap);
  soap_end((struct soap*)soap);
  free(soap);
  return NULL;
}
*/
int ns__getImage(struct soap *soap, char *name, ns__base64Binary &image)
{ if (name)
  { 
    cerr<<"In if"<<endl;
    FILE *fd = fopen(name, "r");
    int i, c;
    if (!fd)
    { soap_fault(soap);
      cerr<<"Can not open file"<<endl;
      soap->fault->faultstring = "Cannot open file";
      return SOAP_FAULT;
    }
    image.__ptr = (unsigned char*)soap_malloc(soap, MAX_FILE_SIZE);
    for (i = 0; i < MAX_FILE_SIZE; i++)
    { if ((c = fgetc(fd)) == EOF)
        break;
      image.__ptr[i] = c;
    }
    image.__size = i;
    //image.type = "image/jpeg";
    //image.options = soap_dime_option(soap, 0, "My picture");
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
