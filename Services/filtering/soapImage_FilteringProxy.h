/* soapImage_FilteringProxy.h
   Generated by gSOAP 2.8.8 from ImageFiltering.h

Copyright(C) 2000-2012, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
1) GPL or 2) Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#ifndef soapImage_FilteringProxy_H
#define soapImage_FilteringProxy_H
#include "soapH.h"
class Image_Filtering
{   public:
	/// Runtime engine context allocated in constructor
	struct soap *soap;
	/// Endpoint URL of service 'Image_Filtering' (change as needed)
	const char *endpoint;
	/// Constructor allocates soap engine context, sets default endpoint URL, and sets namespace mapping table
	Image_Filtering()
	{ soap = soap_new(); endpoint = "http://localhost/cgi-bin/ImageFilteringServer"; if (soap && !soap->namespaces) { static const struct Namespace namespaces[] = 
{
	{"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
	{"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"ns", "urn:filt", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};
	soap->namespaces = namespaces; } };
	/// Destructor frees deserialized data and soap engine context
	virtual ~Image_Filtering() { if (soap) { soap_destroy(soap); soap_end(soap); soap_free(soap); } };
	/// Invoke 'blur' of service 'Image_Filtering' and return error code (or SOAP_OK)
	virtual int ns__blur(std::string InputMatFilename, int kernelRows, int kernelCols, int anchorX_D, int anchorY_D, std::string borderType_D, std::string &OutputMatFilename) { return soap ? soap_call_ns__blur(soap, endpoint, NULL, InputMatFilename, kernelRows, kernelCols, anchorX_D, anchorY_D, borderType_D, OutputMatFilename) : SOAP_EOM; };
	/// Invoke 'GaussianBlur' of service 'Image_Filtering' and return error code (or SOAP_OK)
	virtual int ns__GaussianBlur(std::string InputMatFilename, int kernelRows, int kernelCols, double sigmaX, double sigmaY_D, std::string borderType_D, std::string &OutputMatFilename) { return soap ? soap_call_ns__GaussianBlur(soap, endpoint, NULL, InputMatFilename, kernelRows, kernelCols, sigmaX, sigmaY_D, borderType_D, OutputMatFilename) : SOAP_EOM; };
	/// Invoke 'erode' of service 'Image_Filtering' and return error code (or SOAP_OK)
	virtual int ns__erode(std::string InputMatFilename, std::string StructuringElementFilename, int iteration_, int anchorX_D, int anchorY_D, std::string borderType_D, std::string &OutputMatFilename) { return soap ? soap_call_ns__erode(soap, endpoint, NULL, InputMatFilename, StructuringElementFilename, iteration_, anchorX_D, anchorY_D, borderType_D, OutputMatFilename) : SOAP_EOM; };
	/// Invoke 'dilate' of service 'Image_Filtering' and return error code (or SOAP_OK)
	virtual int ns__dilate(std::string InputMatFilename, std::string StructuringElementFilename, int iteration_, int anchorX_D, int anchorY_D, std::string borderType_D, std::string &OutputMatFilename) { return soap ? soap_call_ns__dilate(soap, endpoint, NULL, InputMatFilename, StructuringElementFilename, iteration_, anchorX_D, anchorY_D, borderType_D, OutputMatFilename) : SOAP_EOM; };
	/// Invoke 'filter2D' of service 'Image_Filtering' and return error code (or SOAP_OK)
	virtual int ns__filter2D(std::string InputMatFilename, int ddepth, std::string kernelFname, int anchorX_D, int anchorY_D, double delta_D, std::string borderType_D, std::string &OutputMatFilename) { return soap ? soap_call_ns__filter2D(soap, endpoint, NULL, InputMatFilename, ddepth, kernelFname, anchorX_D, anchorY_D, delta_D, borderType_D, OutputMatFilename) : SOAP_EOM; };
	/// Invoke 'getStructuringElement' of service 'Image_Filtering' and return error code (or SOAP_OK)
	virtual int ns__getStructuringElement(std::string StructuringShape, int seSizeW, int seSizeH, int anchorX_D, int anchorY_D, std::string &OutputMatFilename) { return soap ? soap_call_ns__getStructuringElement(soap, endpoint, NULL, StructuringShape, seSizeW, seSizeH, anchorX_D, anchorY_D, OutputMatFilename) : SOAP_EOM; };
	/// Invoke 'medianBlur' of service 'Image_Filtering' and return error code (or SOAP_OK)
	virtual int ns__medianBlur(std::string InputMatFilename, int kSize_D, std::string &OutputMatFilename) { return soap ? soap_call_ns__medianBlur(soap, endpoint, NULL, InputMatFilename, kSize_D, OutputMatFilename) : SOAP_EOM; };
	/// Invoke 'MorphologyEx' of service 'Image_Filtering' and return error code (or SOAP_OK)
	virtual int ns__MorphologyEx(std::string InputMatFilename, std::string morphOperation, std::string StructuringElementFname, int iteration_D, int anchorX_D, int anchorY_D, std::string &OutputMatFilename) { return soap ? soap_call_ns__MorphologyEx(soap, endpoint, NULL, InputMatFilename, morphOperation, StructuringElementFname, iteration_D, anchorX_D, anchorY_D, OutputMatFilename) : SOAP_EOM; };
	/// Invoke 'Laplacian' of service 'Image_Filtering' and return error code (or SOAP_OK)
	virtual int ns__Laplacian(std::string InputMatFilename, std::string ddepth, int ksize_D, double scale_D, double delta_D, std::string borderType_D, std::string &OutputMatFilename) { return soap ? soap_call_ns__Laplacian(soap, endpoint, NULL, InputMatFilename, ddepth, ksize_D, scale_D, delta_D, borderType_D, OutputMatFilename) : SOAP_EOM; };
	/// Invoke 'pyrDown' of service 'Image_Filtering' and return error code (or SOAP_OK)
	virtual int ns__pyrDown(std::string InputMatFilename, int rows, int cols, std::string borderType_D, std::string &OutputMatFilename) { return soap ? soap_call_ns__pyrDown(soap, endpoint, NULL, InputMatFilename, rows, cols, borderType_D, OutputMatFilename) : SOAP_EOM; };
	/// Invoke 'pyrUp' of service 'Image_Filtering' and return error code (or SOAP_OK)
	virtual int ns__pyrUp(std::string InputMatFilename, int rows, int cols, std::string borderType_D, std::string &OutputMatFilename) { return soap ? soap_call_ns__pyrUp(soap, endpoint, NULL, InputMatFilename, rows, cols, borderType_D, OutputMatFilename) : SOAP_EOM; };
	/// Invoke 'Sobel' of service 'Image_Filtering' and return error code (or SOAP_OK)
	virtual int ns__Sobel(std::string InputMatFilename, std::string ddepth, int kSize_D, double scale_D, double delta_D, int dx, int dy, std::string borderType_D, std::string &OutputMatFilename) { return soap ? soap_call_ns__Sobel(soap, endpoint, NULL, InputMatFilename, ddepth, kSize_D, scale_D, delta_D, dx, dy, borderType_D, OutputMatFilename) : SOAP_EOM; };
};
#endif
