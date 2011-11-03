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

int ns__LoadMat (char *InputImageFilename, int loadparam, char *&OutputMatFilename);
int ns__BinaryThreshold(char *InputMatFilename, double thresholdValue, double maxValue, char *&OutputMatFilename);
int ns__MorphOpen(char *InpuMattFilename, char *&OutputMatFilename);
int ns__MatToJPG (char *InputMatFilename, char *&OutputMatFilename);
