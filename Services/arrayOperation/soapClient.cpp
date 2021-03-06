/* soapClient.cpp
   Generated by gSOAP 2.8.14 from ArrayOperation.h

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

SOAP_SOURCE_STAMP("@(#) soapClient.cpp ver 2.8.14 2013-03-16 23:49:45 GMT")


SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__Or(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string src1, std::string src2, std::string &OutputMatFilename)
{	struct ns__Or soap_tmp_ns__Or;
	struct ns__OrResponse *soap_tmp_ns__OrResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/ArrayOperationServer";
	soap->encodingStyle = "";
	soap_tmp_ns__Or.src1 = src1;
	soap_tmp_ns__Or.src2 = src2;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__Or(soap, &soap_tmp_ns__Or);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__Or(soap, &soap_tmp_ns__Or, "ns:Or", NULL)
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
	 || soap_put_ns__Or(soap, &soap_tmp_ns__Or, "ns:Or", NULL)
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
	soap_tmp_ns__OrResponse = soap_get_ns__OrResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__OrResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__And(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string src1, std::string src2, std::string &OutputMatFilename)
{	struct ns__And soap_tmp_ns__And;
	struct ns__AndResponse *soap_tmp_ns__AndResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/ArrayOperationServer";
	soap->encodingStyle = "";
	soap_tmp_ns__And.src1 = src1;
	soap_tmp_ns__And.src2 = src2;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__And(soap, &soap_tmp_ns__And);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__And(soap, &soap_tmp_ns__And, "ns:And", NULL)
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
	 || soap_put_ns__And(soap, &soap_tmp_ns__And, "ns:And", NULL)
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
	soap_tmp_ns__AndResponse = soap_get_ns__AndResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__AndResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__Xor(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string src1, std::string src2, std::string &OutputMatFilename)
{	struct ns__Xor soap_tmp_ns__Xor;
	struct ns__XorResponse *soap_tmp_ns__XorResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/ArrayOperationServer";
	soap->encodingStyle = "";
	soap_tmp_ns__Xor.src1 = src1;
	soap_tmp_ns__Xor.src2 = src2;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__Xor(soap, &soap_tmp_ns__Xor);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__Xor(soap, &soap_tmp_ns__Xor, "ns:Xor", NULL)
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
	 || soap_put_ns__Xor(soap, &soap_tmp_ns__Xor, "ns:Xor", NULL)
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
	soap_tmp_ns__XorResponse = soap_get_ns__XorResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__XorResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__Not(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string src, std::string &OutputMatFilename)
{	struct ns__Not soap_tmp_ns__Not;
	struct ns__NotResponse *soap_tmp_ns__NotResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/ArrayOperationServer";
	soap->encodingStyle = "";
	soap_tmp_ns__Not.src = src;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__Not(soap, &soap_tmp_ns__Not);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__Not(soap, &soap_tmp_ns__Not, "ns:Not", NULL)
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
	 || soap_put_ns__Not(soap, &soap_tmp_ns__Not, "ns:Not", NULL)
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
	soap_tmp_ns__NotResponse = soap_get_ns__NotResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__NotResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__addWeighted(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename1, double alpha, std::string InputMatFilename2, double beta, double gamma, int dtype_D, std::string &OutputMatFilename)
{	struct ns__addWeighted soap_tmp_ns__addWeighted;
	struct ns__addWeightedResponse *soap_tmp_ns__addWeightedResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/ArrayOperationServer";
	soap->encodingStyle = "";
	soap_tmp_ns__addWeighted.InputMatFilename1 = InputMatFilename1;
	soap_tmp_ns__addWeighted.alpha = alpha;
	soap_tmp_ns__addWeighted.InputMatFilename2 = InputMatFilename2;
	soap_tmp_ns__addWeighted.beta = beta;
	soap_tmp_ns__addWeighted.gamma = gamma;
	soap_tmp_ns__addWeighted.dtype_D = dtype_D;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__addWeighted(soap, &soap_tmp_ns__addWeighted);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__addWeighted(soap, &soap_tmp_ns__addWeighted, "ns:addWeighted", NULL)
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
	 || soap_put_ns__addWeighted(soap, &soap_tmp_ns__addWeighted, "ns:addWeighted", NULL)
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
	soap_tmp_ns__addWeightedResponse = soap_get_ns__addWeightedResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__addWeightedResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__add(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename1, std::string InputMatFilename2, std::string maskFilename_D, int dtype_D, std::string &OutputMatFilename)
{	struct ns__add soap_tmp_ns__add;
	struct ns__addResponse *soap_tmp_ns__addResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/ArrayOperationServer";
	soap->encodingStyle = "";
	soap_tmp_ns__add.InputMatFilename1 = InputMatFilename1;
	soap_tmp_ns__add.InputMatFilename2 = InputMatFilename2;
	soap_tmp_ns__add.maskFilename_D = maskFilename_D;
	soap_tmp_ns__add.dtype_D = dtype_D;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__add(soap, &soap_tmp_ns__add);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__add(soap, &soap_tmp_ns__add, "ns:add", NULL)
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
	 || soap_put_ns__add(soap, &soap_tmp_ns__add, "ns:add", NULL)
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
	soap_tmp_ns__addResponse = soap_get_ns__addResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__addResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__subtract(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename1, std::string InputMatFilename2, std::string maskFilename_D, int dtype_D, std::string &OutputMatFilename)
{	struct ns__subtract soap_tmp_ns__subtract;
	struct ns__subtractResponse *soap_tmp_ns__subtractResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/ArrayOperationServer";
	soap->encodingStyle = "";
	soap_tmp_ns__subtract.InputMatFilename1 = InputMatFilename1;
	soap_tmp_ns__subtract.InputMatFilename2 = InputMatFilename2;
	soap_tmp_ns__subtract.maskFilename_D = maskFilename_D;
	soap_tmp_ns__subtract.dtype_D = dtype_D;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__subtract(soap, &soap_tmp_ns__subtract);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__subtract(soap, &soap_tmp_ns__subtract, "ns:subtract", NULL)
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
	 || soap_put_ns__subtract(soap, &soap_tmp_ns__subtract, "ns:subtract", NULL)
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
	soap_tmp_ns__subtractResponse = soap_get_ns__subtractResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__subtractResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__abs(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, std::string &OutputMatFilename)
{	struct ns__abs soap_tmp_ns__abs;
	struct ns__absResponse *soap_tmp_ns__absResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/ArrayOperationServer";
	soap->encodingStyle = "";
	soap_tmp_ns__abs.InputMatFilename = InputMatFilename;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__abs(soap, &soap_tmp_ns__abs);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__abs(soap, &soap_tmp_ns__abs, "ns:abs", NULL)
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
	 || soap_put_ns__abs(soap, &soap_tmp_ns__abs, "ns:abs", NULL)
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
	soap_tmp_ns__absResponse = soap_get_ns__absResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__absResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__absdiff(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename1, std::string InputMatFilename2, std::string &OutputMatFilename)
{	struct ns__absdiff soap_tmp_ns__absdiff;
	struct ns__absdiffResponse *soap_tmp_ns__absdiffResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/ArrayOperationServer";
	soap->encodingStyle = "";
	soap_tmp_ns__absdiff.InputMatFilename1 = InputMatFilename1;
	soap_tmp_ns__absdiff.InputMatFilename2 = InputMatFilename2;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__absdiff(soap, &soap_tmp_ns__absdiff);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__absdiff(soap, &soap_tmp_ns__absdiff, "ns:absdiff", NULL)
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
	 || soap_put_ns__absdiff(soap, &soap_tmp_ns__absdiff, "ns:absdiff", NULL)
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
	soap_tmp_ns__absdiffResponse = soap_get_ns__absdiffResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__absdiffResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__sqrt(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, std::string &OutputMatFilename)
{	struct ns__sqrt soap_tmp_ns__sqrt;
	struct ns__sqrtResponse *soap_tmp_ns__sqrtResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/ArrayOperationServer";
	soap->encodingStyle = "";
	soap_tmp_ns__sqrt.InputMatFilename = InputMatFilename;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__sqrt(soap, &soap_tmp_ns__sqrt);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__sqrt(soap, &soap_tmp_ns__sqrt, "ns:sqrt", NULL)
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
	 || soap_put_ns__sqrt(soap, &soap_tmp_ns__sqrt, "ns:sqrt", NULL)
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
	soap_tmp_ns__sqrtResponse = soap_get_ns__sqrtResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__sqrtResponse->OutputMatFilename;
	return soap_closesock(soap);
}

#if defined(__BORLANDC__)
#pragma option pop
#pragma option pop
#endif

/* End of soapClient.cpp */
