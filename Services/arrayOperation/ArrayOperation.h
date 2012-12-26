//gsoap ns service name: Array_Operation
//gsoap ns service style: rpc
//gsoap ns service encoding: encoded
//gsoap ns service namespace: http://localhost/Array_Operation.wsdl
//gsoap ns service location: http://localhost/cgi-bin/ArrayOperationServer

//gsoap ns schema namespace: urn:aropt

//gsoap ns service method-documentation: Or Calculates the per-element bit-wise disjunction of two arrays
int ns__Or( std::string src1, std::string src2, std::string &OutputMatFilename );      

//gsoap ns service method-documentation:  And Calculates the per-element bit-wise conjunction of two arrays
int ns__And(std::string src1, std::string src2, std::string &OutputMatFilename );

//gsoap ns service method-documentation: Xor Calculates the per-element bit-wise “exclusive or” operation on two arrays
int ns__Xor(std::string src1, std::string src2, std::string &OutputMatFilename );                          

//gsoap ns service method-documentation: Not Inverts every bit of an array
int ns__Not(std::string src, std::string &OutputMatFilename );

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
