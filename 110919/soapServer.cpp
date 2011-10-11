/* soapServer.cpp
   Generated by gSOAP 2.7.17 from imgProcess.h
   Copyright(C) 2000-2010, Robert van Engelen, Genivia Inc. All Rights Reserved.
   This part of the software is released under one of the following licenses:
   GPL, the gSOAP public license, or Genivia's license for commercial use.
*/

#if defined(__BORLANDC__)
#pragma option push -w-8060
#pragma option push -w-8004
#endif
#include "soapH.h"

SOAP_SOURCE_STAMP("@(#) soapServer.cpp ver 2.7.17 2011-10-11 06:50:36 GMT")


SOAP_FMAC5 int SOAP_FMAC6 soap_serve(struct soap *soap)
{
#ifndef WITH_FASTCGI
	unsigned int k = soap->max_keep_alive;
#endif

	do
	{
#ifdef WITH_FASTCGI
		if (FCGI_Accept() < 0)
		{
			soap->error = SOAP_EOF;
			return soap_send_fault(soap);
		}
#endif

		soap_begin(soap);

#ifndef WITH_FASTCGI
		if (soap->max_keep_alive > 0 && !--k)
			soap->keep_alive = 0;
#endif

		if (soap_begin_recv(soap))
		{	if (soap->error < SOAP_STOP)
			{
#ifdef WITH_FASTCGI
				soap_send_fault(soap);
#else 
				return soap_send_fault(soap);
#endif
			}
			soap_closesock(soap);

			continue;
		}

		if (soap_envelope_begin_in(soap)
		 || soap_recv_header(soap)
		 || soap_body_begin_in(soap)
		 || soap_serve_request(soap)
		 || (soap->fserveloop && soap->fserveloop(soap)))
		{
#ifdef WITH_FASTCGI
			soap_send_fault(soap);
#else
			return soap_send_fault(soap);
#endif
		}

#ifdef WITH_FASTCGI
		soap_destroy(soap);
		soap_end(soap);
	} while (1);
#else
	} while (soap->keep_alive);
#endif
	return SOAP_OK;
}

