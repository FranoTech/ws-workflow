/* soapClient.cpp
   Generated by gSOAP 2.8.14 from ImageFiltering.h

Copyright(C) 2000-2013, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under ONE of the following licenses:
GPL or Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#if defined(__BORLANDC__)
#pragma option push -w-8060
#pragma option push -w-8004
#endif
#include "soapH.h"

SOAP_SOURCE_STAMP("@(#) soapClient.cpp ver 2.8.14 2013-03-16 17:39:20 GMT")


SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__blur(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, int kernelRows, int kernelCols, int anchorX_D, int anchorY_D, std::string borderType_D, std::string &OutputMatFilename)
{	struct ns__blur soap_tmp_ns__blur;
	struct ns__blurResponse *soap_tmp_ns__blurResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/ImageFilteringServer";
	soap->encodingStyle = "";
	soap_tmp_ns__blur.InputMatFilename = InputMatFilename;
	soap_tmp_ns__blur.kernelRows = kernelRows;
	soap_tmp_ns__blur.kernelCols = kernelCols;
	soap_tmp_ns__blur.anchorX_D = anchorX_D;
	soap_tmp_ns__blur.anchorY_D = anchorY_D;
	soap_tmp_ns__blur.borderType_D = borderType_D;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__blur(soap, &soap_tmp_ns__blur);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__blur(soap, &soap_tmp_ns__blur, "ns:blur", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__blur(soap, &soap_tmp_ns__blur, "ns:blur", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&OutputMatFilename)
		return soap_closesock(soap);
	soap_default_std__string(soap, &OutputMatFilename);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns__blurResponse = soap_get_ns__blurResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__blurResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__GaussianBlur(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, int kernelRows, int kernelCols, double sigmaX, double sigmaY_D, std::string borderType_D, std::string &OutputMatFilename)
{	struct ns__GaussianBlur soap_tmp_ns__GaussianBlur;
	struct ns__GaussianBlurResponse *soap_tmp_ns__GaussianBlurResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/ImageFilteringServer";
	soap->encodingStyle = "";
	soap_tmp_ns__GaussianBlur.InputMatFilename = InputMatFilename;
	soap_tmp_ns__GaussianBlur.kernelRows = kernelRows;
	soap_tmp_ns__GaussianBlur.kernelCols = kernelCols;
	soap_tmp_ns__GaussianBlur.sigmaX = sigmaX;
	soap_tmp_ns__GaussianBlur.sigmaY_D = sigmaY_D;
	soap_tmp_ns__GaussianBlur.borderType_D = borderType_D;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__GaussianBlur(soap, &soap_tmp_ns__GaussianBlur);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__GaussianBlur(soap, &soap_tmp_ns__GaussianBlur, "ns:GaussianBlur", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__GaussianBlur(soap, &soap_tmp_ns__GaussianBlur, "ns:GaussianBlur", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&OutputMatFilename)
		return soap_closesock(soap);
	soap_default_std__string(soap, &OutputMatFilename);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns__GaussianBlurResponse = soap_get_ns__GaussianBlurResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__GaussianBlurResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__erode(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, std::string StructuringElementFilename, int iteration_, int anchorX_D, int anchorY_D, std::string borderType_D, std::string &OutputMatFilename)
{	struct ns__erode soap_tmp_ns__erode;
	struct ns__erodeResponse *soap_tmp_ns__erodeResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/ImageFilteringServer";
	soap->encodingStyle = "";
	soap_tmp_ns__erode.InputMatFilename = InputMatFilename;
	soap_tmp_ns__erode.StructuringElementFilename = StructuringElementFilename;
	soap_tmp_ns__erode.iteration_ = iteration_;
	soap_tmp_ns__erode.anchorX_D = anchorX_D;
	soap_tmp_ns__erode.anchorY_D = anchorY_D;
	soap_tmp_ns__erode.borderType_D = borderType_D;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__erode(soap, &soap_tmp_ns__erode);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__erode(soap, &soap_tmp_ns__erode, "ns:erode", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__erode(soap, &soap_tmp_ns__erode, "ns:erode", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&OutputMatFilename)
		return soap_closesock(soap);
	soap_default_std__string(soap, &OutputMatFilename);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns__erodeResponse = soap_get_ns__erodeResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__erodeResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__dilate(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, std::string StructuringElementFilename, int iteration_, int anchorX_D, int anchorY_D, std::string borderType_D, std::string &OutputMatFilename)
{	struct ns__dilate soap_tmp_ns__dilate;
	struct ns__dilateResponse *soap_tmp_ns__dilateResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/ImageFilteringServer";
	soap->encodingStyle = "";
	soap_tmp_ns__dilate.InputMatFilename = InputMatFilename;
	soap_tmp_ns__dilate.StructuringElementFilename = StructuringElementFilename;
	soap_tmp_ns__dilate.iteration_ = iteration_;
	soap_tmp_ns__dilate.anchorX_D = anchorX_D;
	soap_tmp_ns__dilate.anchorY_D = anchorY_D;
	soap_tmp_ns__dilate.borderType_D = borderType_D;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__dilate(soap, &soap_tmp_ns__dilate);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__dilate(soap, &soap_tmp_ns__dilate, "ns:dilate", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__dilate(soap, &soap_tmp_ns__dilate, "ns:dilate", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&OutputMatFilename)
		return soap_closesock(soap);
	soap_default_std__string(soap, &OutputMatFilename);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns__dilateResponse = soap_get_ns__dilateResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__dilateResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__filter2D(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, int ddepth, std::string kernelFname, int anchorX_D, int anchorY_D, double delta_D, std::string borderType_D, std::string &OutputMatFilename)
{	struct ns__filter2D soap_tmp_ns__filter2D;
	struct ns__filter2DResponse *soap_tmp_ns__filter2DResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/ImageFilteringServer";
	soap->encodingStyle = "";
	soap_tmp_ns__filter2D.InputMatFilename = InputMatFilename;
	soap_tmp_ns__filter2D.ddepth = ddepth;
	soap_tmp_ns__filter2D.kernelFname = kernelFname;
	soap_tmp_ns__filter2D.anchorX_D = anchorX_D;
	soap_tmp_ns__filter2D.anchorY_D = anchorY_D;
	soap_tmp_ns__filter2D.delta_D = delta_D;
	soap_tmp_ns__filter2D.borderType_D = borderType_D;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__filter2D(soap, &soap_tmp_ns__filter2D);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__filter2D(soap, &soap_tmp_ns__filter2D, "ns:filter2D", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__filter2D(soap, &soap_tmp_ns__filter2D, "ns:filter2D", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&OutputMatFilename)
		return soap_closesock(soap);
	soap_default_std__string(soap, &OutputMatFilename);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns__filter2DResponse = soap_get_ns__filter2DResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__filter2DResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__getStructuringElement(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string StructuringShape, int seSizeW, int seSizeH, int anchorX_D, int anchorY_D, std::string &OutputMatFilename)
{	struct ns__getStructuringElement soap_tmp_ns__getStructuringElement;
	struct ns__getStructuringElementResponse *soap_tmp_ns__getStructuringElementResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/ImageFilteringServer";
	soap->encodingStyle = "";
	soap_tmp_ns__getStructuringElement.StructuringShape = StructuringShape;
	soap_tmp_ns__getStructuringElement.seSizeW = seSizeW;
	soap_tmp_ns__getStructuringElement.seSizeH = seSizeH;
	soap_tmp_ns__getStructuringElement.anchorX_D = anchorX_D;
	soap_tmp_ns__getStructuringElement.anchorY_D = anchorY_D;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__getStructuringElement(soap, &soap_tmp_ns__getStructuringElement);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__getStructuringElement(soap, &soap_tmp_ns__getStructuringElement, "ns:getStructuringElement", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__getStructuringElement(soap, &soap_tmp_ns__getStructuringElement, "ns:getStructuringElement", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&OutputMatFilename)
		return soap_closesock(soap);
	soap_default_std__string(soap, &OutputMatFilename);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns__getStructuringElementResponse = soap_get_ns__getStructuringElementResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__getStructuringElementResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__medianBlur(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, int kSize_D, std::string &OutputMatFilename)
{	struct ns__medianBlur soap_tmp_ns__medianBlur;
	struct ns__medianBlurResponse *soap_tmp_ns__medianBlurResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/ImageFilteringServer";
	soap->encodingStyle = "";
	soap_tmp_ns__medianBlur.InputMatFilename = InputMatFilename;
	soap_tmp_ns__medianBlur.kSize_D = kSize_D;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__medianBlur(soap, &soap_tmp_ns__medianBlur);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__medianBlur(soap, &soap_tmp_ns__medianBlur, "ns:medianBlur", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__medianBlur(soap, &soap_tmp_ns__medianBlur, "ns:medianBlur", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&OutputMatFilename)
		return soap_closesock(soap);
	soap_default_std__string(soap, &OutputMatFilename);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns__medianBlurResponse = soap_get_ns__medianBlurResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__medianBlurResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__MorphologyEx(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, std::string morphOperation, std::string StructuringElementFname, int iteration_D, int anchorX_D, int anchorY_D, std::string &OutputMatFilename)
{	struct ns__MorphologyEx soap_tmp_ns__MorphologyEx;
	struct ns__MorphologyExResponse *soap_tmp_ns__MorphologyExResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/ImageFilteringServer";
	soap->encodingStyle = "";
	soap_tmp_ns__MorphologyEx.InputMatFilename = InputMatFilename;
	soap_tmp_ns__MorphologyEx.morphOperation = morphOperation;
	soap_tmp_ns__MorphologyEx.StructuringElementFname = StructuringElementFname;
	soap_tmp_ns__MorphologyEx.iteration_D = iteration_D;
	soap_tmp_ns__MorphologyEx.anchorX_D = anchorX_D;
	soap_tmp_ns__MorphologyEx.anchorY_D = anchorY_D;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__MorphologyEx(soap, &soap_tmp_ns__MorphologyEx);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__MorphologyEx(soap, &soap_tmp_ns__MorphologyEx, "ns:MorphologyEx", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__MorphologyEx(soap, &soap_tmp_ns__MorphologyEx, "ns:MorphologyEx", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&OutputMatFilename)
		return soap_closesock(soap);
	soap_default_std__string(soap, &OutputMatFilename);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns__MorphologyExResponse = soap_get_ns__MorphologyExResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__MorphologyExResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__Laplacian(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, std::string ddepth, int ksize_D, double scale_D, double delta_D, std::string borderType_D, std::string &OutputMatFilename)
{	struct ns__Laplacian soap_tmp_ns__Laplacian;
	struct ns__LaplacianResponse *soap_tmp_ns__LaplacianResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/ImageFilteringServer";
	soap->encodingStyle = "";
	soap_tmp_ns__Laplacian.InputMatFilename = InputMatFilename;
	soap_tmp_ns__Laplacian.ddepth = ddepth;
	soap_tmp_ns__Laplacian.ksize_D = ksize_D;
	soap_tmp_ns__Laplacian.scale_D = scale_D;
	soap_tmp_ns__Laplacian.delta_D = delta_D;
	soap_tmp_ns__Laplacian.borderType_D = borderType_D;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__Laplacian(soap, &soap_tmp_ns__Laplacian);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__Laplacian(soap, &soap_tmp_ns__Laplacian, "ns:Laplacian", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__Laplacian(soap, &soap_tmp_ns__Laplacian, "ns:Laplacian", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&OutputMatFilename)
		return soap_closesock(soap);
	soap_default_std__string(soap, &OutputMatFilename);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns__LaplacianResponse = soap_get_ns__LaplacianResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__LaplacianResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__pyrDown(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, int rows, int cols, std::string borderType_D, std::string &OutputMatFilename)
{	struct ns__pyrDown soap_tmp_ns__pyrDown;
	struct ns__pyrDownResponse *soap_tmp_ns__pyrDownResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/ImageFilteringServer";
	soap->encodingStyle = "";
	soap_tmp_ns__pyrDown.InputMatFilename = InputMatFilename;
	soap_tmp_ns__pyrDown.rows = rows;
	soap_tmp_ns__pyrDown.cols = cols;
	soap_tmp_ns__pyrDown.borderType_D = borderType_D;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__pyrDown(soap, &soap_tmp_ns__pyrDown);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__pyrDown(soap, &soap_tmp_ns__pyrDown, "ns:pyrDown", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__pyrDown(soap, &soap_tmp_ns__pyrDown, "ns:pyrDown", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&OutputMatFilename)
		return soap_closesock(soap);
	soap_default_std__string(soap, &OutputMatFilename);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns__pyrDownResponse = soap_get_ns__pyrDownResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__pyrDownResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__pyrUp(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, int rows, int cols, std::string borderType_D, std::string &OutputMatFilename)
{	struct ns__pyrUp soap_tmp_ns__pyrUp;
	struct ns__pyrUpResponse *soap_tmp_ns__pyrUpResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/ImageFilteringServer";
	soap->encodingStyle = "";
	soap_tmp_ns__pyrUp.InputMatFilename = InputMatFilename;
	soap_tmp_ns__pyrUp.rows = rows;
	soap_tmp_ns__pyrUp.cols = cols;
	soap_tmp_ns__pyrUp.borderType_D = borderType_D;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__pyrUp(soap, &soap_tmp_ns__pyrUp);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__pyrUp(soap, &soap_tmp_ns__pyrUp, "ns:pyrUp", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__pyrUp(soap, &soap_tmp_ns__pyrUp, "ns:pyrUp", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&OutputMatFilename)
		return soap_closesock(soap);
	soap_default_std__string(soap, &OutputMatFilename);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns__pyrUpResponse = soap_get_ns__pyrUpResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__pyrUpResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__Sobel(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, std::string ddepth, int kSize_D, double scale_D, double delta_D, int dx, int dy, std::string borderType_D, std::string &OutputMatFilename)
{	struct ns__Sobel soap_tmp_ns__Sobel;
	struct ns__SobelResponse *soap_tmp_ns__SobelResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/ImageFilteringServer";
	soap->encodingStyle = "";
	soap_tmp_ns__Sobel.InputMatFilename = InputMatFilename;
	soap_tmp_ns__Sobel.ddepth = ddepth;
	soap_tmp_ns__Sobel.kSize_D = kSize_D;
	soap_tmp_ns__Sobel.scale_D = scale_D;
	soap_tmp_ns__Sobel.delta_D = delta_D;
	soap_tmp_ns__Sobel.dx = dx;
	soap_tmp_ns__Sobel.dy = dy;
	soap_tmp_ns__Sobel.borderType_D = borderType_D;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__Sobel(soap, &soap_tmp_ns__Sobel);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__Sobel(soap, &soap_tmp_ns__Sobel, "ns:Sobel", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__Sobel(soap, &soap_tmp_ns__Sobel, "ns:Sobel", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&OutputMatFilename)
		return soap_closesock(soap);
	soap_default_std__string(soap, &OutputMatFilename);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns__SobelResponse = soap_get_ns__SobelResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__SobelResponse->OutputMatFilename;
	return soap_closesock(soap);
}

#if defined(__BORLANDC__)
#pragma option pop
#pragma option pop
#endif

/* End of soapClient.cpp */