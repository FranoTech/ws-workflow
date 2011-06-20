//gsoap ns service name: img	
//gsoap ns service style: rpc
//gsoap ns service namespace: http://localhost/imgSrv.wsdl
//gsoap ns service location: http://localhost/cgi-bin/imgSrv

//gsoap ns schema namespace: urn:img


class ns__ImageData
{ unsigned char *__ptr;
  int __size;
};


int ns__Ipl1ChToMat(char *InputFilename, int *sharedkey);
int ns__BinaryThreshold(double threshold, double maxValue,int *sharedkey);
int ns__MorphOpen(char *InputFilename, char *filename, char *&OutputFilename);
