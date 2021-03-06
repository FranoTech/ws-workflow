/* soapStub.h
   Generated by gSOAP 2.8.14 from BasicStructures.h

Copyright(C) 2000-2013, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under ONE of the following licenses:
GPL or Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#ifndef soapStub_H
#define soapStub_H
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

#ifndef SOAP_TYPE_ns__MatDetail
#define SOAP_TYPE_ns__MatDetail (7)
/* ns:MatDetail */
class SOAP_CMAC ns__MatDetail
{
public:
	int columns;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:int */
	int rows;	/* required element of type xsd:int */
	std::string depth;	/* required element of type xsd:string */
	std::string type;	/* required element of type xsd:string */
	int channel;	/* required element of type xsd:int */
	bool empty;	/* required element of type xsd:boolean */
public:
	virtual int soap_type() const { return 7; } /* = unique id SOAP_TYPE_ns__MatDetail */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         ns__MatDetail() { ns__MatDetail::soap_default(NULL); }
	virtual ~ns__MatDetail() { }
};
#endif

#ifndef SOAP_TYPE_ns__rowRangeResponse
#define SOAP_TYPE_ns__rowRangeResponse (12)
/* ns:rowRangeResponse */
struct ns__rowRangeResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
public:
	int soap_type() const { return 12; } /* = unique id SOAP_TYPE_ns__rowRangeResponse */
};
#endif

#ifndef SOAP_TYPE_ns__rowRange
#define SOAP_TYPE_ns__rowRange (13)
/* ns:rowRange */
struct ns__rowRange
{
public:
	std::string InputMatFilename;	/* required element of type xsd:string */
	int startCol;	/* required element of type xsd:int */
	int endCol;	/* required element of type xsd:int */
public:
	int soap_type() const { return 13; } /* = unique id SOAP_TYPE_ns__rowRange */
};
#endif

#ifndef SOAP_TYPE_ns__colRangeResponse
#define SOAP_TYPE_ns__colRangeResponse (15)
/* ns:colRangeResponse */
struct ns__colRangeResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
public:
	int soap_type() const { return 15; } /* = unique id SOAP_TYPE_ns__colRangeResponse */
};
#endif

#ifndef SOAP_TYPE_ns__colRange
#define SOAP_TYPE_ns__colRange (16)
/* ns:colRange */
struct ns__colRange
{
public:
	std::string InputMatFilename;	/* required element of type xsd:string */
	int startCol;	/* required element of type xsd:int */
	int endCol;	/* required element of type xsd:int */
public:
	int soap_type() const { return 16; } /* = unique id SOAP_TYPE_ns__colRange */
};
#endif

#ifndef SOAP_TYPE_ns__convertToResponse
#define SOAP_TYPE_ns__convertToResponse (19)
/* ns:convertToResponse */
struct ns__convertToResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
public:
	int soap_type() const { return 19; } /* = unique id SOAP_TYPE_ns__convertToResponse */
};
#endif

#ifndef SOAP_TYPE_ns__convertTo
#define SOAP_TYPE_ns__convertTo (20)
/* ns:convertTo */
struct ns__convertTo
{
public:
	std::string InputMatFilename;	/* required element of type xsd:string */
	std::string types;	/* required element of type xsd:string */
	double alpha_D;	/* required element of type xsd:double */
	double beta_D;	/* required element of type xsd:double */
public:
	int soap_type() const { return 20; } /* = unique id SOAP_TYPE_ns__convertTo */
};
#endif

#ifndef SOAP_TYPE_ns__createMatResponse
#define SOAP_TYPE_ns__createMatResponse (22)
/* ns:createMatResponse */
struct ns__createMatResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
public:
	int soap_type() const { return 22; } /* = unique id SOAP_TYPE_ns__createMatResponse */
};
#endif

