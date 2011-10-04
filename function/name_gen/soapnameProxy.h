/* soapnameProxy.h
   Generated by gSOAP 2.8.2 from name.h
   Copyright(C) 2000-2011, Robert van Engelen, Genivia Inc. All Rights Reserved.
   The generated code is released under one of the following licenses:
   GPL OR Genivia's license for commercial use.
*/

#ifndef soapnameProxy_H
#define soapnameProxy_H
#include "soapH.h"
class name
{   public:
	/// Runtime engine context allocated in constructor
	struct soap *soap;
	/// Endpoint URL of service 'name' (change as needed)
	const char *endpoint;
	/// Constructor allocates soap engine context, sets default endpoint URL, and sets namespace mapping table
	name()
	{ soap = soap_new(); endpoint = "http://localhost/cgi-bin/name"; if (soap && !soap->namespaces) { static const struct Namespace namespaces[] = 
{
	{"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
	{"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"ns", "urn:n", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};
	soap->namespaces = namespaces; } };
	/// Destructor frees deserialized data and soap engine context
	virtual ~name() { if (soap) { soap_destroy(soap); soap_end(soap); soap_free(soap); } };
	/// Invoke 'genName' of service 'name' and return error code (or SOAP_OK)
	virtual int ns__genName(char *InputFilename, char *&OutputFilename) { return soap ? soap_call_ns__genName(soap, endpoint, NULL, InputFilename, OutputFilename) : SOAP_EOM; };
	/// Invoke 'genName2' of service 'name' and return error code (or SOAP_OK)
	virtual int ns__genName2(char *InputFilename, char **OutputFilename) { return soap ? soap_call_ns__genName2(soap, endpoint, NULL, InputFilename, OutputFilename) : SOAP_EOM; };
	/// Invoke 'genName3' of service 'name' and return error code (or SOAP_OK)
	virtual int ns__genName3(char *InputFilename, ns__Output &out) { return soap ? soap_call_ns__genName3(soap, endpoint, NULL, InputFilename, out) : SOAP_EOM; };
};
#endif