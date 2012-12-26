/* soapStub.h
   Generated by gSOAP 2.8.8 from ImageTransformations.h

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

#if 0 /* volatile type: do not declare here, declared elsewhere */

#endif

#ifndef SOAP_TYPE_ns__ThresholdResponse
#define SOAP_TYPE_ns__ThresholdResponse (12)
/* ns:ThresholdResponse */
struct ns__ThresholdResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns__Threshold
#define SOAP_TYPE_ns__Threshold (13)
/* ns:Threshold */
struct ns__Threshold
{
public:
	std::string InputMatFilename;	/* required element of type xsd:string */
	double thresholdValue;	/* required element of type xsd:double */
	double maxValue;	/* required element of type xsd:double */
	std::string thresholdType;	/* required element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns__cvtColorResponse
#define SOAP_TYPE_ns__cvtColorResponse (15)
/* ns:cvtColorResponse */
struct ns__cvtColorResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns__cvtColor
#define SOAP_TYPE_ns__cvtColor (16)
/* ns:cvtColor */
struct ns__cvtColor
{
public:
	std::string InputMatFilename;	/* required element of type xsd:string */
	std::string code;	/* required element of type xsd:string */
	int dstChannel_D;	/* required element of type xsd:int */
};
#endif

#ifndef SOAP_TYPE_ns__integralResponse
#define SOAP_TYPE_ns__integralResponse (18)
/* ns:integralResponse */
struct ns__integralResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns__integral
#define SOAP_TYPE_ns__integral (19)
/* ns:integral */
struct ns__integral
{
public:
	std::string InputMatFilename;	/* required element of type xsd:string */
	int sdepth_D;	/* required element of type xsd:int */
};
#endif

#ifndef SOAP_TYPE_ns__adaptiveThresholdResponse
#define SOAP_TYPE_ns__adaptiveThresholdResponse (21)
/* ns:adaptiveThresholdResponse */
struct ns__adaptiveThresholdResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns__adaptiveThreshold
#define SOAP_TYPE_ns__adaptiveThreshold (22)
/* ns:adaptiveThreshold */
struct ns__adaptiveThreshold
{
public:
	std::string InputMatFilename;	/* required element of type xsd:string */
	std::string adaptiveMethod;	/* required element of type xsd:string */
	double maxValue;	/* required element of type xsd:double */
	std::string thresholdType;	/* required element of type xsd:string */
	int blockSize;	/* required element of type xsd:int */
	double C;	/* required element of type xsd:double */
};
#endif

#ifndef SOAP_TYPE_ns__adjustBrighnessAndContrastResponse
#define SOAP_TYPE_ns__adjustBrighnessAndContrastResponse (24)
/* ns:adjustBrighnessAndContrastResponse */
struct ns__adjustBrighnessAndContrastResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns__adjustBrighnessAndContrast
#define SOAP_TYPE_ns__adjustBrighnessAndContrast (25)
/* ns:adjustBrighnessAndContrast */
struct ns__adjustBrighnessAndContrast
{
public:
	std::string InputMatFilename;	/* required element of type xsd:string */
	double alpha;	/* required element of type xsd:double */
	int beta;	/* required element of type xsd:int */
};
#endif

#ifndef SOAP_TYPE_ns__watershedResponse
#define SOAP_TYPE_ns__watershedResponse (27)
/* ns:watershedResponse */
struct ns__watershedResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns__watershed
#define SOAP_TYPE_ns__watershed (28)
/* ns:watershed */
struct ns__watershed
{
public:
	std::string InputMatFilename;	/* required element of type xsd:string */
	std::string MarkerMatFilename;	/* required element of type xsd:string */
};
#endif

#ifndef WITH_NOGLOBAL

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

#endif

#ifndef WITH_NOGLOBAL

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

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Detail
#define SOAP_TYPE_SOAP_ENV__Detail (32)
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
#define SOAP_TYPE_SOAP_ENV__Reason (35)
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


SOAP_FMAC5 int SOAP_FMAC6 ns__Threshold(struct soap*, std::string InputMatFilename, double thresholdValue, double maxValue, std::string thresholdType, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__cvtColor(struct soap*, std::string InputMatFilename, std::string code, int dstChannel_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__integral(struct soap*, std::string InputMatFilename, int sdepth_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__adaptiveThreshold(struct soap*, std::string InputMatFilename, std::string adaptiveMethod, double maxValue, std::string thresholdType, int blockSize, double C, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__adjustBrighnessAndContrast(struct soap*, std::string InputMatFilename, double alpha, int beta, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__watershed(struct soap*, std::string InputMatFilename, std::string MarkerMatFilename, std::string &OutputMatFilename);

/******************************************************************************\
 *                                                                            *
 * Server-Side Skeletons to Invoke Service Operations                         *
 *                                                                            *
\******************************************************************************/

SOAP_FMAC5 int SOAP_FMAC6 soap_serve(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_request(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__Threshold(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__cvtColor(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__integral(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__adaptiveThreshold(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__adjustBrighnessAndContrast(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__watershed(struct soap*);

/******************************************************************************\
 *                                                                            *
 * Client-Side Call Stubs                                                     *
 *                                                                            *
\******************************************************************************/


SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__Threshold(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, double thresholdValue, double maxValue, std::string thresholdType, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__cvtColor(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, std::string code, int dstChannel_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__integral(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, int sdepth_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__adaptiveThreshold(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, std::string adaptiveMethod, double maxValue, std::string thresholdType, int blockSize, double C, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__adjustBrighnessAndContrast(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, double alpha, int beta, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__watershed(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, std::string MarkerMatFilename, std::string &OutputMatFilename);

#endif

/* End of soapStub.h */
