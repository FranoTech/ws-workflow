/* soapStub.h
   Generated by gSOAP 2.8.8 from highGUI.h

Copyright(C) 2000-2012, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
1) GPL or 2) Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#ifndef soapStub_H
#define soapStub_H
#include "stdsoap2.h"
#if GSOAP_VERSION != 20808
# error "GSOAP VERSION MISMATCH IN GENERATED CODE: PLEASE REINSTALL PACKAGE"
#endif


/******************************************************************************\
 *                                                                            *
 * Enumerations                                                               *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Types with Custom Serializers                                              *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Classes and Structs                                                        *
 *                                                                            *
\******************************************************************************/


#if 0 /* volatile type: do not declare here, declared elsewhere */

#endif

#ifndef SOAP_TYPE_ns__base64Binary
#define SOAP_TYPE_ns__base64Binary (7)
/* Base64 schema type: */
class SOAP_CMAC ns__base64Binary
{
public:
	unsigned char *__ptr;
	int __size;
public:
	virtual int soap_type() const { return 7; } /* = unique id SOAP_TYPE_ns__base64Binary */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         ns__base64Binary() { ns__base64Binary::soap_default(NULL); }
	virtual ~ns__base64Binary() { }
};
#endif

#if 0 /* volatile type: do not declare here, declared elsewhere */

#endif

#ifndef SOAP_TYPE_ns__imReadResponse
#define SOAP_TYPE_ns__imReadResponse (14)
/* ns:imReadResponse */
struct ns__imReadResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns__imRead
#define SOAP_TYPE_ns__imRead (15)
/* ns:imRead */
struct ns__imRead
{
public:
	std::string InputMatFilename;	/* required element of type xsd:string */
	int flag;	/* required element of type xsd:int */
};
#endif

#ifndef SOAP_TYPE_ns__imWriteResponse
#define SOAP_TYPE_ns__imWriteResponse (17)
/* ns:imWriteResponse */
struct ns__imWriteResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns__imWrite
#define SOAP_TYPE_ns__imWrite (18)
/* ns:imWrite */
struct ns__imWrite
{
public:
	std::string InputMatFilename;	/* required element of type xsd:string */
	std::string fileExtension;	/* required element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns__viewImageResponse
#define SOAP_TYPE_ns__viewImageResponse (21)
/* ns:viewImageResponse */
struct ns__viewImageResponse
{
public:
	ns__base64Binary image;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type ns:base64Binary */
};
#endif

#ifndef SOAP_TYPE_ns__viewImage
#define SOAP_TYPE_ns__viewImage (22)
/* ns:viewImage */
struct ns__viewImage
{
public:
	std::string InputMatFilename;	/* required element of type xsd:string */
};
#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Header
#define SOAP_TYPE_SOAP_ENV__Header (23)
/* SOAP Header: */
struct SOAP_ENV__Header
{
#ifdef WITH_NOEMPTYSTRUCT
private:
	char dummy;	/* dummy member to enable compilation */
#endif
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Code
#define SOAP_TYPE_SOAP_ENV__Code (24)
/* SOAP Fault Code: */
struct SOAP_ENV__Code
{
public:
	char *SOAP_ENV__Value;	/* optional element of type xsd:QName */
	struct SOAP_ENV__Code *SOAP_ENV__Subcode;	/* optional element of type SOAP-ENV:Code */
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Detail
#define SOAP_TYPE_SOAP_ENV__Detail (26)
/* SOAP-ENV:Detail */
struct SOAP_ENV__Detail
{
public:
	char *__any;
	int __type;	/* any type of element <fault> (defined below) */
	void *fault;	/* transient */
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Reason
#define SOAP_TYPE_SOAP_ENV__Reason (29)
/* SOAP-ENV:Reason */
struct SOAP_ENV__Reason
{
public:
	char *SOAP_ENV__Text;	/* optional element of type xsd:string */
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Fault
#define SOAP_TYPE_SOAP_ENV__Fault (30)
/* SOAP Fault: */
struct SOAP_ENV__Fault
{
public:
	char *faultcode;	/* optional element of type xsd:QName */
	char *faultstring;	/* optional element of type xsd:string */
	char *faultactor;	/* optional element of type xsd:string */
	struct SOAP_ENV__Detail *detail;	/* optional element of type SOAP-ENV:Detail */
	struct SOAP_ENV__Code *SOAP_ENV__Code;	/* optional element of type SOAP-ENV:Code */
	struct SOAP_ENV__Reason *SOAP_ENV__Reason;	/* optional element of type SOAP-ENV:Reason */
	char *SOAP_ENV__Node;	/* optional element of type xsd:string */
	char *SOAP_ENV__Role;	/* optional element of type xsd:string */
	struct SOAP_ENV__Detail *SOAP_ENV__Detail;	/* optional element of type SOAP-ENV:Detail */
};
#endif

#endif

/******************************************************************************\
 *                                                                            *
 * Typedefs                                                                   *
 *                                                                            *
\******************************************************************************/

#ifndef SOAP_TYPE__QName
#define SOAP_TYPE__QName (5)
typedef char *_QName;
#endif

#ifndef SOAP_TYPE__XML
#define SOAP_TYPE__XML (6)
typedef char *_XML;
#endif


/******************************************************************************\
 *                                                                            *
 * Externals                                                                  *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Server-Side Operations                                                     *
 *                                                                            *
\******************************************************************************/


SOAP_FMAC5 int SOAP_FMAC6 ns__imRead(struct soap*, std::string InputMatFilename, int flag, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__imWrite(struct soap*, std::string InputMatFilename, std::string fileExtension, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__viewImage(struct soap*, std::string InputMatFilename, ns__base64Binary &image);

/******************************************************************************\
 *                                                                            *
 * Server-Side Skeletons to Invoke Service Operations                         *
 *                                                                            *
\******************************************************************************/

SOAP_FMAC5 int SOAP_FMAC6 soap_serve(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_request(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__imRead(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__imWrite(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__viewImage(struct soap*);

/******************************************************************************\
 *                                                                            *
 * Client-Side Call Stubs                                                     *
 *                                                                            *
\******************************************************************************/


SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__imRead(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, int flag, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__imWrite(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, std::string fileExtension, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__viewImage(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, ns__base64Binary &image);

#endif

/* End of soapStub.h */
