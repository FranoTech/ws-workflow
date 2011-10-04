//gsoap ns service name: imgProcess	
//gsoap ns service style: rpc
//gsoap ns service encoding: encoded
//gsoap ns service namespace: http://localhost/imgProcess.wsdl
//gsoap ns service location: http://localhost/cgi-bin/imgProcessServer

//gsoap ns schema namespace: urn:img


class ns__ImageData
{ unsigned char *__ptr;
  int __size;
  //char *__filename;
};

int ns__getImage(char *name, ns__ImageData &image);
int ns__Ipl1ChToMat(char *InputFilename, char *&OutputFilename);
int ns__MatToJPG(char *InputFilename, char *&OutputFilename);
int ns__BinaryThreshold(char *InputFilename, double threshold, double maxValue, char *&OutputFilename);
int ns__MorphOpen(char *InputFilename, char *&OutputFilename);

