//gsoap ns service name: imgProcess	
//gsoap ns service style: rpc
//gsoap ns service encoding: encoded
//gsoap ns service namespace: http://localhost/imgProcess.wsdl
//gsoap ns service location: http://localhost/cgi-bin/imgProcessServer

//gsoap ns schema namespace: urn:img

class ns__ImageData
{ 
    int sharedKey;
	int imgHeight;
	int imgWidth;
};

int ns__Ipl1ChToMat(char *InputFilename, ns__ImageData &out);
//int ns__BinaryThreshold( double threshold, double maxValue,struct ns__ImageData &out);




