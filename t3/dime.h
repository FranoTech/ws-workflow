//gsoap ns service name: dime
//gsoap ns service style: rpc
//gsoap ns service encoding: encoded
//gsoap ns service namespace: http://localhost/dime.wsdl
//gsoap ns service location: http://localhost/cgi-bin/dimeserver

//gsoap ns schema namespace: urn:dime


class ns__base64Binary
{ unsigned char *__ptr;
  int __size;
  //char *id;
  //char *type;
  //char *options;
};

int ns__getImage(char *name, ns__base64Binary &image);
