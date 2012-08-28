//gsoap ns service name: omg
//gsoap ns service style: rpc
//gsoap ns service encoding: encoded
//gsoap ns service namespace: http://localhost/omg.wsdl
//gsoap ns service location: http://localhost/cgi-bin/omgServer

//gsoap ns schema namespace: urn:omg

int ns__imgToMat(std::string InputMatFilename, int colorflag=0, std::string types="CV_32FC1", std::string &OutputMatFilename);
int ns__MatToJPG (std::string InputMatFilename, std::string &OutputMatFilename);
int ns__ConvertTo(std::string InputMatFilename, std::string types="CV_32FC1", std::string &OutputMatFilename);
int ns__Threshold(std::string InputMatFilename, double thresholdValue=127.0, double maxValue=255.0, std::string thresholdType="THRESH_BINARY", std::string &OutputMatFilename);
