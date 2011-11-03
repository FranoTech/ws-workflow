//gsoap ns service name: imgProcess	
//gsoap ns service style: rpc
//gsoap ns service encoding: encoded
//gsoap ns service namespace: http://localhost/imgProcess.wsdl
//gsoap ns service location: http://localhost/cgi-bin/imgProcessServer

//gsoap ns schema namespace: urn:img


class ns__base64Binary
{ unsigned char *__ptr;
  int __size;
};

int ns__getImage(char *name, ns__base64Binary &image);
