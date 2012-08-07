//gsoap ns service name: omg
//gsoap ns service style: rpc
//gsoap ns service encoding: encoded
//gsoap ns service namespace: http://localhost/omg.wsdl
//gsoap ns service location: http://localhost/cgi-bin/omgServer

//gsoap ns schema namespace: urn:omg

int ns__loadMat (std::string InputImageFilename, int colorflag=0, std::string types="CV_32FC1", std::string &OutputMatFilename);
int ns__initialService (bool executionTimeChecking=true, bool memoryChecking=true, struct ns__signalResponse { } *noResponse=NULL)