#ifndef SOAP_TYPE_ns__createMat
#define SOAP_TYPE_ns__createMat (23)
/* ns:createMat */
struct ns__createMat
{
public:
	int rows;	/* required element of type xsd:int */
	int columns;	/* required element of type xsd:int */
	std::string type;	/* required element of type xsd:string */
	int scalar;	/* required element of type xsd:int */
public:
	int soap_type() const { return 23; } /* = unique id SOAP_TYPE_ns__createMat */
};
#endif

#ifndef SOAP_TYPE_ns__InverseResponse
#define SOAP_TYPE_ns__InverseResponse (25)
/* ns:InverseResponse */
struct ns__InverseResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
public:
	int soap_type() const { return 25; } /* = unique id SOAP_TYPE_ns__InverseResponse */
};
#endif

#ifndef SOAP_TYPE_ns__Inverse
#define SOAP_TYPE_ns__Inverse (26)
/* ns:Inverse */
struct ns__Inverse
{
public:
	std::string InputMatFilename;	/* required element of type xsd:string */
	std::string InvMethod_D;	/* required element of type xsd:string */
public:
	int soap_type() const { return 26; } /* = unique id SOAP_TYPE_ns__Inverse */
};
#endif

#ifndef SOAP_TYPE_ns__mulResponse
#define SOAP_TYPE_ns__mulResponse (28)
/* ns:mulResponse */
struct ns__mulResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
public:
	int soap_type() const { return 28; } /* = unique id SOAP_TYPE_ns__mulResponse */
};
#endif

#ifndef SOAP_TYPE_ns__mul
#define SOAP_TYPE_ns__mul (29)
/* ns:mul */
struct ns__mul
{
public:
	std::string InputMatFilename;	/* required element of type xsd:string */
	std::string AnotherMatFilename;	/* required element of type xsd:string */
	double scale_D;	/* required element of type xsd:double */
public:
	int soap_type() const { return 29; } /* = unique id SOAP_TYPE_ns__mul */
};
#endif

#ifndef SOAP_TYPE_ns__crossResponse
#define SOAP_TYPE_ns__crossResponse (31)
/* ns:crossResponse */
struct ns__crossResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
public:
	int soap_type() const { return 31; } /* = unique id SOAP_TYPE_ns__crossResponse */
};
#endif

#ifndef SOAP_TYPE_ns__cross
#define SOAP_TYPE_ns__cross (32)
/* ns:cross */
struct ns__cross
{
public:
	std::string InputMatFilename;	/* required element of type xsd:string */
	std::string AnotherMatFilename;	/* required element of type xsd:string */
public:
	int soap_type() const { return 32; } /* = unique id SOAP_TYPE_ns__cross */
};
#endif

#ifndef SOAP_TYPE_ns__dotResponse
#define SOAP_TYPE_ns__dotResponse (34)
/* ns:dotResponse */
struct ns__dotResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
public:
	int soap_type() const { return 34; } /* = unique id SOAP_TYPE_ns__dotResponse */
};
#endif

#ifndef SOAP_TYPE_ns__dot
#define SOAP_TYPE_ns__dot (35)
/* ns:dot */
struct ns__dot
{
public:
	std::string InputMatFilename;	/* required element of type xsd:string */
	std::string AnotherMatFilename;	/* required element of type xsd:string */
public:
	int soap_type() const { return 35; } /* = unique id SOAP_TYPE_ns__dot */
};
#endif

#ifndef SOAP_TYPE_ns__zerosResponse
#define SOAP_TYPE_ns__zerosResponse (37)
/* ns:zerosResponse */
struct ns__zerosResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
public:
	int soap_type() const { return 37; } /* = unique id SOAP_TYPE_ns__zerosResponse */
};
#endif

#ifndef SOAP_TYPE_ns__zeros
#define SOAP_TYPE_ns__zeros (38)
/* ns:zeros */
struct ns__zeros
{
public:
	int rows;	/* required element of type xsd:int */
	int columns;	/* required element of type xsd:int */
	std::string type;	/* required element of type xsd:string */
public:
	int soap_type() const { return 38; } /* = unique id SOAP_TYPE_ns__zeros */
};
#endif

