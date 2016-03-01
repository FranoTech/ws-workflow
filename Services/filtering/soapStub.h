/* soapStub.h
   Generated by gSOAP 2.8.14 from ImageFiltering.h

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

#ifndef SOAP_TYPE_ns__blurResponse
#define SOAP_TYPE_ns__blurResponse (10)
/* ns:blurResponse */
struct ns__blurResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
public:
	int soap_type() const { return 10; } /* = unique id SOAP_TYPE_ns__blurResponse */
};
#endif

#ifndef SOAP_TYPE_ns__blur
#define SOAP_TYPE_ns__blur (11)
/* ns:blur */
struct ns__blur
{
public:
	std::string InputMatFilename;	/* required element of type xsd:string */
	int kernelRows;	/* required element of type xsd:int */
	int kernelCols;	/* required element of type xsd:int */
	int anchorX_D;	/* required element of type xsd:int */
	int anchorY_D;	/* required element of type xsd:int */
	std::string borderType_D;	/* required element of type xsd:string */
public:
	int soap_type() const { return 11; } /* = unique id SOAP_TYPE_ns__blur */
};
#endif

#ifndef SOAP_TYPE_ns__GaussianBlurResponse
#define SOAP_TYPE_ns__GaussianBlurResponse (14)
/* ns:GaussianBlurResponse */
struct ns__GaussianBlurResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
public:
	int soap_type() const { return 14; } /* = unique id SOAP_TYPE_ns__GaussianBlurResponse */
};
#endif

#ifndef SOAP_TYPE_ns__GaussianBlur
#define SOAP_TYPE_ns__GaussianBlur (15)
/* ns:GaussianBlur */
struct ns__GaussianBlur
{
public:
	std::string InputMatFilename;	/* required element of type xsd:string */
	int kernelRows;	/* required element of type xsd:int */
	int kernelCols;	/* required element of type xsd:int */
	double sigmaX;	/* required element of type xsd:double */
	double sigmaY_D;	/* required element of type xsd:double */
	std::string borderType_D;	/* required element of type xsd:string */
public:
	int soap_type() const { return 15; } /* = unique id SOAP_TYPE_ns__GaussianBlur */
};
#endif

#ifndef SOAP_TYPE_ns__erodeResponse
#define SOAP_TYPE_ns__erodeResponse (17)
/* ns:erodeResponse */
struct ns__erodeResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
public:
	int soap_type() const { return 17; } /* = unique id SOAP_TYPE_ns__erodeResponse */
};
#endif

#ifndef SOAP_TYPE_ns__erode
#define SOAP_TYPE_ns__erode (18)
/* ns:erode */
struct ns__erode
{
public:
	std::string InputMatFilename;	/* required element of type xsd:string */
	std::string StructuringElementFilename;	/* required element of type xsd:string */
	int iteration_;	/* required element of type xsd:int */
	int anchorX_D;	/* required element of type xsd:int */
	int anchorY_D;	/* required element of type xsd:int */
	std::string borderType_D;	/* required element of type xsd:string */
public:
	int soap_type() const { return 18; } /* = unique id SOAP_TYPE_ns__erode */
};
#endif

#ifndef SOAP_TYPE_ns__dilateResponse
#define SOAP_TYPE_ns__dilateResponse (20)
/* ns:dilateResponse */
struct ns__dilateResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
public:
	int soap_type() const { return 20; } /* = unique id SOAP_TYPE_ns__dilateResponse */
};
#endif

#ifndef SOAP_TYPE_ns__dilate
#define SOAP_TYPE_ns__dilate (21)
/* ns:dilate */
struct ns__dilate
{
public:
	std::string InputMatFilename;	/* required element of type xsd:string */
	std::string StructuringElementFilename;	/* required element of type xsd:string */
	int iteration_;	/* required element of type xsd:int */
	int anchorX_D;	/* required element of type xsd:int */
	int anchorY_D;	/* required element of type xsd:int */
	std::string borderType_D;	/* required element of type xsd:string */
public:
	int soap_type() const { return 21; } /* = unique id SOAP_TYPE_ns__dilate */
};
#endif

#ifndef SOAP_TYPE_ns__filter2DResponse
#define SOAP_TYPE_ns__filter2DResponse (23)
/* ns:filter2DResponse */
struct ns__filter2DResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
public:
	int soap_type() const { return 23; } /* = unique id SOAP_TYPE_ns__filter2DResponse */
};
#endif

