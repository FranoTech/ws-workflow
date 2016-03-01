/* soapImage_TransformationsProxy.h
   Generated by gSOAP 2.8.8 from ImageTransformations.h

Copyright(C) 2000-2012, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
1) GPL or 2) Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#ifndef soapImage_TransformationsProxy_H
#define soapImage_TransformationsProxy_H
#include "soapH.h"
class Image_Transformations
{   public:
	/// Runtime engine context allocated in constructor
	struct soap *soap;
	/// Endpoint URL of service 'Image_Transformations' (change as needed)
	const char *endpoint;
	/// Constructor allocates soap engine context, sets default endpoint URL, and sets namespace mapping table
	Image_Transformations()
	{ soap = soap_new(); endpoint = "http://localhost/cgi-bin/ImageTransformationsServer"; if (soap && !soap->namespaces) { static const struct Namespace namespaces[] = 
{
	{"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
	{"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"ns", "urn:trn", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};
	soap->namespaces = namespaces; } };
	/// Destructor frees deserialized data and soap engine context
	virtual ~Image_Transformations() { if (soap) { soap_destroy(soap); soap_end(soap); soap_free(soap); } };
	/// Invoke 'Threshold' of service 'Image_Transformations' and return error code (or SOAP_OK)
	virtual int ns__Threshold(std::string InputMatFilename, double thresholdValue, double maxValue, std::string thresholdType, std::string &OutputMatFilename) { return soap ? soap_call_ns__Threshold(soap, endpoint, NULL, InputMatFilename, thresholdValue, maxValue, thresholdType, OutputMatFilename) : SOAP_EOM; };
	/// Invoke 'cvtColor' of service 'Image_Transformations' and return error code (or SOAP_OK)
	virtual int ns__cvtColor(std::string InputMatFilename, std::string code, int dstChannel_D, std::string &OutputMatFilename) { return soap ? soap_call_ns__cvtColor(soap, endpoint, NULL, InputMatFilename, code, dstChannel_D, OutputMatFilename) : SOAP_EOM; };
	/// Invoke 'integral' of service 'Image_Transformations' and return error code (or SOAP_OK)
	virtual int ns__integral(std::string InputMatFilename, int sdepth_D, std::string &OutputMatFilename) { return soap ? soap_call_ns__integral(soap, endpoint, NULL, InputMatFilename, sdepth_D, OutputMatFilename) : SOAP_EOM; };
	/// Invoke 'adaptiveThreshold' of service 'Image_Transformations' and return error code (or SOAP_OK)
	virtual int ns__adaptiveThreshold(std::string InputMatFilename, std::string adaptiveMethod, double maxValue, std::string thresholdType, int blockSize, double C, std::string &OutputMatFilename) { return soap ? soap_call_ns__adaptiveThreshold(soap, endpoint, NULL, InputMatFilename, adaptiveMethod, maxValue, thresholdType, blockSize, C, OutputMatFilename) : SOAP_EOM; };
	/// Invoke 'adjustBrighnessAndContrast' of service 'Image_Transformations' and return error code (or SOAP_OK)
	virtual int ns__adjustBrighnessAndContrast(std::string InputMatFilename, double alpha, int beta, std::string &OutputMatFilename) { return soap ? soap_call_ns__adjustBrighnessAndContrast(soap, endpoint, NULL, InputMatFilename, alpha, beta, OutputMatFilename) : SOAP_EOM; };
	/// Invoke 'watershed' of service 'Image_Transformations' and return error code (or SOAP_OK)
	virtual int ns__watershed(std::string InputMatFilename, std::string MarkerMatFilename, std::string &OutputMatFilename) { return soap ? soap_call_ns__watershed(soap, endpoint, NULL, InputMatFilename, MarkerMatFilename, OutputMatFilename) : SOAP_EOM; };
};
#endif