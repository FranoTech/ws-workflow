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

//gsoap ns service method-documentation: imgToMat Convert Image to Mat data (8UC1 gray scale image is default)
int ns__imgToMat(std::string InputMatFilename, int colorflag=0, std::string types="CV_8UC1", std::string &OutputMatFilename);

//gsoap ns service method-documentation: MatToJPG Saving Mat to JPG image
int ns__MatToJPG (std::string InputMatFilename, std::string &OutputMatFilename);

//gsoap ns service method-documentation: viewImage View an image in workbench
int ns__viewImage( std::string InputMatFilename, ns__base64Binary &image);

//gsoap ns service method-documentation: ConvertTo Converts an array to another data type
int ns__convertTo(std::string InputMatFilename, std::string types="CV_32FC1", double alpha_D=1, double beta_D=0, std::string &OutputMatFilename);

//gsoap ns service method-documentation: Threshold Applies a fixed-level threshold to each array element
int ns__Threshold(std::string InputMatFilename, double thresholdValue=127.0, double maxValue=255.0, std::string thresholdType="THRESH_BINARY", std::string &OutputMatFilename);

//gsoap ns service method-documentation: getStructuringElement Returns a structuring element of the specified size and shape for morphological operations
int ns__getStructuringElement( std::string StructuringShape="MORPH_ELLIPSE", int seSizeW=3, int seSizeH=3, int anchorX_D=-1, int anchorY_D=-1, std::string &OutputMatFilename);


//gsoap ns service method-documentation: MorphologyEx Performs advanced morphological transformations
int ns__MorphologyEx( std::string InputMatFilename, std::string morphOperation="MORPH_OPEN", int anchorX_D=-1, int anchorY_D=-1, std::string StructuringElementFname, std::string StructuringShape="MORPH_ELLIPSE", int seSizeW_=3, int seSizeH_=3, std::string &OutputMatFilename);

//gsoap ns service method-documentation: erode Erodes an image by using a specific structuring element
int ns__erode(  std::string InputMatFilename, std::string StructuringElementFilename, int iteration_=1, int anchorX_D=-1, int anchorY_D=-1, std::string borderType_D ,std::string &OutputMatFilename );

//gsoap ns service method-documentation: dilate Dilates an image by using a specific structuring element
int ns__dilate( std::string InputMatFilename, std::string StructuringElementFilename, int iteration_=1, int anchorX_D=-1, int anchorY_D=-1, std::string borderType_D ,std::string &OutputMatFilename );   

//gsoap ns service method-documentation: Or Calculates the per-element bit-wise disjunction of two arrays
int ns__Or( std::string src1, std::string src2, std::string &OutputMatFilename );      

//gsoap ns service method-documentation:  And Calculates the per-element bit-wise conjunction of two arrays
int ns__And(std::string src1, std::string src2, std::string &OutputMatFilename );

//gsoap ns service method-documentation: Xor Calculates the per-element bit-wise “exclusive or” operation on two arrays
int ns__Xor(std::string src1, std::string src2, std::string &OutputMatFilename );                          

//gsoap ns service method-documentation: Not Inverts every bit of an array
int ns__Not(std::string src, std::string &OutputMatFilename );   

//gsoap ns service method-documentation: Inverse Inverses a matrix
int ns__Inverse( std::string InputMatFilename, std::string InvMethod_D="DECOMP_LU", std::string &OutputMatFilename );

//gsoap ns service method-documentation: mul Performs an element-wise multiplication or division of the two matrices
int ns__mul( std::string InputMatFilename, std::string AnotherMatFilename, double scale_D=1, std::string &OutputMatFilename );    

//gsoap ns service method-documentation: cross Computes a cross-product of two 3-element vectors
int ns__cross(  std::string InputMatFilename, std::string AnotherMatFilename, std::string &OutputMatFilename );

//gsoap ns service method-documentation: dot Computes a dot-product of two vectors
int ns__dot(std::string InputMatFilename, std::string AnotherMatFilename, std::string &OutputMatFilename ) ;     

//gsoap ns service method-documentation: zeros Returns a zero array of the specified size and type
int ns__zeros(int rows=0, int columns=0,std::string type="CV_32F", std::string &OutputMatFilename );        

//gsoap ns service method-documentation: ones Returns an array of all 1’s of the specified size and type
int ns__ones( int rows=0, int columns=0, std::string type="CV_32F", std::string &OutputMatFilename );

//gsoap ns service method-documentation: createMat Allocates new array data if needed
int ns__createMat(int rows=0, int columns=0, std::string type="CV_32F", std::string &OutputMatFilename );
  
//gsoap ns service method-documentation: colRange Creates a matrix header for the specified column span
int ns__colRange(std::string InputMatFilename,int startCol, int endCol,std::string &OutputMatFilename );       

//gsoap ns service method-documentation: rowRange Creates a matrix header for the specified row span
int ns__rowRange(  std::string InputMatFilename,int startCol, int endCol, std::string &OutputMatFilename );        

//gsoap ns service method-documentation: getMatDetail Get Mat detail (rows, cols, depth, data type, channels, empty)
int ns__getMatDetail( std::string InputMatFilename, ns__MatDetail &detail);

//gsoap ns service method-documentation: blur Smoothes an image using the normalized box filter
int ns__blur(std::string InputMatFilename, int rows=0, int cols=0, int anchorX_D=-1, int anchorY_D=-1, std::string borderType_D, std::string &OutputMatFilename );

//gsoap ns service method-documentation: GaussianBlur Smoothes an image using a Gaussian filter
int ns__GaussianBlur( std::string InputMatFilename, int rows=0, int cols=0, double sigmaX=0, double sigmaY_D=0, std::string borderType_D, std::string &OutputMatFilename );

