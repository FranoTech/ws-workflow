//gsoap ns service name: imgProcess	
//gsoap ns service style: rpc
//gsoap ns service encoding: encoded
//gsoap ns service namespace: http://localhost/imgProcess.wsdl
//gsoap ns service location: http://localhost/cgi-bin/imgProcessServer

//gsoap ns schema namespace: urn:img


class ns__FindContours
{ 
	char *smallerArea;
	char *biggerArea;
};

class ns__RemoveSmallCell
{ 
	char *keepedArea;
	char *biggerArea;
};

int ns__loadMat (char *InputImageFilename, int loadparam, char *&OutputMatFilename);
int ns__binaryThreshold(char *InputMatFilename, double thresholdValue, double maxValue, char *&OutputMatFilename);
int ns__morphOpen(char *InpuMattFilename, char *&OutputMatFilename);
int ns__MatToJPG (char *InputMatFilename, char *&OutputMatFilename);
int ns__findContoursAndFillpoly (char *InputMatFilename, int lowerBound, ns__FindContours &out);
int ns__erode(char *src, char *element, int iteration=1, char **OutputMatFilename=NULL);
int ns__viewResult( char *src, struct ns__signalResponse { } *out );
