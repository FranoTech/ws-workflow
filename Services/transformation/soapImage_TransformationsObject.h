/* soapImage_TransformationsObject.h
   Generated by gSOAP 2.8.8 from ImageTransformations.h

Copyright(C) 2000-2012, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
1) GPL or 2) Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#ifndef soapImage_TransformationsObject_H
#define soapImage_TransformationsObject_H
#include "soapH.h"

/******************************************************************************\
 *                                                                            *
 * Service Object                                                             *
 *                                                                            *
\******************************************************************************/

class Image_TransformationsService : public soap
{    public:
	Image_TransformationsService()
	{ static const struct Namespace namespaces[] =
{
	{"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
	{"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"ns", "urn:trn", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};

	this->namespaces = namespaces; };
	virtual ~Image_TransformationsService() { };
	/// Bind service to port (returns master socket or SOAP_INVALID_SOCKET)
	virtual	SOAP_SOCKET bind(const char *host, int port, int backlog) { return soap_bind(this, host, port, backlog); };
	/// Accept next request (returns socket or SOAP_INVALID_SOCKET)
	virtual	SOAP_SOCKET accept() { return soap_accept(this); };
	/// Serve this request (returns error code or SOAP_OK)
	virtual	int serve() { return soap_serve(this); };
};

/******************************************************************************\
 *                                                                            *
 * Service Operations (you should define these globally)                      *
 *                                                                            *
\******************************************************************************/


SOAP_FMAC5 int SOAP_FMAC6 ns__Threshold(struct soap*, std::string InputMatFilename, double thresholdValue, double maxValue, std::string thresholdType, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__cvtColor(struct soap*, std::string InputMatFilename, std::string code, int dstChannel_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__integral(struct soap*, std::string InputMatFilename, int sdepth_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__adaptiveThreshold(struct soap*, std::string InputMatFilename, std::string adaptiveMethod, double maxValue, std::string thresholdType, int blockSize, double C, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__adjustBrighnessAndContrast(struct soap*, std::string InputMatFilename, double alpha, int beta, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__watershed(struct soap*, std::string InputMatFilename, std::string MarkerMatFilename, std::string &OutputMatFilename);

#endif