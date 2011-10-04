/* soapServer.cpp
   Generated by gSOAP 2.8.2 from name.h
   Copyright(C) 2000-2011, Robert van Engelen, Genivia Inc. All Rights Reserved.
   The generated code is released under one of the following licenses:
   GPL OR Genivia's license for commercial use.
*/

#if defined(__BORLANDC__)
#pragma option push -w-8060
#pragma option push -w-8004
#endif
#include "soapH.h"

SOAP_SOURCE_STAMP("@(#) soapServer.cpp ver 2.8.2 2011-09-19 17:47:00 GMT")


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
	if (!soap_match_tag(soap, soap->tag, "ns:genName"))
		return soap_serve_ns__genName(soap);
	if (!soap_match_tag(soap, soap->tag, "ns:genName2"))
		return soap_serve_ns__genName2(soap);
	if (!soap_match_tag(soap, soap->tag, "ns:genName3"))
		return soap_serve_ns__genName3(soap);
	return soap->error = SOAP_NO_METHOD;
}
#endif

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__genName(struct soap *soap)
{	struct ns__genName soap_tmp_ns__genName;
	struct ns__genNameResponse soap_tmp_ns__genNameResponse;
	soap_default_ns__genNameResponse(soap, &soap_tmp_ns__genNameResponse);
	soap_default_ns__genName(soap, &soap_tmp_ns__genName);
	soap->encodingStyle = "";
	if (!soap_get_ns__genName(soap, &soap_tmp_ns__genName, "ns:genName", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns__genName(soap, soap_tmp_ns__genName.InputFilename, soap_tmp_ns__genNameResponse.OutputFilename);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns__genNameResponse(soap, &soap_tmp_ns__genNameResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__genNameResponse(soap, &soap_tmp_ns__genNameResponse, "ns:genNameResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__genNameResponse(soap, &soap_tmp_ns__genNameResponse, "ns:genNameResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__genName2(struct soap *soap)
{	struct ns__genName2 soap_tmp_ns__genName2;
	struct ns__genName2Response soap_tmp_ns__genName2Response;
	char * soap_tmp_string;
	soap_default_ns__genName2Response(soap, &soap_tmp_ns__genName2Response);
	soap_tmp_string = NULL;
	soap_tmp_ns__genName2Response.OutputFilename = &soap_tmp_string;
	soap_default_ns__genName2(soap, &soap_tmp_ns__genName2);
	soap->encodingStyle = "";
	if (!soap_get_ns__genName2(soap, &soap_tmp_ns__genName2, "ns:genName2", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns__genName2(soap, soap_tmp_ns__genName2.InputFilename, soap_tmp_ns__genName2Response.OutputFilename);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns__genName2Response(soap, &soap_tmp_ns__genName2Response);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__genName2Response(soap, &soap_tmp_ns__genName2Response, "ns:genName2Response", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__genName2Response(soap, &soap_tmp_ns__genName2Response, "ns:genName2Response", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__genName3(struct soap *soap)
{	struct ns__genName3 soap_tmp_ns__genName3;
	ns__Output out;
	out.soap_default(soap);
	soap_default_ns__genName3(soap, &soap_tmp_ns__genName3);
	soap->encodingStyle = "";
	if (!soap_get_ns__genName3(soap, &soap_tmp_ns__genName3, "ns:genName3", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns__genName3(soap, soap_tmp_ns__genName3.InputFilename, out);
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
		 || out.soap_put(soap, "ns:Output", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || out.soap_put(soap, "ns:Output", "")
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