//gsoap ns service name: standAlone
//gsoap ns service style: rpc
//gsoap ns service encoding: encoded
//gsoap ns service namespace: http://localhost/standAlone.wsdl
//gsoap ns service location: http://localhost:8080

//gsoap ns schema namespace: urn:standAlone


class ns__RemoveSmallCell
{ 
	char *keepedArea;
	char *biggerArea;
};

class ns__base64Binary
{ unsigned char *__ptr;
  int __size;
};

int ns__loadMat (char *InputImageFilename, int colorflag=0, char *types="CV_32FC1", char **OutputMatFilename=NULL);
int ns__MatToJPG (char *InputMatFilename, char **OutputMatFilename);
int ns__convertTo(char *InputMatFilename, char *types="CV_32FC1", char **OutputMatFilename=NULL);
int ns__threshold(char *InputMatFilename, double thresholdValue=127.0, double maxValue=255.0, char *thresholdType="THRESH_BINARY", char **OutputMatFilename=NULL);
int ns__morphologyEx(char *InputMatFilename, char *morphOperation="MORPH_OPEN", char **OutputMatFilename=NULL);
int ns__erode(char *InputMatFilename, char *elementFilename, int iteration=1, char **OutputMatFilename=NULL);
int ns__dilate(char *InputMatFilename, char *elementFilename, int iteration=1, char **OutputMatFilename=NULL);
int ns__bitwiseOr(char *src1, char *src2, char **OutputMatFilename);
int ns__bitwiseAnd(char *src1, char *src2, char **OutputMatFilename);
int ns__bitwiseNot(char *src, char **OutputMatFilename);
int ns__removeSmallCell(char *inputMatFilename, ns__RemoveSmallCell &out);
int ns__scanningCell(char *biggerArea, char *keepArea, char **OutputMatFilename);
int ns__trainANN(char *inputMatFilename, char *neuralFile, char **OutputMatFilename);
int ns__separateCell(char *input1, char *input2, char **OutputMatFilename);
int ns__prepareResult(char *inputMatFilename, char *afterthresNN, char **OutputMatFilename);
int ns__viewImage(char *inputMatFilename, ns__base64Binary &image);
