/* soapStub.h
   Generated by gSOAP 2.7.17 from imgProcess.h
   Copyright(C) 2000-2010, Robert van Engelen, Genivia Inc. All Rights Reserved.
   This part of the software is released under one of the following licenses:
   GPL, the gSOAP public license, or Genivia's license for commercial use.
*/

#ifndef soapStub_H
#define soapStub_H
#include "stdsoap2.h"

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

#ifndef SOAP_TYPE_ns__ImageData
#define SOAP_TYPE_ns__ImageData (7)
/* Base64 schema type: */
class SOAP_CMAC ns__ImageData
{
public:
	unsigned char *__ptr;
	int __size;
public:
	virtual int soap_type() const { return 7; } /* = unique id SOAP_TYPE_ns__ImageData */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         ns__ImageData(): __ptr(NULL) { ns__ImageData::soap_default(NULL); }
	virtual ~ns__ImageData() { }
};
#endif

#ifndef SOAP_TYPE_ns__getImageResponse
#define SOAP_TYPE_ns__getImageResponse (13)
/* ns:getImageResponse */
struct ns__getImageResponse
{
public:
	ns__ImageData image;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type ns:ImageData */
};
#endif

#ifndef SOAP_TYPE_ns__getImage
#define SOAP_TYPE_ns__getImage (14)
/* ns:getImage */
struct ns__getImage
{
public:
	char *name;	/* optional element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns__Ipl1ChToMatResponse
#define SOAP_TYPE_ns__Ipl1ChToMatResponse (17)
/* ns:Ipl1ChToMatResponse */
struct ns__Ipl1ChToMatResponse
{
public:
	char *OutputFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns__Ipl1ChToMat
#define SOAP_TYPE_ns__Ipl1ChToMat (18)
/* ns:Ipl1ChToMat */
struct ns__Ipl1ChToMat
{
public:
	char *InputFilename;	/* optional element of type xsd:string */
	char *filename;	/* optional element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns__MatToIpl1ChResponse
#define SOAP_TYPE_ns__MatToIpl1ChResponse (20)
/* ns:MatToIpl1ChResponse */
struct ns__MatToIpl1ChResponse
{
public:
	char *OutputFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns__MatToIpl1Ch
#define SOAP_TYPE_ns__MatToIpl1Ch (21)
/* ns:MatToIpl1Ch */
struct ns__MatToIpl1Ch
{
public:
	char *InputFilename;	/* optional element of type xsd:string */
	char *filename;	/* optional element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns__BinaryThresholdResponse
#define SOAP_TYPE_ns__BinaryThresholdResponse (24)
/* ns:BinaryThresholdResponse */
struct ns__BinaryThresholdResponse
{
public:
	char *OutputFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns__BinaryThreshold
#define SOAP_TYPE_ns__BinaryThreshold (25)
/* ns:BinaryThreshold */
struct ns__BinaryThreshold
{
public:
	char *InputFilename;	/* optional element of type xsd:string */
	double threshold;	/* required element of type xsd:double */
	double maxValue;	/* required element of type xsd:double */
	char *filename;	/* optional element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns__MorphOpenResponse
#define SOAP_TYPE_ns__MorphOpenResponse (27)
/* ns:MorphOpenResponse */
struct ns__MorphOpenResponse
{
public:
	char *OutputFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns__MorphOpen
#define SOAP_TYPE_ns__MorphOpen (28)
/* ns:MorphOpen */
struct ns__MorphOpen
{
public:
	char *InputFilename;	/* optional element of type xsd:string */
	char *filename;	/* optional element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Header
#define SOAP_TYPE_SOAP_ENV__Header (29)
/* SOAP Header: */
struct SOAP_ENV__Header
{
#ifdef WITH_NOEMPTYSTRUCT
private:
	char dummy;	/* dummy member to enable compilation */
#endif
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Code
#define SOAP_TYPE_SOAP_ENV__Code (30)
/* SOAP Fault Code: */
struct SOAP_ENV__Code
{
public:
	char *SOAP_ENV__Value;	/* optional element of type xsd:QName */
	struct SOAP_ENV__Code *SOAP_ENV__Subcode;	/* optional element of type SOAP-ENV:Code */
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Detail
#define SOAP_TYPE_SOAP_ENV__Detail (32)
/* SOAP-ENV:Detail */
struct SOAP_ENV__Detail
{
public:
	int __type;	/* any type of element <fault> (defined below) */
	void *fault;	/* transient */
	char *__any;
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Reason
#define SOAP_TYPE_SOAP_ENV__Reason (35)
/* SOAP-ENV:Reason */
struct SOAP_ENV__Reason
{
public:
	char *SOAP_ENV__Text;	/* optional element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Fault
#define SOAP_TYPE_SOAP_ENV__Fault (36)
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


SOAP_FMAC5 int SOAP_FMAC6 ns__getImage(struct soap*, char *name, ns__ImageData &image);

SOAP_FMAC5 int SOAP_FMAC6 ns__Ipl1ChToMat(struct soap*, char *InputFilename, char *filename, char *&OutputFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__MatToIpl1Ch(struct soap*, char *InputFilename, char *filename, char *&OutputFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__BinaryThreshold(struct soap*, char *InputFilename, double threshold, double maxValue, char *filename, char *&OutputFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__MorphOpen(struct soap*, char *InputFilename, char *filename, char *&OutputFilename);

/******************************************************************************\
 *                                                                            *
 * Server-Side Skeletons to Invoke Service Operations                         *
 *                                                                            *
\******************************************************************************/

SOAP_FMAC5 int SOAP_FMAC6 soap_serve(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_request(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__getImage(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__Ipl1ChToMat(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__MatToIpl1Ch(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__BinaryThreshold(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__MorphOpen(struct soap*);

/******************************************************************************\
 *                                                                            *
 * Client-Side Call Stubs                                                     *
 *                                                                            *
\******************************************************************************/


SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__getImage(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *name, ns__ImageData &image);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__Ipl1ChToMat(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *InputFilename, char *filename, char *&OutputFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__MatToIpl1Ch(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *InputFilename, char *filename, char *&OutputFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__BinaryThreshold(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *InputFilename, double threshold, double maxValue, char *filename, char *&OutputFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__MorphOpen(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *InputFilename, char *filename, char *&OutputFilename);

#endif

/* End of soapStub.h */
