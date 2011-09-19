//gsoap ns service name: imgProcess	
//gsoap ns service style: rpc
//gsoap ns service encoding: encoded
//gsoap ns service namespace: http://localhost/imgProcess.wsdl
//gsoap ns service location: http://localhost/cgi-bin/imgProcessServer

//gsoap ns schema namespace: urn:img


class ns__Output
{ 
	char *&outputFilename;
	char *&anotherOutputFilename;
};

int ns__loadMat (char *InputImageFilename, int loadparam, char *&OutputMatFilename);
int ns__binaryThreshold(char *InputMatFilename, double thresholdValue, double maxValue, char *&OutputMatFilename);
int ns__morphOpen(char *InpuMattFilename, char *&OutputMatFilename);
int ns__MatToJPG (char *InputMatFilename, char *&OutputMatFilename);
int ns__findContoursAndFillPoly (char *InputMatFilename, int lowerBound,int UpperBound, Output &OutputMat);
