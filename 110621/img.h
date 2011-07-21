//gsoap ns service name: img	
//gsoap ns service style: rpc
//gsoap ns service encoding: encoded
//gsoap ns service namespace: http://localhost/img.wsdl
//gsoap ns service location: http://localhost/cgi-bin/imgSrv

//gsoap ns schema namespace: urn:img


class ns__ImgData
{
    int __imgHeight;
    int __imgWidth;
    int __sharedKey;
};

int ns__Ipl1ChToMat(char *InputFilename, ns__ImgData &imgData);
int ns__BinaryThreshold(ns__ImgData dataInput, double threshold, double maxValue, ns__ImgData &imgData);
int ns__MorphOpen(char *InputFilename, char *filename, char *&OutputFilename);
