//06.06.2011
//gsoap ns service name: CIA	
//gsoap ns service style: rpc
//gsoap ns service encoding: encoded
//gsoap ns service namespace: http://localhost/CIA.wsdl
//gsoap ns service location: http://localhost/cgi-bin/CIAServer

//gsoap ns schema namespace: urn:img

class ns__ImageData
{ 
	int __key;
	int __size;
};

int ns__Ipl1ChToMat(char* InputFilename, ns__ImageData &output);
//int ns__MatToIpl1Ch(void *_, ns__ImageData &output);
int ns__BinaryThreshold(double threshold, double maxValue, ns__ImageData &output);
int ns__MorphOpen(void *_, ns__ImageData &output);

