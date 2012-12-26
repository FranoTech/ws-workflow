//gsoap ns service name: Drawing
//gsoap ns service style: rpc
//gsoap ns service encoding: encoded
//gsoap ns service namespace: http://localhost/Drawing.wsdl
//gsoap ns service location: http://localhost/cgi-bin/DrawingServer

//gsoap ns schema namespace: urn:draw

#include <string>


//gsoap ns service method-documentation: circle Draws a simple or filled circle with a given center and radius
int ns__circle( std::string InputMatFilename, int centerX, int centerY, int radius, int scalarColor0, int scalarColor1, int scalarColor2, int thickness_D=1, int lineType_D=8, int shift_D=0, std::string &OutputMatFilename);

//gsoap ns service method-documentation: ellipse Draws a simple or thick elliptic arc or fills an ellipse sector
int ns__ellipse( std::string InputMatFilename, int centerX=10, int centerY=10, int axeX=1, int axeY=1, double angle=0.0, double startAngle=0.0, double endAngle=360.0, int scalarColor0=0, int scalarColor1=0, int scalarColor2=0, int thickness_D=1, int lineType_D=8, int shift_D=0, std::string &OutputMatFilename);

