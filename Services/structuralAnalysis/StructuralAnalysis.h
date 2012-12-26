//gsoap ns service name: Structural_Analysis
//gsoap ns service style: rpc
//gsoap ns service encoding: encoded
//gsoap ns service namespace: http://localhost/Structural_Analysis.wsdl
//gsoap ns service location: http://localhost/cgi-bin/StructuralAnalysisServer

//gsoap ns schema namespace: urn:str

//gsoap ns service method-documentation: findContours 
int ns__findContours( std::string InputMatFilename, std::string mode, std::string method,
            int offsetX_D=-1, int offsetY_D=-1, std::string &OutputMatFilename);

//gsoap ns service method-documentation: resize Resizes an image
int ns__resize( std::string InputMatFilename, int dstRows=0, int dstCols=0,
            double fx_D=0, double fy_D=0, std::string interpolation_D,
			std::string &OutputMatFilename);
