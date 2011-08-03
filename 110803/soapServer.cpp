/* soapServer.cpp
   Generated by gSOAP 2.8.2 from imgProcess.h
   Copyright(C) 2000-2011, Robert van Engelen, Genivia Inc. All Rights Reserved.
   The generated code is released under one of the following licenses:
   GPL OR Genivia's license for commercial use.
*/

#if defined(__BORLANDC__)
#pragma option push -w-8060
#pragma option push -w-8004
#endif
#include "soapH.h"

SOAP_SOURCE_STAMP("@(#) soapServer.cpp ver 2.8.2 2011-08-03 08:08:50 GMT")


SOAP_FMAC5 int SOAP_FMAC6 soap_serve(struct soap *soap)
{
#ifndef WITH_FASTCGI
	unsigned int k = soap->max_keep_alive;
#endif
	do
	{
#ifndef WITH_FASTCGI
		if (soap->max_keep_alive > 0 && !--k)
			soap->keep_alive = 0;
#endif
		if (soap_begin_serve(soap))
		{	if (soap->error >= SOAP_STOP)
				continue;
			return soap->error;
		}
		if (soap_serve_request(soap) || (soap->fserveloop && soap->fserveloop(soap)))
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
	if (!soap_match_tag(soap, soap->tag, "ns:getImage"))
		return soap_serve_ns__getImage(soap);
	if (!soap_match_tag(soap, soap->tag, "ns:Ipl1ChToMat"))
		return soap_serve_ns__Ipl1ChToMat(soap);
	if (!soap_match_tag(soap, soap->tag, "ns:MatToJPG"))
		return soap_serve_ns__MatToJPG(soap);
	if (!soap_match_tag(soap, soap->tag, "ns:BinaryThreshold"))
		return soap_serve_ns__BinaryThreshold(soap);
	if (!soap_match_tag(soap, soap->tag, "ns:MorphOpen"))
		return soap_serve_ns__MorphOpen(soap);
	return soap->error = SOAP_NO_METHOD;
}
#endif

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__getImage(struct soap *soap)
{	struct ns__getImage soap_tmp_ns__getImage;
	struct ns__getImageResponse soap_tmp_ns__getImageResponse;
	soap_default_ns__getImageResponse(soap, &soap_tmp_ns__getImageResponse);
	soap_default_ns__getImage(soap, &soap_tmp_ns__getImage);
	soap->encodingStyle = "";
	if (!soap_get_ns__getImage(soap, &soap_tmp_ns__getImage, "ns:getImage", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns__getImage(soap, soap_tmp_ns__getImage.name, soap_tmp_ns__getImageResponse.image);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns__getImageResponse(soap, &soap_tmp_ns__getImageResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__getImageResponse(soap, &soap_tmp_ns__getImageResponse, "ns:getImageResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__getImageResponse(soap, &soap_tmp_ns__getImageResponse, "ns:getImageResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__Ipl1ChToMat(struct soap *soap)
{	struct ns__Ipl1ChToMat soap_tmp_ns__Ipl1ChToMat;
	struct ns__Ipl1ChToMatResponse soap_tmp_ns__Ipl1ChToMatResponse;
	soap_default_ns__Ipl1ChToMatResponse(soap, &soap_tmp_ns__Ipl1ChToMatResponse);
	soap_default_ns__Ipl1ChToMat(soap, &soap_tmp_ns__Ipl1ChToMat);
	soap->encodingStyle = "";
	if (!soap_get_ns__Ipl1ChToMat(soap, &soap_tmp_ns__Ipl1ChToMat, "ns:Ipl1ChToMat", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns__Ipl1ChToMat(soap, soap_tmp_ns__Ipl1ChToMat.InputFilename, soap_tmp_ns__Ipl1ChToMatResponse.OutputFilename);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns__Ipl1ChToMatResponse(soap, &soap_tmp_ns__Ipl1ChToMatResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__Ipl1ChToMatResponse(soap, &soap_tmp_ns__Ipl1ChToMatResponse, "ns:Ipl1ChToMatResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__Ipl1ChToMatResponse(soap, &soap_tmp_ns__Ipl1ChToMatResponse, "ns:Ipl1ChToMatResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__MatToJPG(struct soap *soap)
{	struct ns__MatToJPG soap_tmp_ns__MatToJPG;
	struct ns__MatToJPGResponse soap_tmp_ns__MatToJPGResponse;
	soap_default_ns__MatToJPGResponse(soap, &soap_tmp_ns__MatToJPGResponse);
	soap_default_ns__MatToJPG(soap, &soap_tmp_ns__MatToJPG);
	soap->encodingStyle = "";
	if (!soap_get_ns__MatToJPG(soap, &soap_tmp_ns__MatToJPG, "ns:MatToJPG", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns__MatToJPG(soap, soap_tmp_ns__MatToJPG.InputFilename, soap_tmp_ns__MatToJPGResponse.OutputFilename);
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

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__BinaryThreshold(struct soap *soap)
{	struct ns__BinaryThreshold soap_tmp_ns__BinaryThreshold;
	struct ns__BinaryThresholdResponse soap_tmp_ns__BinaryThresholdResponse;
	soap_default_ns__BinaryThresholdResponse(soap, &soap_tmp_ns__BinaryThresholdResponse);
	soap_default_ns__BinaryThreshold(soap, &soap_tmp_ns__BinaryThreshold);
	soap->encodingStyle = "";
	if (!soap_get_ns__BinaryThreshold(soap, &soap_tmp_ns__BinaryThreshold, "ns:BinaryThreshold", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns__BinaryThreshold(soap, soap_tmp_ns__BinaryThreshold.InputFilename, soap_tmp_ns__BinaryThreshold.threshold, soap_tmp_ns__BinaryThreshold.maxValue, soap_tmp_ns__BinaryThresholdResponse.OutputFilename);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns__BinaryThresholdResponse(soap, &soap_tmp_ns__BinaryThresholdResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__BinaryThresholdResponse(soap, &soap_tmp_ns__BinaryThresholdResponse, "ns:BinaryThresholdResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__BinaryThresholdResponse(soap, &soap_tmp_ns__BinaryThresholdResponse, "ns:BinaryThresholdResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__MorphOpen(struct soap *soap)
{	struct ns__MorphOpen soap_tmp_ns__MorphOpen;
	struct ns__MorphOpenResponse soap_tmp_ns__MorphOpenResponse;
	soap_default_ns__MorphOpenResponse(soap, &soap_tmp_ns__MorphOpenResponse);
	soap_default_ns__MorphOpen(soap, &soap_tmp_ns__MorphOpen);
	soap->encodingStyle = "";
	if (!soap_get_ns__MorphOpen(soap, &soap_tmp_ns__MorphOpen, "ns:MorphOpen", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns__MorphOpen(soap, soap_tmp_ns__MorphOpen.InputFilename, soap_tmp_ns__MorphOpenResponse.OutputFilename);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns__MorphOpenResponse(soap, &soap_tmp_ns__MorphOpenResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__MorphOpenResponse(soap, &soap_tmp_ns__MorphOpenResponse, "ns:MorphOpenResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__MorphOpenResponse(soap, &soap_tmp_ns__MorphOpenResponse, "ns:MorphOpenResponse", NULL)
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
