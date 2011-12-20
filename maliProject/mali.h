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
int ns__MatToJPG (char *InputMatFilename, char **OutputMatFilename);
int ns__ConvertTo(char *InputMatFilename, char *types="CV_32FC1", char **OutputMatFilename=NULL);
int ns__Threshold(char *InputMatFilename, double thresholdValue=127.0, double maxValue=255.0, char *thresholdType="THRESH_BINARY", char **OutputMatFilename=NULL);
int ns__MorphologyEx(char *InputMatFilename, char *morphOperation="MORPH_OPEN", char **OutputMatFilename=NULL);
int ns__erode(char *InputMatFilename, char *elementFilename, int iteration=1, char **OutputMatFilename=NULL);
int ns__dilate(char *InputMatFilename, char *elementFilename, int iteration=1, char **OutputMatFilename=NULL);
int ns__Or(char *src1, char *src2, char **OutputMatFilename);
int ns__And(char *src1, char *src2, char **OutputMatFilename);
int ns__Not(char *src, char **OutputMatFilename);
int ns__removeSmallCell(char *inputMatFilename, ns__RemoveSmallCell &out);
int ns__scanningCell(char *biggerArea, char *keepArea, char **OutputMatFilename);
int ns__trainANN(char *inputMatFilename, char *neuralFile, char **OutputMatFilename);
int ns__separateCell(char *input1, char *input2, char **OutputMatFilename);
int ns__prepareResult(char *inputMatFilename, char *afterthresNN, char **OutputMatFilename);



//~ int ns__colorRatioMethod(char *inputMatFilename, char **OutputMatFilename);
