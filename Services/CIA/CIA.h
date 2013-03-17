//gsoap ns service name: CIA
//gsoap ns service style: rpc
//gsoap ns service encoding: encoded
//gsoap ns service location: http://localhost/cgi-bin/CIAServer

//gsoap ns schema namespace: urn:mali


class ns__RemoveSmallCell
{ 
	char *keepedArea;
	char *biggerArea;
};

class ns__base64Binary
{ unsigned char *__ptr;
  int __size;
};

int ns__removeSmallCell(char *inputMatFilename, ns__RemoveSmallCell &out);
int ns__scanningCell(char *biggerArea, char *keepArea, char **OutputMatFilename);
int ns__trainANN(char *inputMatFilename, char *neuralFile, char **OutputMatFilename);
int ns__separateCell(char *input1, char *input2, char **OutputMatFilename);
int ns__prepareResult(char *inputMatFilename, char *afterthresNN, char **OutputMatFilename);
int ns__viewImage(char *inputMatFilename, ns__base64Binary &image);



//~ int ns__colorRatioMethod(char *inputMatFilename, char **OutputMatFilename);
