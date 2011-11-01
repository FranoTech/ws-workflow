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
//gsoap ns service method-documentation: colorflag : 0 = CV_LOAD_IMAGE_GRAYSCALE, 1 = CV_LOAD_IMAGE_COLOR, -1 = CV_LOAD_IMAGE_UNCHANGED
int ns__loadMat (char *InputImageFilename, int colorflag=0, char *types="CV_32FC1", char **OutputMatFilename=NULL);
int ns__MatToJPG (char *InputMatFilename, char **OutputMatFilename);
int ns__ConvertTo(char *InputMatFilename, char *types="CV_32FC1", char **OutputMatFilename=NULL);
int ns__Threshold(char *InputMatFilename, double thresholdValue=127.0, double maxValue=255.0, char *thresholdType="THRESH_BINARY", char **OutputMatFilename=NULL);

