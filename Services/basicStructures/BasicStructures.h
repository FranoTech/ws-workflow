//gsoap ns service name: Basic_Structures
//gsoap ns service style: rpc
//gsoap ns service encoding: encoded
//gsoap ns service namespace: http://localhost/Basic_Structures.wsdl
//gsoap ns service location: http://localhost/cgi-bin/BasicStructuresServer

//gsoap ns schema namespace: urn:bs

class ns__MatDetail
{
	int columns;
	int rows;
	std::string depth;
	std::string type;
	int channel;
	bool empty;
};


//gsoap ns service method-documentation: rowRange Creates a matrix header for the specified row span
int ns__rowRange(std::string InputMatFilename,int startCol, int endCol, std::string &OutputMatFilename ); 

//gsoap ns service method-documentation: colRange Creates a matrix header for the specified column span
int ns__colRange(std::string InputMatFilename,int startCol, int endCol, std::string &OutputMatFilename );

//gsoap ns service method-documentation: ConvertTo Converts an array to another data type
int ns__convertTo(std::string InputMatFilename, std::string types="CV_32FC1", double alpha_D=1, double beta_D=0, std::string &OutputMatFilename);

//gsoap ns service method-documentation: createMat Allocates new array data if needed
int ns__createMat(int rows=0, int columns=0, std::string type, int scalar=-1, std::string &OutputMatFilename );

//gsoap ns service method-documentation: Inverse Inverses a matrix
int ns__Inverse( std::string InputMatFilename, std::string InvMethod_D, std::string &OutputMatFilename );

//gsoap ns service method-documentation: mul Performs an element-wise multiplication or division of the two matrices
int ns__mul( std::string InputMatFilename, std::string AnotherMatFilename, double scale_D=1, std::string &OutputMatFilename ); 

//gsoap ns service method-documentation: cross Computes a cross-product of two 3-element vectors
int ns__cross(  std::string InputMatFilename, std::string AnotherMatFilename, std::string &OutputMatFilename );

//gsoap ns service method-documentation: dot Computes a dot-product of two vectors
int ns__dot(std::string InputMatFilename, std::string AnotherMatFilename, std::string &OutputMatFilename );

//gsoap ns service method-documentation: zeros Returns a zero array of the specified size and type
int ns__zeros(int rows=0, int columns=0,std::string type, std::string &OutputMatFilename );        

//gsoap ns service method-documentation: ones Returns an array of all 1’s of the specified size and type
int ns__ones( int rows=0, int columns=0, int fillWith=0, std::string type, std::string &OutputMatFilename );

//gsoap ns service method-documentation: getMatDetail Get Mat detail (rows, cols, depth, data type, channels, empty)
int ns__getMatDetail( std::string InputMatFilename, ns__MatDetail &detail);

//gsoap ns service method-documentation: printAllMatValue
int ns__printAllMatValue (std::string InputMatFilename, std::string &OutputMat);

//gsoap ns service method-documentation: accessPixelValue 
int ns__accessPixelValue(
            std::string InputMatFilename,
            std::string returnType,
            int intToSet=0, float floatToSet=0,
            int pixelI =0, int pixelJ =0, int channel =0,
			std::string &OutputMatFilename);




