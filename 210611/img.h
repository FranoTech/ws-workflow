//gsoap ns service name: img	
//gsoap ns service style: rpc
//gsoap ns service encoding: encoded
//gsoap ns service namespace: http://localhost/imgSrv.wsdl
//gsoap ns service location: http://localhost/cgi-bin/imgSrv

//gsoap ns schema namespace: urn:img


class ns__ImgData
{
    int imgHeigh;
    int imgWidth;
    int sharedKey;
};

int ns__Ipl1ChToMat(char *InputFilename, ns__ImgData &data);
int ns__BinaryThreshold(double threshold, double maxValue, ns__ImgData &data);
int ns__MorphOpen(char *InputFilename, char *filename, char *&OutputFilename);
