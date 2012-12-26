//gsoap ns service name: Image_Filtering
//gsoap ns service style: rpc
//gsoap ns service encoding: encoded
//gsoap ns service namespace: http://localhost/Image_Filtering.wsdl
//gsoap ns service location: http://localhost/cgi-bin/ImageFilteringServer

//gsoap ns schema namespace: urn:filt

//gsoap ns service method-documentation: blur Smoothes an image using the normalized box filter
int ns__blur(std::string InputMatFilename, int kernelRows=1, int kernelCols=1, int anchorX_D=-1, int anchorY_D=-1, std::string borderType_D, std::string &OutputMatFilename );

//gsoap ns service method-documentation: GaussianBlur Smoothes an image using a Gaussian filter
int ns__GaussianBlur( std::string InputMatFilename, int kernelRows=1, int kernelCols=1, double sigmaX=0, double sigmaY_D=0, std::string borderType_D, std::string &OutputMatFilename );

//gsoap ns service method-documentation: erode Erodes an image by using a specific structuring element
int ns__erode(  std::string InputMatFilename, std::string StructuringElementFilename, int iteration_=1, int anchorX_D=-1, int anchorY_D=-1, std::string borderType_D ,std::string &OutputMatFilename );

//gsoap ns service method-documentation: dilate Dilates an image by using a specific structuring element
int ns__dilate( std::string InputMatFilename, std::string StructuringElementFilename, int iteration_=1, int anchorX_D=-1, int anchorY_D=-1, std::string borderType_D ,std::string &OutputMatFilename ); 

//gsoap ns service method-documentation: filter2D Convolves an image with the kernel
int ns__filter2D( 
			std::string InputMatFilename,
            int ddepth, std::string kernelFname, 
            int anchorX_D=-1, int anchorY_D=-1, 
            double delta_D=0, std::string borderType_D,
            std::string &OutputMatFilename);
            
//gsoap ns service method-documentation: getStructuringElement Returns a structuring element of the specified size and shape for morphological operations
int ns__getStructuringElement( std::string StructuringShape="MORPH_ELLIPSE", int seSizeW=3, int seSizeH=3, int anchorX_D=-1, int anchorY_D=-1, std::string &OutputMatFilename);

//gsoap ns service method-documentation: medianBlur Smoothes an image using the median filter
int ns__medianBlur( std::string InputMatFilename, int kSize_D=3, std::string &OutputMatFilename);


//gsoap ns service method-documentation: MorphologyEx Performs advanced morphological transformations
int ns__MorphologyEx( std::string InputMatFilename, std::string morphOperation, std::string StructuringElementFname, int iteration_D=1, int anchorX_D=-1, int anchorY_D=-1,std::string &OutputMatFilename);


//gsoap ns service method-documentation: Laplacian Calculates the Laplacian of an image
int ns__Laplacian( std::string InputMatFilename, std::string ddepth, int ksize_D=1, double scale_D=1, double delta_D=0, std::string borderType_D , std::string &OutputMatFilename);

//gsoap ns service method-documentation: pyrDown Smoothes an image and downsamples it
int ns__pyrDown( std::string InputMatFilename, int rows=0, int cols=0, std::string borderType_D, std::string &OutputMatFilename);

//gsoap ns service method-documentation: pyrUp Upsamples an image and then smoothes it
int ns__pyrUp( std::string InputMatFilename, int rows=0, int cols=0, std::string borderType_D, std::string &OutputMatFilename);

//gsoap ns service method-documentation: Sobel Calculates the first, second, third, or mixed image derivatives using an extended Sobel operator
int ns__Sobel( std::string InputMatFilename, std::string ddepth="CV_8U", int kSize_D=3, double scale_D=1, double delta_D=0, int dx, int dy, std::string borderType_D, std::string &OutputMatFilename);
