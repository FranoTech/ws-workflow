//gsoap ns service name: name	
//gsoap ns service style: rpc
//gsoap ns service encoding: encoded
//gsoap ns service namespace: http://localhost/name.wsdl
//gsoap ns service location: http://localhost/cgi-bin/name

//gsoap ns schema namespace: urn:n

class ns__Output
{ 
	char *outputFilename;
	char *anotherOutputFilename;
};

int ns__genName(char *InputFilename, char *&OutputFilename);
int ns__genName2(char *InputFilename, char **OutputFilename);
int ns__genName3(char *InputFilename, ns__Output &out);
//int ns__genName4(struct soap *soap, char *InputFilename, char *OutputFilename)
