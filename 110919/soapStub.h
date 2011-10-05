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

#ifndef SOAP_TYPE_ns__FindContours
#define SOAP_TYPE_ns__FindContours (7)
/* ns:FindContours */
class SOAP_CMAC ns__FindContours
{
public:
	char *smallerArea;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type xsd:string */
	char *biggerArea;	/* optional element of type xsd:string */
public:
	virtual int soap_type() const { return 7; } /* = unique id SOAP_TYPE_ns__FindContours */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         ns__FindContours(): smallerArea(NULL), biggerArea(NULL) { ns__FindContours::soap_default(NULL); }
	virtual ~ns__FindContours() { }
};
#endif

#ifndef SOAP_TYPE_ns__RemoveSmallCell
#define SOAP_TYPE_ns__RemoveSmallCell (8)
/* ns:RemoveSmallCell */
class SOAP_CMAC ns__RemoveSmallCell
{
public:
	char *keepedArea;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type xsd:string */
	char *biggerArea;	/* optional element of type xsd:string */
public:
	virtual int soap_type() const { return 8; } /* = unique id SOAP_TYPE_ns__RemoveSmallCell */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         ns__RemoveSmallCell(): keepedArea(NULL), biggerArea(NULL) { ns__RemoveSmallCell::soap_default(NULL); }
	virtual ~ns__RemoveSmallCell() { }
};
#endif

