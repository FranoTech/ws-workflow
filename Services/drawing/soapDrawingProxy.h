/* soapDrawingProxy.h
   Generated by gSOAP 2.8.8 from Drawing.h

Copyright(C) 2000-2012, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
1) GPL or 2) Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#ifndef soapDrawingProxy_H
#define soapDrawingProxy_H
#include "soapH.h"
class Drawing
{   public:
	/// Runtime engine context allocated in constructor
	struct soap *soap;
	/// Endpoint URL of service 'Drawing' (change as needed)
	const char *endpoint;
	/// Constructor allocates soap engine context, sets default endpoint URL, and sets namespace mapping table
	Drawing()
	{ soap = soap_new(); endpoint = "http://localhost/cgi-bin/DrawingServer"; if (soap && !soap->namespaces) { static const struct Namespace namespaces[] = 
{
	{"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
	{"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"ns", "urn:draw", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};
	soap->namespaces = namespaces; } };
	/// Destructor frees deserialized data and soap engine context
	virtual ~Drawing() { if (soap) { soap_destroy(soap); soap_end(soap); soap_free(soap); } };
	/// Invoke 'circle' of service 'Drawing' and return error code (or SOAP_OK)
	virtual int ns__circle(std::string InputMatFilename, int centerX, int centerY, int radius, int scalarColor0, int scalarColor1, int scalarColor2, int thickness_D, int lineType_D, int shift_D, std::string &OutputMatFilename) { return soap ? soap_call_ns__circle(soap, endpoint, NULL, InputMatFilename, centerX, centerY, radius, scalarColor0, scalarColor1, scalarColor2, thickness_D, lineType_D, shift_D, OutputMatFilename) : SOAP_EOM; };
	/// Invoke 'ellipse' of service 'Drawing' and return error code (or SOAP_OK)
	virtual int ns__ellipse(std::string InputMatFilename, int centerX, int centerY, int axeX, int axeY, double angle, double startAngle, double endAngle, int scalarColor0, int scalarColor1, int scalarColor2, int thickness_D, int lineType_D, int shift_D, std::string &OutputMatFilename) { return soap ? soap_call_ns__ellipse(soap, endpoint, NULL, InputMatFilename, centerX, centerY, axeX, axeY, angle, startAngle, endAngle, scalarColor0, scalarColor1, scalarColor2, thickness_D, lineType_D, shift_D, OutputMatFilename) : SOAP_EOM; };
};
#endif
