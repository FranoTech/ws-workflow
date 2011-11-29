//gsoap ns service name: mali
//gsoap ns service style: rpc
//gsoap ns service encoding: encoded
//gsoap ns service namespace: http://localhost/mali.wsdl
//gsoap ns service location: http://localhost/cgi-bin/maliServer

//gsoap ns schema namespace: urn:mali


class ns__RemoveSmallCell
{ 
	char *keepedArea;
	char *biggerArea;
};

int ns__loadMat (char *InputImageFilename, int colorflag=0, char *types="CV_32FC1", char **OutputMatFilename=NULL);
