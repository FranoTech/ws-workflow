/* soapStub.h
   Generated by gSOAP 2.8.14 from Drawing.h

Copyright(C) 2000-2013, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under ONE of the following licenses:
GPL or Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#ifndef soapStub_H
#define soapStub_H
#include <string>
#include "stdsoap2.h"
#if GSOAP_VERSION != 20814
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

#if 0 /* volatile type: do not declare here, declared elsewhere */

#endif

#ifndef SOAP_TYPE_ns__circleResponse
#define SOAP_TYPE_ns__circleResponse (10)
/* ns:circleResponse */
struct ns__circleResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
public:
	int soap_type() const { return 10; } /* = unique id SOAP_TYPE_ns__circleResponse */
};
#endif

#ifndef SOAP_TYPE_ns__circle
#define SOAP_TYPE_ns__circle (11)
/* ns:circle */
struct ns__circle
{
public:
	std::string InputMatFilename;	/* required element of type xsd:string */
	int centerX;	/* required element of type xsd:int */
	int centerY;	/* required element of type xsd:int */
	int radius;	/* required element of type xsd:int */
	int scalarColor0;	/* required element of type xsd:int */
	int scalarColor1;	/* required element of type xsd:int */
	int scalarColor2;	/* required element of type xsd:int */
	int thickness_D;	/* required element of type xsd:int */
	int lineType_D;	/* required element of type xsd:int */
	int shift_D;	/* required element of type xsd:int */
public:
	int soap_type() const { return 11; } /* = unique id SOAP_TYPE_ns__circle */
};
#endif

#ifndef SOAP_TYPE_ns__ellipseResponse
#define SOAP_TYPE_ns__ellipseResponse (15)
/* ns:ellipseResponse */
struct ns__ellipseResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
public:
	int soap_type() const { return 15; } /* = unique id SOAP_TYPE_ns__ellipseResponse */
};
#endif

#ifndef SOAP_TYPE_ns__ellipse
#define SOAP_TYPE_ns__ellipse (16)
/* ns:ellipse */
struct ns__ellipse
{
public:
	std::string InputMatFilename;	/* required element of type xsd:string */
	int centerX;	/* required element of type xsd:int */
	int centerY;	/* required element of type xsd:int */
	int axeX;	/* required element of type xsd:int */
	int axeY;	/* required element of type xsd:int */
	double angle;	/* required element of type xsd:double */
	double startAngle;	/* required element of type xsd:double */
	double endAngle;	/* required element of type xsd:double */
	int scalarColor0;	/* required element of type xsd:int */
	int scalarColor1;	/* required element of type xsd:int */
	int scalarColor2;	/* required element of type xsd:int */
	int thickness_D;	/* required element of type xsd:int */
	int lineType_D;	/* required element of type xsd:int */
	int shift_D;	/* required element of type xsd:int */
public:
	int soap_type() const { return 16; } /* = unique id SOAP_TYPE_ns__ellipse */
};
#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Header
#define SOAP_TYPE_SOAP_ENV__Header (17)
/* SOAP Header: */
struct SOAP_ENV__Header
{
public:
	int soap_type() const { return 17; } /* = unique id SOAP_TYPE_SOAP_ENV__Header */
#ifdef WITH_NOEMPTYSTRUCT
private:
	char dummy;	/* dummy member to enable compilation */
#endif
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Code
#define SOAP_TYPE_SOAP_ENV__Code (18)
/* SOAP Fault Code: */
struct SOAP_ENV__Code
{
public:
	char *SOAP_ENV__Value;	/* optional element of type xsd:QName */
	struct SOAP_ENV__Code *SOAP_ENV__Subcode;	/* optional element of type SOAP-ENV:Code */
public:
	int soap_type() const { return 18; } /* = unique id SOAP_TYPE_SOAP_ENV__Code */
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Detail
#define SOAP_TYPE_SOAP_ENV__Detail (20)
/* SOAP-ENV:Detail */
struct SOAP_ENV__Detail
{
public:
	char *__any;
	int __type;	/* any type of element <fault> (defined below) */
	void *fault;	/* transient */
public:
	int soap_type() const { return 20; } /* = unique id SOAP_TYPE_SOAP_ENV__Detail */
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Reason
#define SOAP_TYPE_SOAP_ENV__Reason (23)
/* SOAP-ENV:Reason */
struct SOAP_ENV__Reason
{
public:
	char *SOAP_ENV__Text;	/* optional element of type xsd:string */
public:
	int soap_type() const { return 23; } /* = unique id SOAP_TYPE_SOAP_ENV__Reason */
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Fault
#define SOAP_TYPE_SOAP_ENV__Fault (24)
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
public:
	int soap_type() const { return 24; } /* = unique id SOAP_TYPE_SOAP_ENV__Fault */
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


SOAP_FMAC5 int SOAP_FMAC6 ns__circle(struct soap*, std::string InputMatFilename, int centerX, int centerY, int radius, int scalarColor0, int scalarColor1, int scalarColor2, int thickness_D, int lineType_D, int shift_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__ellipse(struct soap*, std::string InputMatFilename, int centerX, int centerY, int axeX, int axeY, double angle, double startAngle, double endAngle, int scalarColor0, int scalarColor1, int scalarColor2, int thickness_D, int lineType_D, int shift_D, std::string &OutputMatFilename);

/******************************************************************************\
 *                                                                            *
 * Server-Side Skeletons to Invoke Service Operations                         *
 *                                                                            *
\******************************************************************************/

extern "C" SOAP_FMAC5 int SOAP_FMAC6 soap_serve(struct soap*);

extern "C" SOAP_FMAC5 int SOAP_FMAC6 soap_serve_request(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__circle(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__ellipse(struct soap*);

/******************************************************************************\
 *                                                                            *
 * Client-Side Call Stubs                                                     *
 *                                                                            *
\******************************************************************************/


SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__circle(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, int centerX, int centerY, int radius, int scalarColor0, int scalarColor1, int scalarColor2, int thickness_D, int lineType_D, int shift_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__ellipse(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, int centerX, int centerY, int axeX, int axeY, double angle, double startAngle, double endAngle, int scalarColor0, int scalarColor1, int scalarColor2, int thickness_D, int lineType_D, int shift_D, std::string &OutputMatFilename);

#endif

/* End of soapStub.h */
