//gsoap ns service name: Image_Transformations
//gsoap ns service style: rpc
//gsoap ns service encoding: encoded
//gsoap ns service namespace: http://localhost/Image_Transformations.wsdl
//gsoap ns service location: http://localhost/cgi-bin/ImageTransformationsServer

//gsoap ns schema namespace: urn:trn



//gsoap ns service method-documentation: Threshold Applies a fixed-level threshold to each array element
int ns__Threshold(std::string InputMatFilename, double thresholdValue=127.0, double maxValue=255.0, std::string thresholdType="THRESH_BINARY", std::string &OutputMatFilename);

//gsoap ns service method-documentation: cvtColor Converts an image from one color space to another
int ns__cvtColor( std::string InputMatFilename, std::string code, int dstChannel_D=0, std::string &OutputMatFilename);

//gsoap ns service method-documentation: integral Calculates the integral of an image
int ns__integral( std::string InputMatFilename, int sdepth_D=-1, std::string &OutputMatFilename);

//gsoap ns service method-documentation: adaptiveThreshold Applies an adaptive threshold to an array
int ns__adaptiveThreshold( std::string InputMatFilename, std::string adaptiveMethod, double maxValue=255.0, std::string thresholdType, int blockSize=3, double C=1, std::string &OutputMatFilename);

//gsoap ns service method-documentation: adjustBrighnessAndContrast simple brighness and contrast control (alpha value [1.0-3.0], beta value [0-100])
int ns__adjustBrighnessAndContrast( std::string InputMatFilename, double alpha, int beta, std::string &OutputMatFilename);

//gsoap ns service method-documentation: watershed Performs a marker-based image segmentation using the watershed algorithm
int ns__watershed( std::string InputMatFilename, std::string MarkerMatFilename, std::string &OutputMatFilename);