#ifndef SOAP_TYPE_ns__filter2D
#define SOAP_TYPE_ns__filter2D (24)
/* ns:filter2D */
struct ns__filter2D
{
public:
	std::string InputMatFilename;	/* required element of type xsd:string */
	int ddepth;	/* required element of type xsd:int */
	std::string kernelFname;	/* required element of type xsd:string */
	int anchorX_D;	/* required element of type xsd:int */
	int anchorY_D;	/* required element of type xsd:int */
	double delta_D;	/* required element of type xsd:double */
	std::string borderType_D;	/* required element of type xsd:string */
public:
	int soap_type() const { return 24; } /* = unique id SOAP_TYPE_ns__filter2D */
};
#endif

#ifndef SOAP_TYPE_ns__getStructuringElementResponse
#define SOAP_TYPE_ns__getStructuringElementResponse (26)
/* ns:getStructuringElementResponse */
struct ns__getStructuringElementResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
public:
	int soap_type() const { return 26; } /* = unique id SOAP_TYPE_ns__getStructuringElementResponse */
};
#endif

#ifndef SOAP_TYPE_ns__getStructuringElement
#define SOAP_TYPE_ns__getStructuringElement (27)
/* ns:getStructuringElement */
struct ns__getStructuringElement
{
public:
	std::string StructuringShape;	/* required element of type xsd:string */
	int seSizeW;	/* required element of type xsd:int */
	int seSizeH;	/* required element of type xsd:int */
	int anchorX_D;	/* required element of type xsd:int */
	int anchorY_D;	/* required element of type xsd:int */
public:
	int soap_type() const { return 27; } /* = unique id SOAP_TYPE_ns__getStructuringElement */
};
#endif

#ifndef SOAP_TYPE_ns__medianBlurResponse
#define SOAP_TYPE_ns__medianBlurResponse (29)
/* ns:medianBlurResponse */
struct ns__medianBlurResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
public:
	int soap_type() const { return 29; } /* = unique id SOAP_TYPE_ns__medianBlurResponse */
};
#endif

#ifndef SOAP_TYPE_ns__medianBlur
#define SOAP_TYPE_ns__medianBlur (30)
/* ns:medianBlur */
struct ns__medianBlur
{
public:
	std::string InputMatFilename;	/* required element of type xsd:string */
	int kSize_D;	/* required element of type xsd:int */
public:
	int soap_type() const { return 30; } /* = unique id SOAP_TYPE_ns__medianBlur */
};
#endif

#ifndef SOAP_TYPE_ns__MorphologyExResponse
#define SOAP_TYPE_ns__MorphologyExResponse (32)
/* ns:MorphologyExResponse */
struct ns__MorphologyExResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
public:
	int soap_type() const { return 32; } /* = unique id SOAP_TYPE_ns__MorphologyExResponse */
};
#endif

#ifndef SOAP_TYPE_ns__MorphologyEx
#define SOAP_TYPE_ns__MorphologyEx (33)
/* ns:MorphologyEx */
struct ns__MorphologyEx
{
public:
	std::string InputMatFilename;	/* required element of type xsd:string */
	std::string morphOperation;	/* required element of type xsd:string */
	std::string StructuringElementFname;	/* required element of type xsd:string */
	int iteration_D;	/* required element of type xsd:int */
	int anchorX_D;	/* required element of type xsd:int */
	int anchorY_D;	/* required element of type xsd:int */
public:
	int soap_type() const { return 33; } /* = unique id SOAP_TYPE_ns__MorphologyEx */
};
#endif

#ifndef SOAP_TYPE_ns__LaplacianResponse
#define SOAP_TYPE_ns__LaplacianResponse (35)
/* ns:LaplacianResponse */
struct ns__LaplacianResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
public:
	int soap_type() const { return 35; } /* = unique id SOAP_TYPE_ns__LaplacianResponse */
};
#endif

#ifndef SOAP_TYPE_ns__Laplacian
#define SOAP_TYPE_ns__Laplacian (36)
/* ns:Laplacian */
struct ns__Laplacian
{
public:
	std::string InputMatFilename;	/* required element of type xsd:string */
	std::string ddepth;	/* required element of type xsd:string */
	int ksize_D;	/* required element of type xsd:int */
	double scale_D;	/* required element of type xsd:double */
	double delta_D;	/* required element of type xsd:double */
	std::string borderType_D;	/* required element of type xsd:string */
public:
	int soap_type() const { return 36; } /* = unique id SOAP_TYPE_ns__Laplacian */
};
#endif

