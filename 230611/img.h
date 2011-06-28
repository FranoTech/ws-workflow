//gsoap ns service name: img	
//gsoap ns service style: rpc
//gsoap ns service encoding: encoded
//gsoap ns service namespace: http://localhost/img.wsdl
//gsoap ns service location: http://localhost/cgi-bin/imgSrv

//gsoap ns schema namespace: urn:img


struct ns__ImageData
{ 
	int sharedKey;
	int imgHeight;
	int imgWidth;
};


int ns__Ipl1ChToMat(char *InputFilename, struct ns__ImageData &out);
int ns__BinaryThreshold(struct ns__ImageData *in, double threshold, double maxValue,struct ns__ImageData &out);
int ns__MorphOpen(char *InputFilename, char *filename, char *&OutputFilename);