#ifndef WITH_NOSERVEREQUEST
SOAP_FMAC5 int SOAP_FMAC6 soap_serve_request(struct soap *soap)
{
	soap_peek_element(soap);
	if (!soap_match_tag(soap, soap->tag, "ns:loadMat"))
		return soap_serve_ns__loadMat(soap);
	if (!soap_match_tag(soap, soap->tag, "ns:binaryThreshold"))
		return soap_serve_ns__binaryThreshold(soap);
	if (!soap_match_tag(soap, soap->tag, "ns:morphOpen"))
		return soap_serve_ns__morphOpen(soap);
	if (!soap_match_tag(soap, soap->tag, "ns:MatToJPG"))
		return soap_serve_ns__MatToJPG(soap);
	if (!soap_match_tag(soap, soap->tag, "ns:findContoursAndFillpoly"))
		return soap_serve_ns__findContoursAndFillpoly(soap);
	if (!soap_match_tag(soap, soap->tag, "ns:erode"))
		return soap_serve_ns__erode(soap);
	if (!soap_match_tag(soap, soap->tag, "ns:dilate"))
		return soap_serve_ns__dilate(soap);
	if (!soap_match_tag(soap, soap->tag, "ns:Or"))
		return soap_serve_ns__Or(soap);
	if (!soap_match_tag(soap, soap->tag, "ns:And"))
		return soap_serve_ns__And(soap);
	if (!soap_match_tag(soap, soap->tag, "ns:Not"))
		return soap_serve_ns__Not(soap);
	if (!soap_match_tag(soap, soap->tag, "ns:removeSmallCell"))
		return soap_serve_ns__removeSmallCell(soap);
	if (!soap_match_tag(soap, soap->tag, "ns:scanningCell"))
		return soap_serve_ns__scanningCell(soap);
	return soap->error = SOAP_NO_METHOD;
}
#endif

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__loadMat(struct soap *soap)
{	struct ns__loadMat soap_tmp_ns__loadMat;
	struct ns__loadMatResponse soap_tmp_ns__loadMatResponse;
	char * soap_tmp_string;
	soap_default_ns__loadMatResponse(soap, &soap_tmp_ns__loadMatResponse);
	soap_tmp_string = NULL;
	soap_tmp_ns__loadMatResponse.OutputMatFilename = &soap_tmp_string;
	soap_default_ns__loadMat(soap, &soap_tmp_ns__loadMat);
	soap->encodingStyle = "";
	if (!soap_get_ns__loadMat(soap, &soap_tmp_ns__loadMat, "ns:loadMat", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns__loadMat(soap, soap_tmp_ns__loadMat.InputImageFilename, soap_tmp_ns__loadMat.loadparam, &soap_tmp_string);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns__loadMatResponse(soap, &soap_tmp_ns__loadMatResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__loadMatResponse(soap, &soap_tmp_ns__loadMatResponse, "ns:loadMatResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__loadMatResponse(soap, &soap_tmp_ns__loadMatResponse, "ns:loadMatResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__binaryThreshold(struct soap *soap)
{	struct ns__binaryThreshold soap_tmp_ns__binaryThreshold;
	struct ns__binaryThresholdResponse soap_tmp_ns__binaryThresholdResponse;
	char * soap_tmp_string;
	soap_default_ns__binaryThresholdResponse(soap, &soap_tmp_ns__binaryThresholdResponse);
	soap_tmp_string = NULL;
	soap_tmp_ns__binaryThresholdResponse.OutputMatFilename = &soap_tmp_string;
	soap_default_ns__binaryThreshold(soap, &soap_tmp_ns__binaryThreshold);
	soap->encodingStyle = "";
	if (!soap_get_ns__binaryThreshold(soap, &soap_tmp_ns__binaryThreshold, "ns:binaryThreshold", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns__binaryThreshold(soap, soap_tmp_ns__binaryThreshold.InputMatFilename, soap_tmp_ns__binaryThreshold.thresholdValue, soap_tmp_ns__binaryThreshold.maxValue, &soap_tmp_string);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns__binaryThresholdResponse(soap, &soap_tmp_ns__binaryThresholdResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__binaryThresholdResponse(soap, &soap_tmp_ns__binaryThresholdResponse, "ns:binaryThresholdResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__binaryThresholdResponse(soap, &soap_tmp_ns__binaryThresholdResponse, "ns:binaryThresholdResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__morphOpen(struct soap *soap)
{	struct ns__morphOpen soap_tmp_ns__morphOpen;
	struct ns__morphOpenResponse soap_tmp_ns__morphOpenResponse;
	char * soap_tmp_string;
	soap_default_ns__morphOpenResponse(soap, &soap_tmp_ns__morphOpenResponse);
	soap_tmp_string = NULL;
	soap_tmp_ns__morphOpenResponse.OutputMatFilename = &soap_tmp_string;
	soap_default_ns__morphOpen(soap, &soap_tmp_ns__morphOpen);
	soap->encodingStyle = "";
	if (!soap_get_ns__morphOpen(soap, &soap_tmp_ns__morphOpen, "ns:morphOpen", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns__morphOpen(soap, soap_tmp_ns__morphOpen.InpuMattFilename, &soap_tmp_string);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns__morphOpenResponse(soap, &soap_tmp_ns__morphOpenResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__morphOpenResponse(soap, &soap_tmp_ns__morphOpenResponse, "ns:morphOpenResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__morphOpenResponse(soap, &soap_tmp_ns__morphOpenResponse, "ns:morphOpenResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__MatToJPG(struct soap *soap)
{	struct ns__MatToJPG soap_tmp_ns__MatToJPG;
	struct ns__MatToJPGResponse soap_tmp_ns__MatToJPGResponse;
	char * soap_tmp_string;
	soap_default_ns__MatToJPGResponse(soap, &soap_tmp_ns__MatToJPGResponse);
	soap_tmp_string = NULL;
	soap_tmp_ns__MatToJPGResponse.OutputMatFilename = &soap_tmp_string;
	soap_default_ns__MatToJPG(soap, &soap_tmp_ns__MatToJPG);
	soap->encodingStyle = "";
	if (!soap_get_ns__MatToJPG(soap, &soap_tmp_ns__MatToJPG, "ns:MatToJPG", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns__MatToJPG(soap, soap_tmp_ns__MatToJPG.InputMatFilename, &soap_tmp_string);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns__MatToJPGResponse(soap, &soap_tmp_ns__MatToJPGResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__MatToJPGResponse(soap, &soap_tmp_ns__MatToJPGResponse, "ns:MatToJPGResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__MatToJPGResponse(soap, &soap_tmp_ns__MatToJPGResponse, "ns:MatToJPGResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__findContoursAndFillpoly(struct soap *soap)
{	struct ns__findContoursAndFillpoly soap_tmp_ns__findContoursAndFillpoly;
	ns__FindContours out;
	out.soap_default(soap);
	soap_default_ns__findContoursAndFillpoly(soap, &soap_tmp_ns__findContoursAndFillpoly);
	soap->encodingStyle = "";
	if (!soap_get_ns__findContoursAndFillpoly(soap, &soap_tmp_ns__findContoursAndFillpoly, "ns:findContoursAndFillpoly", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns__findContoursAndFillpoly(soap, soap_tmp_ns__findContoursAndFillpoly.InputMatFilename, soap_tmp_ns__findContoursAndFillpoly.lowerBound, out);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	out.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || out.soap_put(soap, "ns:FindContours", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || out.soap_put(soap, "ns:FindContours", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__erode(struct soap *soap)
{	struct ns__erode soap_tmp_ns__erode;
	struct ns__erodeResponse soap_tmp_ns__erodeResponse;
	char * soap_tmp_string;
	soap_default_ns__erodeResponse(soap, &soap_tmp_ns__erodeResponse);
	soap_tmp_string = NULL;
	soap_tmp_ns__erodeResponse.OutputMatFilename = &soap_tmp_string;
	soap_default_ns__erode(soap, &soap_tmp_ns__erode);
	soap->encodingStyle = "";
	if (!soap_get_ns__erode(soap, &soap_tmp_ns__erode, "ns:erode", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns__erode(soap, soap_tmp_ns__erode.src, soap_tmp_ns__erode.element, soap_tmp_ns__erode.iteration, &soap_tmp_string);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns__erodeResponse(soap, &soap_tmp_ns__erodeResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__erodeResponse(soap, &soap_tmp_ns__erodeResponse, "ns:erodeResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__erodeResponse(soap, &soap_tmp_ns__erodeResponse, "ns:erodeResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__dilate(struct soap *soap)
{	struct ns__dilate soap_tmp_ns__dilate;
	struct ns__dilateResponse soap_tmp_ns__dilateResponse;
	char * soap_tmp_string;
	soap_default_ns__dilateResponse(soap, &soap_tmp_ns__dilateResponse);
	soap_tmp_string = NULL;
	soap_tmp_ns__dilateResponse.OutputMatFilename = &soap_tmp_string;
	soap_default_ns__dilate(soap, &soap_tmp_ns__dilate);
	soap->encodingStyle = "";
	if (!soap_get_ns__dilate(soap, &soap_tmp_ns__dilate, "ns:dilate", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns__dilate(soap, soap_tmp_ns__dilate.src, soap_tmp_ns__dilate.element, soap_tmp_ns__dilate.iteration, &soap_tmp_string);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns__dilateResponse(soap, &soap_tmp_ns__dilateResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__dilateResponse(soap, &soap_tmp_ns__dilateResponse, "ns:dilateResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__dilateResponse(soap, &soap_tmp_ns__dilateResponse, "ns:dilateResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__Or(struct soap *soap)
{	struct ns__Or soap_tmp_ns__Or;
	struct ns__OrResponse soap_tmp_ns__OrResponse;
	char * soap_tmp_string;
	soap_default_ns__OrResponse(soap, &soap_tmp_ns__OrResponse);
	soap_tmp_string = NULL;
	soap_tmp_ns__OrResponse.OutputMatFilename = &soap_tmp_string;
	soap_default_ns__Or(soap, &soap_tmp_ns__Or);
	soap->encodingStyle = "";
	if (!soap_get_ns__Or(soap, &soap_tmp_ns__Or, "ns:Or", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns__Or(soap, soap_tmp_ns__Or.src1, soap_tmp_ns__Or.src2, &soap_tmp_string);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns__OrResponse(soap, &soap_tmp_ns__OrResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__OrResponse(soap, &soap_tmp_ns__OrResponse, "ns:OrResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__OrResponse(soap, &soap_tmp_ns__OrResponse, "ns:OrResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__And(struct soap *soap)
{	struct ns__And soap_tmp_ns__And;
	struct ns__AndResponse soap_tmp_ns__AndResponse;
	char * soap_tmp_string;
	soap_default_ns__AndResponse(soap, &soap_tmp_ns__AndResponse);
	soap_tmp_string = NULL;
	soap_tmp_ns__AndResponse.OutputMatFilename = &soap_tmp_string;
	soap_default_ns__And(soap, &soap_tmp_ns__And);
	soap->encodingStyle = "";
	if (!soap_get_ns__And(soap, &soap_tmp_ns__And, "ns:And", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns__And(soap, soap_tmp_ns__And.src1, soap_tmp_ns__And.src2, &soap_tmp_string);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns__AndResponse(soap, &soap_tmp_ns__AndResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__AndResponse(soap, &soap_tmp_ns__AndResponse, "ns:AndResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__AndResponse(soap, &soap_tmp_ns__AndResponse, "ns:AndResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__Not(struct soap *soap)
{	struct ns__Not soap_tmp_ns__Not;
	struct ns__NotResponse soap_tmp_ns__NotResponse;
	char * soap_tmp_string;
	soap_default_ns__NotResponse(soap, &soap_tmp_ns__NotResponse);
	soap_tmp_string = NULL;
	soap_tmp_ns__NotResponse.OutputMatFilename = &soap_tmp_string;
	soap_default_ns__Not(soap, &soap_tmp_ns__Not);
	soap->encodingStyle = "";
	if (!soap_get_ns__Not(soap, &soap_tmp_ns__Not, "ns:Not", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns__Not(soap, soap_tmp_ns__Not.src, &soap_tmp_string);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns__NotResponse(soap, &soap_tmp_ns__NotResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__NotResponse(soap, &soap_tmp_ns__NotResponse, "ns:NotResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__NotResponse(soap, &soap_tmp_ns__NotResponse, "ns:NotResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__removeSmallCell(struct soap *soap)
{	struct ns__removeSmallCell soap_tmp_ns__removeSmallCell;
	ns__RemoveSmallCell out;
	out.soap_default(soap);
	soap_default_ns__removeSmallCell(soap, &soap_tmp_ns__removeSmallCell);
	soap->encodingStyle = "";
	if (!soap_get_ns__removeSmallCell(soap, &soap_tmp_ns__removeSmallCell, "ns:removeSmallCell", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns__removeSmallCell(soap, soap_tmp_ns__removeSmallCell.inputMatFilename, out);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	out.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || out.soap_put(soap, "ns:RemoveSmallCell", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || out.soap_put(soap, "ns:RemoveSmallCell", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__scanningCell(struct soap *soap)
{	struct ns__scanningCell soap_tmp_ns__scanningCell;
	struct ns__scanningCellResponse soap_tmp_ns__scanningCellResponse;
	char * soap_tmp_string;
	soap_default_ns__scanningCellResponse(soap, &soap_tmp_ns__scanningCellResponse);
	soap_tmp_string = NULL;
	soap_tmp_ns__scanningCellResponse.outputMatFilename = &soap_tmp_string;
	soap_default_ns__scanningCell(soap, &soap_tmp_ns__scanningCell);
	soap->encodingStyle = "";
	if (!soap_get_ns__scanningCell(soap, &soap_tmp_ns__scanningCell, "ns:scanningCell", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns__scanningCell(soap, soap_tmp_ns__scanningCell.inputMatFilename, &soap_tmp_string);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns__scanningCellResponse(soap, &soap_tmp_ns__scanningCellResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__scanningCellResponse(soap, &soap_tmp_ns__scanningCellResponse, "ns:scanningCellResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__scanningCellResponse(soap, &soap_tmp_ns__scanningCellResponse, "ns:scanningCellResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

#if defined(__BORLANDC__)
#pragma option pop
#pragma option pop
#endif

/* End of soapServer.cpp */
