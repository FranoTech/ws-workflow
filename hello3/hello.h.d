//gsoap h service name: hello simple hello
//gsoap h service style: rpc
//gsoap h service encoding: encoded
//gsoap h service namespace: http://localhost/hello.wsdl
//gsoap h service location: http://localhost/cgi-bin/hello

//gsoap h schema namespace: urn:hello 

//gsoap h service method-documentation: print hello 
int  h_hello(struct soap *, char*&);
