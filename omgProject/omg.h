//gsoap ns service name: omg
//gsoap ns service style: rpc
//gsoap ns service encoding: encoded
//gsoap ns service namespace: http://localhost/omg.wsdl
//gsoap ns service location: http://localhost/cgi-bin/omgServer

//gsoap ns schema namespace: urn:omg

class ns__ServiceData 
{
	public:
		std::string InputFilename;
		std::string OutputMatFilename;
		bool timeChecking;
		bool memoryChecking;
};

int ns__loadMat (int colorflag=0, std::string types="CV_32FC1", ns__ServiceData& data);