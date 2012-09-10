//gsoap ns service name: omg
//gsoap ns service style: rpc
//gsoap ns service encoding: encoded
//gsoap ns service namespace: http://localhost/omg.wsdl
//gsoap ns service location: http://localhost/cgi-bin/omgServer

//gsoap ns schema namespace: urn:omg

#include <string>
extern class std::string;

#include <cv.h>

class ns__RemoveSmallCell
{ 
	std::string keepedArea;
	std::string biggerArea;
};

class ns__base64Binary
{ unsigned char *__ptr;
  int __size;
};

class ns__MatDetail
{
	int columns;
	int rows;
	std::string depth;
	std::string type;
	int channel;
	bool empty;
};

int ns__imgToMat(std::string InputMatFilename, int colorflag=0, std::string types="CV_32FC1", std::string &OutputMatFilename);
int ns__MatToJPG (std::string InputMatFilename, std::string &OutputMatFilename);
int ns__ConvertTo(std::string InputMatFilename, std::string types="CV_32FC1", std::string &OutputMatFilename);
int ns__Threshold(std::string InputMatFilename, double thresholdValue=127.0, double maxValue=255.0, std::string thresholdType="THRESH_BINARY", std::string &OutputMatFilename);
int ns__MorphologyEx(   std::string InputMatFilename,
						std::string morphOperation="MORPH_OPEN",
						std::string &OutputMatFilename );
int ns__erode(  std::string InputMatFilename,
				std::string elementFilename,
				int iteration=1,
				std::string &OutputMatFilename );
int ns__dilate( std::string InputMatFilename,
				std::string elementFilename,
				int iteration=1,
				std::string &OutputMatFilename );   
int ns__Or( std::string src1,
			std::string src2,
			std::string &OutputMatFilename );      
int ns__And(std::string src1,
			std::string src2,
			std::string &OutputMatFilename );
int ns__Xor(std::string src1,
			std::string src2,
			std::string &OutputMatFilename );                          
int ns__Not(std::string src,
			std::string &OutputMatFilename );   
int ns__Inverse(    std::string InputMatFilename,
                    std::string &OutputMatFilename );             
int ns__mul(    std::string InputMatFilename,
                std::string AnotherMatFilename, double scale=1,
                std::string &OutputMatFilename );    
int ns__cross(  std::string InputMatFilename,
                std::string AnotherMatFilename,
                std::string &OutputMatFilename );
int ns__dot(std::string InputMatFilename,
            std::string AnotherMatFilename,
			std::string &OutputMatFilename ) ;     
int ns__zeros(int rows=0, int columns=0,
			std::string type="CV_32F",
			std::string &OutputMatFilename );        
int ns__ones( int rows=0, int columns=0,
			int size=0, std::string type="CV_32F",
			std::string &OutputMatFilename );
int ns__createMat(int rows=0, int columns=0,
			std::string type="CV_32F",
			std::string &OutputMatFilename );                
int ns__colRange(std::string InputMatFilename,
			int startCol, int endCol, 
			std::string &OutputMatFilename );       
int ns__rowRange(  std::string InputMatFilename,
			int startCol, int endCol, 
			std::string &OutputMatFilename );         
int ns__getMatDetail( std::string InputMatFilename, ns__MatDetail &detail);
int ns__blur(std::string InputMatFilename, int rows=0, int cols=0, 
            int anchorX=-1, int anchorY=-1, int borderType,
			std::string &OutputMatFilename );
int ns__GaussianBlur( std::string InputMatFilename, int rows=0, int cols=0,
            double sigmaX=0, double sigmaY=0, int borderType,
			std::string &OutputMatFilename );
