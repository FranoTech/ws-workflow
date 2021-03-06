/* soapimgProcessProxy.h
   Generated by gSOAP 2.8.2 from imgProcess.h
   Copyright(C) 2000-2011, Robert van Engelen, Genivia Inc. All Rights Reserved.
   The generated code is released under one of the following licenses:
   GPL OR Genivia's license for commercial use.
*/

#ifndef soapimgProcessProxy_H
#define soapimgProcessProxy_H
#include "soapH.h"
class imgProcess
{   public:
	/// Runtime engine context allocated in constructor
	struct soap *soap;
	/// Endpoint URL of service 'imgProcess' (change as needed)
	const char *endpoint;
	/// Constructor allocates soap engine context, sets default endpoint URL, and sets namespace mapping table
	imgProcess()
	{ soap = soap_new(); endpoint = "http://localhost/cgi-bin/imgProcessServer"; if (soap && !soap->namespaces) { static const struct Namespace namespaces[] = 
{
	{"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
	{"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"ns", "urn:img", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};
	soap->namespaces = namespaces; } };
	/// Destructor frees deserialized data and soap engine context
	virtual ~imgProcess() { if (soap) { soap_destroy(soap); soap_end(soap); soap_free(soap); } };
	/// Invoke 'Ipl1ChToMat' of service 'imgProcess' and return error code (or SOAP_OK)
	virtual int ns__Ipl1ChToMat(char *InputFilename, ns__ImageData &out) { return soap ? soap_call_ns__Ipl1ChToMat(soap, endpoint, NULL, InputFilename, out) : SOAP_EOM; };
};
#endif