#ifndef SOAP_TYPE_ns__loadMatResponse
#define SOAP_TYPE_ns__loadMatResponse (11)
/* ns:loadMatResponse */
struct ns__loadMatResponse
{
public:
	char *OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns__loadMat
#define SOAP_TYPE_ns__loadMat (12)
/* ns:loadMat */
struct ns__loadMat
{
public:
	char *InputImageFilename;	/* optional element of type xsd:string */
	int loadparam;	/* required element of type xsd:int */
};
#endif

#ifndef SOAP_TYPE_ns__binaryThresholdResponse
#define SOAP_TYPE_ns__binaryThresholdResponse (15)
/* ns:binaryThresholdResponse */
struct ns__binaryThresholdResponse
{
public:
	char *OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns__binaryThreshold
#define SOAP_TYPE_ns__binaryThreshold (16)
/* ns:binaryThreshold */
struct ns__binaryThreshold
{
public:
	char *InputMatFilename;	/* optional element of type xsd:string */
	double thresholdValue;	/* required element of type xsd:double */
	double maxValue;	/* required element of type xsd:double */
};
#endif

#ifndef SOAP_TYPE_ns__morphOpenResponse
#define SOAP_TYPE_ns__morphOpenResponse (18)
/* ns:morphOpenResponse */
struct ns__morphOpenResponse
{
public:
	char *OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns__morphOpen
#define SOAP_TYPE_ns__morphOpen (19)
/* ns:morphOpen */
struct ns__morphOpen
{
public:
	char *InpuMattFilename;	/* optional element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns__MatToJPGResponse
#define SOAP_TYPE_ns__MatToJPGResponse (21)
/* ns:MatToJPGResponse */
struct ns__MatToJPGResponse
{
public:
	char *OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns__MatToJPG
#define SOAP_TYPE_ns__MatToJPG (22)
/* ns:MatToJPG */
struct ns__MatToJPG
{
public:
	char *InputMatFilename;	/* optional element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns__findContoursAndFillpoly
#define SOAP_TYPE_ns__findContoursAndFillpoly (25)
/* ns:findContoursAndFillpoly */
struct ns__findContoursAndFillpoly
{
public:
	char *InputMatFilename;	/* optional element of type xsd:string */
	int lowerBound;	/* required element of type xsd:int */
};
#endif

#ifndef SOAP_TYPE_ns__erodeResponse
#define SOAP_TYPE_ns__erodeResponse (28)
/* ns:erodeResponse */
struct ns__erodeResponse
{
public:
	char **OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns__erode
#define SOAP_TYPE_ns__erode (29)
/* ns:erode */
struct ns__erode
{
public:
	char *src;	/* optional element of type xsd:string */
	char *element;	/* optional element of type xsd:string */
	int iteration;	/* required element of type xsd:int */
};
#endif

#ifndef SOAP_TYPE_ns__dilateResponse
#define SOAP_TYPE_ns__dilateResponse (31)
/* ns:dilateResponse */
struct ns__dilateResponse
{
public:
	char **OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns__dilate
#define SOAP_TYPE_ns__dilate (32)
/* ns:dilate */
struct ns__dilate
{
public:
	char *src;	/* optional element of type xsd:string */
	char *element;	/* optional element of type xsd:string */
	int iteration;	/* required element of type xsd:int */
};
#endif

#ifndef SOAP_TYPE_ns__OrResponse
#define SOAP_TYPE_ns__OrResponse (34)
/* ns:OrResponse */
struct ns__OrResponse
{
public:
	char **OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns__Or
#define SOAP_TYPE_ns__Or (35)
/* ns:Or */
struct ns__Or
{
public:
	char *src1;	/* optional element of type xsd:string */
	char *src2;	/* optional element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns__removeSmallCell
#define SOAP_TYPE_ns__removeSmallCell (38)
/* ns:removeSmallCell */
struct ns__removeSmallCell
{
public:
	char *inputMatFilename;	/* optional element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Header
#define SOAP_TYPE_SOAP_ENV__Header (39)
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
#define SOAP_TYPE_SOAP_ENV__Code (40)
/* SOAP Fault Code: */
struct SOAP_ENV__Code
{
public:
	char *SOAP_ENV__Value;	/* optional element of type xsd:QName */
	struct SOAP_ENV__Code *SOAP_ENV__Subcode;	/* optional element of type SOAP-ENV:Code */
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Detail
#define SOAP_TYPE_SOAP_ENV__Detail (42)
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
#define SOAP_TYPE_SOAP_ENV__Reason (45)
/* SOAP-ENV:Reason */
struct SOAP_ENV__Reason
{
public:
	char *SOAP_ENV__Text;	/* optional element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Fault
#define SOAP_TYPE_SOAP_ENV__Fault (46)
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


SOAP_FMAC5 int SOAP_FMAC6 ns__loadMat(struct soap*, char *InputImageFilename, int loadparam, char *&OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__binaryThreshold(struct soap*, char *InputMatFilename, double thresholdValue, double maxValue, char *&OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__morphOpen(struct soap*, char *InpuMattFilename, char *&OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__MatToJPG(struct soap*, char *InputMatFilename, char *&OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__findContoursAndFillpoly(struct soap*, char *InputMatFilename, int lowerBound, ns__FindContours &out);

SOAP_FMAC5 int SOAP_FMAC6 ns__erode(struct soap*, char *src, char *element, int iteration, char **OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__dilate(struct soap*, char *src, char *element, int iteration, char **OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__Or(struct soap*, char *src1, char *src2, char **OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__removeSmallCell(struct soap*, char *inputMatFilename, ns__RemoveSmallCell &out);

/******************************************************************************\
 *                                                                            *
 * Server-Side Skeletons to Invoke Service Operations                         *
 *                                                                            *
\******************************************************************************/

SOAP_FMAC5 int SOAP_FMAC6 soap_serve(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_request(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__loadMat(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__binaryThreshold(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__morphOpen(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__MatToJPG(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__findContoursAndFillpoly(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__erode(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__dilate(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__Or(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__removeSmallCell(struct soap*);

/******************************************************************************\
 *                                                                            *
 * Client-Side Call Stubs                                                     *
 *                                                                            *
\******************************************************************************/


SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__loadMat(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *InputImageFilename, int loadparam, char *&OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__binaryThreshold(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *InputMatFilename, double thresholdValue, double maxValue, char *&OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__morphOpen(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *InpuMattFilename, char *&OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__MatToJPG(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *InputMatFilename, char *&OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__findContoursAndFillpoly(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *InputMatFilename, int lowerBound, ns__FindContours &out);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__erode(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *src, char *element, int iteration, char **OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__dilate(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *src, char *element, int iteration, char **OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__Or(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *src1, char *src2, char **OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__removeSmallCell(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *inputMatFilename, ns__RemoveSmallCell &out);

#endif

/* End of soapStub.h */