#ifndef SOAP_TYPE_ns__onesResponse
#define SOAP_TYPE_ns__onesResponse (40)
/* ns:onesResponse */
struct ns__onesResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
public:
	int soap_type() const { return 40; } /* = unique id SOAP_TYPE_ns__onesResponse */
};
#endif

#ifndef SOAP_TYPE_ns__ones
#define SOAP_TYPE_ns__ones (41)
/* ns:ones */
struct ns__ones
{
public:
	int rows;	/* required element of type xsd:int */
	int columns;	/* required element of type xsd:int */
	int fillWith;	/* required element of type xsd:int */
	std::string type;	/* required element of type xsd:string */
public:
	int soap_type() const { return 41; } /* = unique id SOAP_TYPE_ns__ones */
};
#endif

#ifndef SOAP_TYPE_ns__getMatDetail
#define SOAP_TYPE_ns__getMatDetail (44)
/* ns:getMatDetail */
struct ns__getMatDetail
{
public:
	std::string InputMatFilename;	/* required element of type xsd:string */
public:
	int soap_type() const { return 44; } /* = unique id SOAP_TYPE_ns__getMatDetail */
};
#endif

#ifndef SOAP_TYPE_ns__printAllMatValueResponse
#define SOAP_TYPE_ns__printAllMatValueResponse (46)
/* ns:printAllMatValueResponse */
struct ns__printAllMatValueResponse
{
public:
	std::string OutputMat;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
public:
	int soap_type() const { return 46; } /* = unique id SOAP_TYPE_ns__printAllMatValueResponse */
};
#endif

#ifndef SOAP_TYPE_ns__printAllMatValue
#define SOAP_TYPE_ns__printAllMatValue (47)
/* ns:printAllMatValue */
struct ns__printAllMatValue
{
public:
	std::string InputMatFilename;	/* required element of type xsd:string */
public:
	int soap_type() const { return 47; } /* = unique id SOAP_TYPE_ns__printAllMatValue */
};
#endif

#ifndef SOAP_TYPE_ns__accessPixelValueResponse
#define SOAP_TYPE_ns__accessPixelValueResponse (50)
/* ns:accessPixelValueResponse */
struct ns__accessPixelValueResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
public:
	int soap_type() const { return 50; } /* = unique id SOAP_TYPE_ns__accessPixelValueResponse */
};
#endif

