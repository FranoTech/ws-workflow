//gsoap ns service name: Feature_Detection
//gsoap ns service style: rpc
//gsoap ns service encoding: encoded
//gsoap ns service namespace: http://localhost/Feature_Detection.wsdl
//gsoap ns service location: http://localhost/cgi-bin/FeatureDetectionServer

//gsoap ns schema namespace: urn:fea

//gsoap ns service method-documentation: Canny Finds edges in an image using the Canny86 algorithm
int ns__Canny( std::string InputMatFilename, double threshold1, double threshold2,
            int apertureSize_D=3, int L2gradient_D=0,std::string &OutputMatFilenameE);

// int ns__cornerHarris( std::string InputMatFilename, double threshold1, double threshold2,
//             int apertureSize_D=3, int L2gradient_D=0,std::string &OutputMatFilenameE);

// int ns__HoughCircles( std::string InputMatFilename, double threshold1, double threshold2,
//             int apertureSize_D=3, int L2gradient_D=0,std::string &OutputMatFilenameE);



