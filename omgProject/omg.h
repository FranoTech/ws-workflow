//gsoap ns service name: omg
//gsoap ns service style: rpc
//gsoap ns service encoding: encoded
//gsoap ns service namespace: http://localhost/omg.wsdl
//gsoap ns service location: http://localhost/cgi-bin/omgServer

//gsoap ns schema namespace: urn:omg

#include <string>

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

//gsoap ns service method-documentation: convert Image to Mat data
int ns__imgToMat(std::string InputMatFilename, int colorflag=0, std::string types="CV_32FC1", std::string &OutputMatFilename);

//gsoap ns service method-documentation: Saving Mat to JPG image
int ns__MatToJPG (std::string InputMatFilename, std::string &OutputMatFilename);

//gsoap ns service method-documentation: Converts an array to another data type
int ns__ConvertTo(std::string InputMatFilename, std::string types="CV_32FC1", std::string &OutputMatFilename);

//gsoap ns service method-documentation: Applies a fixed-level threshold to each array element
int ns__Threshold(std::string InputMatFilename, double thresholdValue=127.0, double maxValue=255.0, std::string thresholdType="THRESH_BINARY", std::string &OutputMatFilename);

//gsoap ns service method-documentation: Performs advanced morphological transformations
int ns__MorphologyEx(   std::string InputMatFilename,
						std::string morphOperation="MORPH_OPEN",
						std::string &OutputMatFilename );

//gsoap ns service method-documentation: Erodes an image by using a specific structuring element
int ns__erode(  std::string InputMatFilename,
				std::string elementFilename,
				int iteration=1,
				std::string &OutputMatFilename );

//gsoap ns service method-documentation: Dilates an image by using a specific structuring element
int ns__dilate( std::string InputMatFilename,
				std::string elementFilename,
				int iteration=1,
				std::string &OutputMatFilename );   

//gsoap ns service method-documentation: Calculates the per-element bit-wise disjunction of two arrays
int ns__Or( std::string src1,
			std::string src2,
			std::string &OutputMatFilename );      

//gsoap ns service method-documentation: Calculates the per-element bit-wise conjunction of two arrays
int ns__And(std::string src1,
			std::string src2,
			std::string &OutputMatFilename );

//gsoap ns service method-documentation: Calculates the per-element bit-wise “exclusive or” operation on two arrays
int ns__Xor(std::string src1,
			std::string src2,
			std::string &OutputMatFilename );                          

//gsoap ns service method-documentation: Inverts every bit of an array
int ns__Not(std::string src,
			std::string &OutputMatFilename );   

//gsoap ns service method-documentation: Inverses a matrix
int ns__Inverse(    std::string InputMatFilename,
                    std::string &OutputMatFilename );             

//gsoap ns service method-documentation: Performs an element-wise multiplication or division of the two matrices
int ns__mul(    std::string InputMatFilename,
                std::string AnotherMatFilename, double scale=1,
                std::string &OutputMatFilename );    

//gsoap ns service method-documentation: Computes a cross-product of two 3-element vectors
int ns__cross(  std::string InputMatFilename,
                std::string AnotherMatFilename,
                std::string &OutputMatFilename );

//gsoap ns service method-documentation: Computes a dot-product of two vectors
int ns__dot(std::string InputMatFilename,
            std::string AnotherMatFilename,
			std::string &OutputMatFilename ) ;     

//gsoap ns service method-documentation: Returns a zero array of the specified size and type
int ns__zeros(int rows=0, int columns=0,
			std::string type="CV_32F",
			std::string &OutputMatFilename );        

//gsoap ns service method-documentation: Returns an array of all 1’s of the specified size and type
int ns__ones( int rows=0, int columns=0,
			int size=0, std::string type="CV_32F",
			std::string &OutputMatFilename );

//gsoap ns service method-documentation: Allocates new array data if needed
int ns__createMat(int rows=0, int columns=0,
			std::string type="CV_32F",
			std::string &OutputMatFilename );                

//gsoap ns service method-documentation: Creates a matrix header for the specified column span
int ns__colRange(std::string InputMatFilename,
			int startCol, int endCol, 
			std::string &OutputMatFilename );       

//gsoap ns service method-documentation: Creates a matrix header for the specified row span
int ns__rowRange(  std::string InputMatFilename,
			int startCol, int endCol, 
			std::string &OutputMatFilename );         

//gsoap ns service method-documentation: Get Mat detail (rows, cols, depth, data type, channels, empty)
int ns__getMatDetail( std::string InputMatFilename, ns__MatDetail &detail);

//gsoap ns service method-documentation: Smoothes an image using the normalized box filter
int ns__blur(std::string InputMatFilename, int rows=0, int cols=0, 
            int anchorX=-1, int anchorY=-1, int borderType,
			std::string &OutputMatFilename );

//gsoap ns service method-documentation: Smoothes an image using a Gaussian filter
int ns__GaussianBlur( std::string InputMatFilename, int rows=0, int cols=0,
            double sigmaX=0, double sigmaY=0, int borderType,
			std::string &OutputMatFilename );

//gsoap ns service method-documentation: Converts an image from one color space to another
int ns__cvtColor( std::string InputMatFilename, std::string code, int dstChannel=0,
			std::string &OutputMatFilename);

//gsoap ns service method-documentation: Calculates the integral of an image
int ns__integral( std::string InputMatFilename, int sdepth=-1,
			std::string &OutputMatFilename);

//gsoap ns service method-documentation: Applies an adaptive threshold to an array
int ns__adaptiveThreshold(
                        std::string InputMatFilename,
                        std::string adaptiveMethod,
                        double maxValue=255.0,
                        std::string thresholdType="THRESH_BINARY",
                        int blockSize=3, double C=1,
                        std::string &OutputMatFilename);

//gsoap ns service method-documentation: simple brighness and contrast control (alpha value [1.0-3.0], beta value [0-100])
int ns__adjustBrighnessAndContrast(
                        std::string InputMatFilename,
						double alpha, int beta,
						std::string &OutputMatFilename);

//gsoap ns service method-documentation: Preparing result for CIA
int ns__CIAprepareResult(  std::string InputMatFilename,
                        std::string afterthresNN,
						std::string &OutputMatFilename);

//gsoap ns service method-documentation: Apply naural network training for CIA
int ns__CIAtrainANN(
                std::string InputMatFilename,
                std::string neuralFile,
                std::string &OutputMatFilename);

//gsoap ns service method-documentation: Remove some noise and small cell from cell image
int ns__CIAremoveSmallCell(std::string InputMatFilename,
						ns__RemoveSmallCell &out);

//gsoap ns service method-documentation: Separate wanted cells from background
int ns__CIAseparateCell(   std::string outSingleCh,
                        std::string outputFormMorph,
						std::string &OutputMatFilename);

//gsoap ns service method-documentation: Scanning cells in cancer image
int ns__CIAscanningCell(   std::string biggerArea,
                        std::string keepArea,
						std::string &OutputMatFilename);        