//gsoap ns service method-documentation: cvtColor Converts an image from one color space to another
int ns__cvtColor( std::string InputMatFilename, std::string code, int dstChannel_D=0, std::string &OutputMatFilename);

//gsoap ns service method-documentation: integral Calculates the integral of an image
int ns__integral( std::string InputMatFilename, int sdepth_D=-1, std::string &OutputMatFilename);

//gsoap ns service method-documentation: adaptiveThreshold Applies an adaptive threshold to an array
int ns__adaptiveThreshold( std::string InputMatFilename, std::string adaptiveMethod, double maxValue=255.0, std::string thresholdType="THRESH_BINARY", int blockSize=3, double C=1, std::string &OutputMatFilename);

//gsoap ns service method-documentation: adjustBrighnessAndContrast simple brighness and contrast control (alpha value [1.0-3.0], beta value [0-100])
int ns__adjustBrighnessAndContrast( std::string InputMatFilename, double alpha, int beta, std::string &OutputMatFilename);

//gsoap ns service method-documentation: CIAprepareResult Preparing result for CIA
int ns__CIAprepareResult(  std::string InputMatFilename, std::string afterthresNN, std::string &OutputMatFilename);

//gsoap ns service method-documentation: CIAtrainANN Apply naural network training for CIA
int ns__CIAtrainANN( std::string InputMatFilename, std::string neuralFile, std::string &OutputMatFilename);

//gsoap ns service method-documentation: CIAremoveSmallCell Remove some noise and small cell from cell image
int ns__CIAremoveSmallCell(std::string InputMatFilename, ns__RemoveSmallCell &out);

//gsoap ns service method-documentation: CIAseparateCell Separate wanted cells from background
int ns__CIAseparateCell(   std::string outSingleCh, std::string outputFormMorph, std::string &OutputMatFilename);

//gsoap ns service method-documentation: CIAscanningCell Scanning cells in cancer image
int ns__CIAscanningCell(   std::string biggerArea, std::string keepArea, std::string &OutputMatFilename);        

//gsoap ns service method-documentation: medianBlur Smoothes an image using the median filter
int ns__medianBlur( std::string InputMatFilename, int kSize=1, std::string &OutputMatFilename);

//gsoap ns service method-documentation: Laplacian Calculates the Laplacian of an image
int ns__Laplacian( std::string InputMatFilename, std::string ddepth, int ksize_D=1, double scale_D=1, double delta_D=0, std::string borderType_D , std::string &OutputMatFilename);

//gsoap ns service method-documentation: pyrDown Smoothes an image and downsamples it
int ns__pyrDown( std::string InputMatFilename, int rows=0, int cols=0, std::string borderType_D, std::string &OutputMatFilename);

//gsoap ns service method-documentation: pyrUp Upsamples an image and then smoothes it
int ns__pyrUp( std::string InputMatFilename, int rows=0, int cols=0, std::string borderType_D, std::string &OutputMatFilename);

//gsoap ns service method-documentation: addWeighted Computes the weighted sum of two arrays
int ns__addWeighted( std::string InputMatFilename1, double alpha, std::string InputMatFilename2 , double beta, double gamma, int dtype_D=-1, std::string &OutputMatFilename);

//gsoap ns service method-documentation: add Computes the per-element sum of two arrays or an array and a scalar
int ns__add( std::string InputMatFilename1, std::string InputMatFilename2 , std::string maskFilename_D , int dtype_D=-1, std::string &OutputMatFilename);

//gsoap ns service method-documentation: subtract Calculates the per-element difference between two arrays or array and a scalar
int ns__subtract( std::string InputMatFilename1, std::string InputMatFilename2 , std::string maskFilename_D , int dtype_D=-1, std::string &OutputMatFilename);

//gsoap ns service method-documentation: abs Computes an absolute value of each matrix element
int ns__abs( std::string InputMatFilename, std::string &OutputMatFilename);

//gsoap ns service method-documentation: absdiff Computes the per-element absolute difference between two arrays or between an array and a scalar
int ns__absdiff( std::string InputMatFilename1, std::string InputMatFilename2, std::string &OutputMatFilename);

//gsoap ns service method-documentation: sqrt Calculates a square root of array elements
int ns__sqrt( std::string InputMatFilename, std::string &OutputMatFilename);

//gsoap ns service method-documentation: watershed Performs a marker-based image segmentation using the watershed algorithm
int ns__watershed( std::string InputMatFilename, std::string MarkerMatFilename, std::string &OutputMatFilename);

//gsoap ns service method-documentation: circle Draws a simple or filled circle with a given center and radius
int ns__circle( std::string InputMatFilename, int centerX, int centerY, int radius, int scalarColor0, int scalarColor1, int scalarColor2, int thickness_D=1, int lineType_D=8, int shift_D=0, std::string &OutputMatFilename);

//gsoap ns service method-documentation: ellipse Draws a simple or thick elliptic arc or fills an ellipse sector
int ns__ellipse( std::string InputMatFilename, int centerX=10, int centerY=10, int axeX=1, int axeY=1, double angle=0.0, double startAngle=0.0, double endAngle=360.0, int scalarColor0=0, int scalarColor1=0, int scalarColor2=0, int thickness_D=1, int lineType_D=8, int shift_D=0, std::string &OutputMatFilename);

//gsoap ns service method-documentation: Sobel Calculates the first, second, third, or mixed image derivatives using an extended Sobel operator
int ns__Sobel( std::string InputMatFilename, std::string ddepth="CV_8U", int kSize_D=3, double scale_D=1, double delta_D=0, int dx, int dy, std::string borderType_D, std::string &OutputMatFilename);


