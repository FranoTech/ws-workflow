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

int ns__LoadMat (const char *InputImageFilename, int loadparam, char *&OutputMatFilename);
int ns__BinaryThreshold(const char *InputMatFilename, double threshold, double maxValue, char *&OutputMatFilename);
