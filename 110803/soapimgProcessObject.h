/* soapimgProcessObject.h
   Generated by gSOAP 2.8.2 from imgProcess.h
   Copyright(C) 2000-2011, Robert van Engelen, Genivia Inc. All Rights Reserved.
   The generated code is released under one of the following licenses:
   GPL OR Genivia's license for commercial use.
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


SOAP_FMAC5 int SOAP_FMAC6 ns__getImage(struct soap*, char *name, ns__ImageData &image);

SOAP_FMAC5 int SOAP_FMAC6 ns__Ipl1ChToMat(struct soap*, char *InputFilename, char *&OutputFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__MatToJPG(struct soap*, char *InputFilename, char *&OutputFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__BinaryThreshold(struct soap*, char *InputFilename, double threshold, double maxValue, char *&OutputFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__MorphOpen(struct soap*, char *InputFilename, char *&OutputFilename);

#endif
