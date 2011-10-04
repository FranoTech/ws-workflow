//gsoap ns service name:	calc Simple calculator service
//gsoap ns service style:	rpc
//gsoap ns service encoding:	encoded
//gsoap ns service namespace:	http://localhost/calc.wsdl
//gsoap ns service location:	http://localhost/cgi-bin/calcserver

//gsoap ns schema namespace:	urn:calc

//gsoap ns service method-documentation: add Sums two values
int ns__add(double a=10, double b=12, double *result=0);
int ns__test(char* s, int i, char** t);