#ifndef SOAP_TYPE_ns__accessPixelValue
#define SOAP_TYPE_ns__accessPixelValue (51)
/* ns:accessPixelValue */
struct ns__accessPixelValue
{
public:
	std::string InputMatFilename;	/* required element of type xsd:string */
	std::string returnType;	/* required element of type xsd:string */
	int intToSet;	/* required element of type xsd:int */
	float floatToSet;	/* required element of type xsd:float */
	int pixelI;	/* required element of type xsd:int */
	int pixelJ;	/* required element of type xsd:int */
	int channel;	/* required element of type xsd:int */
public:
	int soap_type() const { return 51; } /* = unique id SOAP_TYPE_ns__accessPixelValue */
};
#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Header
#define SOAP_TYPE_SOAP_ENV__Header (52)
/* SOAP Header: */
struct SOAP_ENV__Header
{
public:
	int soap_type() const { return 52; } /* = unique id SOAP_TYPE_SOAP_ENV__Header */
#ifdef WITH_NOEMPTYSTRUCT
private:
	char dummy;	/* dummy member to enable compilation */
#endif
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Code
#define SOAP_TYPE_SOAP_ENV__Code (53)
/* SOAP Fault Code: */
struct SOAP_ENV__Code
{
public:
	char *SOAP_ENV__Value;	/* optional element of type xsd:QName */
	struct SOAP_ENV__Code *SOAP_ENV__Subcode;	/* optional element of type SOAP-ENV:Code */
public:
	int soap_type() const { return 53; } /* = unique id SOAP_TYPE_SOAP_ENV__Code */
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Detail
#define SOAP_TYPE_SOAP_ENV__Detail (55)
/* SOAP-ENV:Detail */
struct SOAP_ENV__Detail
{
public:
	char *__any;
	int __type;	/* any type of element <fault> (defined below) */
	void *fault;	/* transient */
public:
	int soap_type() const { return 55; } /* = unique id SOAP_TYPE_SOAP_ENV__Detail */
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Reason
#define SOAP_TYPE_SOAP_ENV__Reason (58)
/* SOAP-ENV:Reason */
struct SOAP_ENV__Reason
{
public:
	char *SOAP_ENV__Text;	/* optional element of type xsd:string */
public:
	int soap_type() const { return 58; } /* = unique id SOAP_TYPE_SOAP_ENV__Reason */
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Fault
#define SOAP_TYPE_SOAP_ENV__Fault (59)
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
	int soap_type() const { return 59; } /* = unique id SOAP_TYPE_SOAP_ENV__Fault */
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


SOAP_FMAC5 int SOAP_FMAC6 ns__rowRange(struct soap*, std::string InputMatFilename, int startCol, int endCol, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__colRange(struct soap*, std::string InputMatFilename, int startCol, int endCol, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__convertTo(struct soap*, std::string InputMatFilename, std::string types, double alpha_D, double beta_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__createMat(struct soap*, int rows, int columns, std::string type, int scalar, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__Inverse(struct soap*, std::string InputMatFilename, std::string InvMethod_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__mul(struct soap*, std::string InputMatFilename, std::string AnotherMatFilename, double scale_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__cross(struct soap*, std::string InputMatFilename, std::string AnotherMatFilename, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__dot(struct soap*, std::string InputMatFilename, std::string AnotherMatFilename, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__zeros(struct soap*, int rows, int columns, std::string type, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__ones(struct soap*, int rows, int columns, int fillWith, std::string type, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__getMatDetail(struct soap*, std::string InputMatFilename, ns__MatDetail &detail);

SOAP_FMAC5 int SOAP_FMAC6 ns__printAllMatValue(struct soap*, std::string InputMatFilename, std::string &OutputMat);

SOAP_FMAC5 int SOAP_FMAC6 ns__accessPixelValue(struct soap*, std::string InputMatFilename, std::string returnType, int intToSet, float floatToSet, int pixelI, int pixelJ, int channel, std::string &OutputMatFilename);

/******************************************************************************\
 *                                                                            *
 * Server-Side Skeletons to Invoke Service Operations                         *
 *                                                                            *
\******************************************************************************/

extern "C" SOAP_FMAC5 int SOAP_FMAC6 soap_serve(struct soap*);

extern "C" SOAP_FMAC5 int SOAP_FMAC6 soap_serve_request(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__rowRange(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__colRange(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__convertTo(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__createMat(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__Inverse(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__mul(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__cross(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__dot(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__zeros(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__ones(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__getMatDetail(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__printAllMatValue(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__accessPixelValue(struct soap*);

/******************************************************************************\
 *                                                                            *
 * Client-Side Call Stubs                                                     *
 *                                                                            *
\******************************************************************************/


SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__rowRange(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, int startCol, int endCol, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__colRange(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, int startCol, int endCol, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__convertTo(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, std::string types, double alpha_D, double beta_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__createMat(struct soap *soap, const char *soap_endpoint, const char *soap_action, int rows, int columns, std::string type, int scalar, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__Inverse(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, std::string InvMethod_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__mul(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, std::string AnotherMatFilename, double scale_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__cross(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, std::string AnotherMatFilename, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__dot(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, std::string AnotherMatFilename, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__zeros(struct soap *soap, const char *soap_endpoint, const char *soap_action, int rows, int columns, std::string type, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__ones(struct soap *soap, const char *soap_endpoint, const char *soap_action, int rows, int columns, int fillWith, std::string type, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__getMatDetail(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, ns__MatDetail &detail);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__printAllMatValue(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, std::string &OutputMat);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__accessPixelValue(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, std::string returnType, int intToSet, float floatToSet, int pixelI, int pixelJ, int channel, std::string &OutputMatFilename);

#endif

/* End of soapStub.h */
