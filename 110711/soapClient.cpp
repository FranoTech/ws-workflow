/* soapClient.cpp
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

SOAP_SOURCE_STAMP("@(#) soapClient.cpp ver 2.8.2 2011-07-15 15:19:39 GMT")


SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__Ipl1ChToMat(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *InputFilename, ns__ImageData &out)
{	struct ns__Ipl1ChToMat soap_tmp_ns__Ipl1ChToMat;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost/cgi-bin/imgProcessServer";
	soap->encodingStyle = "";
	soap_tmp_ns__Ipl1ChToMat.InputFilename = InputFilename;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__Ipl1ChToMat(soap, &soap_tmp_ns__Ipl1ChToMat);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__Ipl1ChToMat(soap, &soap_tmp_ns__Ipl1ChToMat, "ns:Ipl1ChToMat", NULL)
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
	 || soap_put_ns__Ipl1ChToMat(soap, &soap_tmp_ns__Ipl1ChToMat, "ns:Ipl1ChToMat", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&out)
		return soap_closesock(soap);
	out.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	out.soap_get(soap, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__BinaryThreshold(struct soap *soap, const char *soap_endpoint, const char *soap_action, ns__ImageData in, double threshold, double maxValue, ns__ImageData &out)
{	struct ns__BinaryThreshold soap_tmp_ns__BinaryThreshold;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost/cgi-bin/imgProcessServer";
	soap->encodingStyle = "";
	soap_tmp_ns__BinaryThreshold.in = in;
	soap_tmp_ns__BinaryThreshold.threshold = threshold;
	soap_tmp_ns__BinaryThreshold.maxValue = maxValue;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__BinaryThreshold(soap, &soap_tmp_ns__BinaryThreshold);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__BinaryThreshold(soap, &soap_tmp_ns__BinaryThreshold, "ns:BinaryThreshold", NULL)
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
	 || soap_put_ns__BinaryThreshold(soap, &soap_tmp_ns__BinaryThreshold, "ns:BinaryThreshold", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&out)
		return soap_closesock(soap);
	out.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	out.soap_get(soap, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__MorphOpen(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *InputFilename, char *filename, char *&OutputFilename)
{	struct ns__MorphOpen soap_tmp_ns__MorphOpen;
	struct ns__MorphOpenResponse *soap_tmp_ns__MorphOpenResponse;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost/cgi-bin/imgProcessServer";
	soap->encodingStyle = "";
	soap_tmp_ns__MorphOpen.InputFilename = InputFilename;
	soap_tmp_ns__MorphOpen.filename = filename;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__MorphOpen(soap, &soap_tmp_ns__MorphOpen);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__MorphOpen(soap, &soap_tmp_ns__MorphOpen, "ns:MorphOpen", NULL)
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
	 || soap_put_ns__MorphOpen(soap, &soap_tmp_ns__MorphOpen, "ns:MorphOpen", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	OutputFilename = NULL;
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns__MorphOpenResponse = soap_get_ns__MorphOpenResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputFilename = soap_tmp_ns__MorphOpenResponse->OutputFilename;
	return soap_closesock(soap);
}

#if defined(__BORLANDC__)
#pragma option pop
#pragma option pop
#endif

/* End of soapClient.cpp */
