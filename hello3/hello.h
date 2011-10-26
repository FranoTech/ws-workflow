//gsoap ns service name:        hello Simple hello service
//gsoap ns service style:       rpc
//gsoap ns service encoding:    encoded
//gsoap ns service namespace:   http://localhost/hello.wsdl
//gsoap ns service location:    http://localhost/cgi-bin/helloserver
 
//gsoap ns schema namespace:    urn:hello

//gsoap ns service method-documentation: print hello
int ns__hello(struct soap*, char*&);

