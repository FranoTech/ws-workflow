/* soapimgProcessObject.h
   Generated by gSOAP 2.8.6 from imgProcess.h

Copyright(C) 2000-2011, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
1) GPL or 2) Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#ifndef soapimgProcessObject_H
#define soapimgProcessObject_H
#include "soapH.h"

/******************************************************************************\
 *                                                                            *
 * Service Object                                                             *
 *                                                                            *
\******************************************************************************/

class imgProcessService : public soap
{    public:
	imgProcessService()
	{ static const struct Namespace namespaces[] =
{
	{"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
	{"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"ns", "urn:img", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};

	this->namespaces = namespaces; };
	virtual ~imgProcessService() { };
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


SOAP_FMAC5 int SOAP_FMAC6 ns__loadMat(struct soap*, char *InputImageFilename, int loadparam, char **OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__binaryThreshold(struct soap*, char *InputMatFilename, double thresholdValue, double maxValue, char **OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__morphOpen(struct soap*, char *InpuMattFilename, char **OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__MatToJPG(struct soap*, char *InputMatFilename, char **OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__findContoursAndFillpoly(struct soap*, char *InputMatFilename, int lowerBound, ns__FindContours &out);

SOAP_FMAC5 int SOAP_FMAC6 ns__erode(struct soap*, char *src, char *element, int iteration, char **OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__dilate(struct soap*, char *src, char *element, int iteration, char **OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__Or(struct soap*, char *src1, char *src2, char **OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__And(struct soap*, char *src1, char *src2, char **OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__Not(struct soap*, char *src, char **OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__removeSmallCell(struct soap*, char *inputMatFilename, ns__RemoveSmallCell &out);

SOAP_FMAC5 int SOAP_FMAC6 ns__scanningCell(struct soap*, char *inputMatFilename, char **outputMatFilename);

#endif
