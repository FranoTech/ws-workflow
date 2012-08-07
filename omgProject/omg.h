//gsoap ns service name: omg
//gsoap ns service style: rpc
//gsoap ns service encoding: encoded
//gsoap ns service namespace: http://localhost/omg.wsdl
//gsoap ns service location: http://localhost/cgi-bin/omgServer

//gsoap ns schema namespace: urn:omg


class Configure {
	public:
		bool timeChecking;
		bool memoryChecking;
		bool keepLoging;
		
		friend std::ostream& operator<<(std::ostream& os, const Configure& c)
		{
			os << c.timeChecking << '\n';
			os << c.memoryChecking << '\n';
			os << c.keepLoging;
			return os;
		}
		
		friend std:: istream& operator>>(std::istream& is, Configure& c)
		{
			is >> c.timeChecking >> c.memoryChecking >> c.keepLoging;
			return is;
		}
 }
int ns__loadMat (std::string InputImageFilename, int colorflag=0, std::string types="CV_32FC1", std::string &OutputMatFilename);