#ifndef SOAP_TYPE_ns__pyrDownResponse
#define SOAP_TYPE_ns__pyrDownResponse (38)
/* ns:pyrDownResponse */
struct ns__pyrDownResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
public:
	int soap_type() const { return 38; } /* = unique id SOAP_TYPE_ns__pyrDownResponse */
};
#endif

#ifndef SOAP_TYPE_ns__pyrDown
#define SOAP_TYPE_ns__pyrDown (39)
/* ns:pyrDown */
struct ns__pyrDown
{
public:
	std::string InputMatFilename;	/* required element of type xsd:string */
	int rows;	/* required element of type xsd:int */
	int cols;	/* required element of type xsd:int */
	std::string borderType_D;	/* required element of type xsd:string */
public:
	int soap_type() const { return 39; } /* = unique id SOAP_TYPE_ns__pyrDown */
};
#endif

#ifndef SOAP_TYPE_ns__pyrUpResponse
#define SOAP_TYPE_ns__pyrUpResponse (41)
/* ns:pyrUpResponse */
struct ns__pyrUpResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
public:
	int soap_type() const { return 41; } /* = unique id SOAP_TYPE_ns__pyrUpResponse */
};
#endif

#ifndef SOAP_TYPE_ns__pyrUp
#define SOAP_TYPE_ns__pyrUp (42)
/* ns:pyrUp */
struct ns__pyrUp
{
public:
	std::string InputMatFilename;	/* required element of type xsd:string */
	int rows;	/* required element of type xsd:int */
	int cols;	/* required element of type xsd:int */
	std::string borderType_D;	/* required element of type xsd:string */
public:
	int soap_type() const { return 42; } /* = unique id SOAP_TYPE_ns__pyrUp */
};
#endif

#ifndef SOAP_TYPE_ns__SobelResponse
#define SOAP_TYPE_ns__SobelResponse (44)
/* ns:SobelResponse */
struct ns__SobelResponse
{
public:
	std::string OutputMatFilename;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
public:
	int soap_type() const { return 44; } /* = unique id SOAP_TYPE_ns__SobelResponse */
};
#endif

#ifndef SOAP_TYPE_ns__Sobel
#define SOAP_TYPE_ns__Sobel (45)
/* ns:Sobel */
struct ns__Sobel
{
public:
	std::string InputMatFilename;	/* required element of type xsd:string */
	std::string ddepth;	/* required element of type xsd:string */
	int kSize_D;	/* required element of type xsd:int */
	double scale_D;	/* required element of type xsd:double */
	double delta_D;	/* required element of type xsd:double */
	int dx;	/* required element of type xsd:int */
	int dy;	/* required element of type xsd:int */
	std::string borderType_D;	/* required element of type xsd:string */
public:
	int soap_type() const { return 45; } /* = unique id SOAP_TYPE_ns__Sobel */
};
#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Header
#define SOAP_TYPE_SOAP_ENV__Header (46)
/* SOAP Header: */
struct SOAP_ENV__Header
{
public:
	int soap_type() const { return 46; } /* = unique id SOAP_TYPE_SOAP_ENV__Header */
#ifdef WITH_NOEMPTYSTRUCT
private:
	char dummy;	/* dummy member to enable compilation */
#endif
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Code
#define SOAP_TYPE_SOAP_ENV__Code (47)
/* SOAP Fault Code: */
struct SOAP_ENV__Code
{
public:
	char *SOAP_ENV__Value;	/* optional element of type xsd:QName */
	struct SOAP_ENV__Code *SOAP_ENV__Subcode;	/* optional element of type SOAP-ENV:Code */
public:
	int soap_type() const { return 47; } /* = unique id SOAP_TYPE_SOAP_ENV__Code */
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Detail
#define SOAP_TYPE_SOAP_ENV__Detail (49)
/* SOAP-ENV:Detail */
struct SOAP_ENV__Detail
{
public:
	char *__any;
	int __type;	/* any type of element <fault> (defined below) */
	void *fault;	/* transient */
public:
	int soap_type() const { return 49; } /* = unique id SOAP_TYPE_SOAP_ENV__Detail */
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Reason
#define SOAP_TYPE_SOAP_ENV__Reason (52)
/* SOAP-ENV:Reason */
struct SOAP_ENV__Reason
{
public:
	char *SOAP_ENV__Text;	/* optional element of type xsd:string */
public:
	int soap_type() const { return 52; } /* = unique id SOAP_TYPE_SOAP_ENV__Reason */
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Fault
#define SOAP_TYPE_SOAP_ENV__Fault (53)
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
	int soap_type() const { return 53; } /* = unique id SOAP_TYPE_SOAP_ENV__Fault */
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


SOAP_FMAC5 int SOAP_FMAC6 ns__blur(struct soap*, std::string InputMatFilename, int kernelRows, int kernelCols, int anchorX_D, int anchorY_D, std::string borderType_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__GaussianBlur(struct soap*, std::string InputMatFilename, int kernelRows, int kernelCols, double sigmaX, double sigmaY_D, std::string borderType_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__erode(struct soap*, std::string InputMatFilename, std::string StructuringElementFilename, int iteration_, int anchorX_D, int anchorY_D, std::string borderType_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__dilate(struct soap*, std::string InputMatFilename, std::string StructuringElementFilename, int iteration_, int anchorX_D, int anchorY_D, std::string borderType_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__filter2D(struct soap*, std::string InputMatFilename, int ddepth, std::string kernelFname, int anchorX_D, int anchorY_D, double delta_D, std::string borderType_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__getStructuringElement(struct soap*, std::string StructuringShape, int seSizeW, int seSizeH, int anchorX_D, int anchorY_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__medianBlur(struct soap*, std::string InputMatFilename, int kSize_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__MorphologyEx(struct soap*, std::string InputMatFilename, std::string morphOperation, std::string StructuringElementFname, int iteration_D, int anchorX_D, int anchorY_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__Laplacian(struct soap*, std::string InputMatFilename, std::string ddepth, int ksize_D, double scale_D, double delta_D, std::string borderType_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__pyrDown(struct soap*, std::string InputMatFilename, int rows, int cols, std::string borderType_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__pyrUp(struct soap*, std::string InputMatFilename, int rows, int cols, std::string borderType_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 ns__Sobel(struct soap*, std::string InputMatFilename, std::string ddepth, int kSize_D, double scale_D, double delta_D, int dx, int dy, std::string borderType_D, std::string &OutputMatFilename);

/******************************************************************************\
 *                                                                            *
 * Server-Side Skeletons to Invoke Service Operations                         *
 *                                                                            *
\******************************************************************************/

extern "C" SOAP_FMAC5 int SOAP_FMAC6 soap_serve(struct soap*);

extern "C" SOAP_FMAC5 int SOAP_FMAC6 soap_serve_request(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__blur(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__GaussianBlur(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__erode(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__dilate(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__filter2D(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__getStructuringElement(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__medianBlur(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__MorphologyEx(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__Laplacian(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__pyrDown(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__pyrUp(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__Sobel(struct soap*);

/******************************************************************************\
 *                                                                            *
 * Client-Side Call Stubs                                                     *
 *                                                                            *
\******************************************************************************/


SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__blur(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, int kernelRows, int kernelCols, int anchorX_D, int anchorY_D, std::string borderType_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__GaussianBlur(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, int kernelRows, int kernelCols, double sigmaX, double sigmaY_D, std::string borderType_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__erode(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, std::string StructuringElementFilename, int iteration_, int anchorX_D, int anchorY_D, std::string borderType_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__dilate(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, std::string StructuringElementFilename, int iteration_, int anchorX_D, int anchorY_D, std::string borderType_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__filter2D(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, int ddepth, std::string kernelFname, int anchorX_D, int anchorY_D, double delta_D, std::string borderType_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__getStructuringElement(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string StructuringShape, int seSizeW, int seSizeH, int anchorX_D, int anchorY_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__medianBlur(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, int kSize_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__MorphologyEx(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, std::string morphOperation, std::string StructuringElementFname, int iteration_D, int anchorX_D, int anchorY_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__Laplacian(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, std::string ddepth, int ksize_D, double scale_D, double delta_D, std::string borderType_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__pyrDown(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, int rows, int cols, std::string borderType_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__pyrUp(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, int rows, int cols, std::string borderType_D, std::string &OutputMatFilename);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__Sobel(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, std::string ddepth, int kSize_D, double scale_D, double delta_D, int dx, int dy, std::string borderType_D, std::string &OutputMatFilename);

#endif

/* End of soapStub.h */