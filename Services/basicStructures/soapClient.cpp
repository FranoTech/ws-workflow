/* soapClient.cpp
   Generated by gSOAP 2.8.14 from BasicStructures.h

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

SOAP_SOURCE_STAMP("@(#) soapClient.cpp ver 2.8.14 2013-03-16 23:48:16 GMT")


SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__rowRange(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, int startCol, int endCol, std::string &OutputMatFilename)
{	struct ns__rowRange soap_tmp_ns__rowRange;
	struct ns__rowRangeResponse *soap_tmp_ns__rowRangeResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/BasicStructuresServer";
	soap->encodingStyle = "";
	soap_tmp_ns__rowRange.InputMatFilename = InputMatFilename;
	soap_tmp_ns__rowRange.startCol = startCol;
	soap_tmp_ns__rowRange.endCol = endCol;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__rowRange(soap, &soap_tmp_ns__rowRange);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__rowRange(soap, &soap_tmp_ns__rowRange, "ns:rowRange", NULL)
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
	 || soap_put_ns__rowRange(soap, &soap_tmp_ns__rowRange, "ns:rowRange", NULL)
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
	soap_tmp_ns__rowRangeResponse = soap_get_ns__rowRangeResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__rowRangeResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__colRange(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, int startCol, int endCol, std::string &OutputMatFilename)
{	struct ns__colRange soap_tmp_ns__colRange;
	struct ns__colRangeResponse *soap_tmp_ns__colRangeResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/BasicStructuresServer";
	soap->encodingStyle = "";
	soap_tmp_ns__colRange.InputMatFilename = InputMatFilename;
	soap_tmp_ns__colRange.startCol = startCol;
	soap_tmp_ns__colRange.endCol = endCol;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__colRange(soap, &soap_tmp_ns__colRange);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__colRange(soap, &soap_tmp_ns__colRange, "ns:colRange", NULL)
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
	 || soap_put_ns__colRange(soap, &soap_tmp_ns__colRange, "ns:colRange", NULL)
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
	soap_tmp_ns__colRangeResponse = soap_get_ns__colRangeResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__colRangeResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__convertTo(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, std::string types, double alpha_D, double beta_D, std::string &OutputMatFilename)
{	struct ns__convertTo soap_tmp_ns__convertTo;
	struct ns__convertToResponse *soap_tmp_ns__convertToResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/BasicStructuresServer";
	soap->encodingStyle = "";
	soap_tmp_ns__convertTo.InputMatFilename = InputMatFilename;
	soap_tmp_ns__convertTo.types = types;
	soap_tmp_ns__convertTo.alpha_D = alpha_D;
	soap_tmp_ns__convertTo.beta_D = beta_D;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__convertTo(soap, &soap_tmp_ns__convertTo);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__convertTo(soap, &soap_tmp_ns__convertTo, "ns:convertTo", NULL)
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
	 || soap_put_ns__convertTo(soap, &soap_tmp_ns__convertTo, "ns:convertTo", NULL)
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
	soap_tmp_ns__convertToResponse = soap_get_ns__convertToResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__convertToResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__createMat(struct soap *soap, const char *soap_endpoint, const char *soap_action, int rows, int columns, std::string type, int scalar, std::string &OutputMatFilename)
{	struct ns__createMat soap_tmp_ns__createMat;
	struct ns__createMatResponse *soap_tmp_ns__createMatResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/BasicStructuresServer";
	soap->encodingStyle = "";
	soap_tmp_ns__createMat.rows = rows;
	soap_tmp_ns__createMat.columns = columns;
	soap_tmp_ns__createMat.type = type;
	soap_tmp_ns__createMat.scalar = scalar;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__createMat(soap, &soap_tmp_ns__createMat);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__createMat(soap, &soap_tmp_ns__createMat, "ns:createMat", NULL)
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
	 || soap_put_ns__createMat(soap, &soap_tmp_ns__createMat, "ns:createMat", NULL)
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
	soap_tmp_ns__createMatResponse = soap_get_ns__createMatResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__createMatResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__Inverse(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, std::string InvMethod_D, std::string &OutputMatFilename)
{	struct ns__Inverse soap_tmp_ns__Inverse;
	struct ns__InverseResponse *soap_tmp_ns__InverseResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/BasicStructuresServer";
	soap->encodingStyle = "";
	soap_tmp_ns__Inverse.InputMatFilename = InputMatFilename;
	soap_tmp_ns__Inverse.InvMethod_D = InvMethod_D;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__Inverse(soap, &soap_tmp_ns__Inverse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__Inverse(soap, &soap_tmp_ns__Inverse, "ns:Inverse", NULL)
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
	 || soap_put_ns__Inverse(soap, &soap_tmp_ns__Inverse, "ns:Inverse", NULL)
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
	soap_tmp_ns__InverseResponse = soap_get_ns__InverseResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__InverseResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__mul(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, std::string AnotherMatFilename, double scale_D, std::string &OutputMatFilename)
{	struct ns__mul soap_tmp_ns__mul;
	struct ns__mulResponse *soap_tmp_ns__mulResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/BasicStructuresServer";
	soap->encodingStyle = "";
	soap_tmp_ns__mul.InputMatFilename = InputMatFilename;
	soap_tmp_ns__mul.AnotherMatFilename = AnotherMatFilename;
	soap_tmp_ns__mul.scale_D = scale_D;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__mul(soap, &soap_tmp_ns__mul);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__mul(soap, &soap_tmp_ns__mul, "ns:mul", NULL)
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
	 || soap_put_ns__mul(soap, &soap_tmp_ns__mul, "ns:mul", NULL)
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
	soap_tmp_ns__mulResponse = soap_get_ns__mulResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__mulResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__cross(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, std::string AnotherMatFilename, std::string &OutputMatFilename)
{	struct ns__cross soap_tmp_ns__cross;
	struct ns__crossResponse *soap_tmp_ns__crossResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/BasicStructuresServer";
	soap->encodingStyle = "";
	soap_tmp_ns__cross.InputMatFilename = InputMatFilename;
	soap_tmp_ns__cross.AnotherMatFilename = AnotherMatFilename;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__cross(soap, &soap_tmp_ns__cross);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__cross(soap, &soap_tmp_ns__cross, "ns:cross", NULL)
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
	 || soap_put_ns__cross(soap, &soap_tmp_ns__cross, "ns:cross", NULL)
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
	soap_tmp_ns__crossResponse = soap_get_ns__crossResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__crossResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__dot(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, std::string AnotherMatFilename, std::string &OutputMatFilename)
{	struct ns__dot soap_tmp_ns__dot;
	struct ns__dotResponse *soap_tmp_ns__dotResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/BasicStructuresServer";
	soap->encodingStyle = "";
	soap_tmp_ns__dot.InputMatFilename = InputMatFilename;
	soap_tmp_ns__dot.AnotherMatFilename = AnotherMatFilename;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__dot(soap, &soap_tmp_ns__dot);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__dot(soap, &soap_tmp_ns__dot, "ns:dot", NULL)
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
	 || soap_put_ns__dot(soap, &soap_tmp_ns__dot, "ns:dot", NULL)
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
	soap_tmp_ns__dotResponse = soap_get_ns__dotResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__dotResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__zeros(struct soap *soap, const char *soap_endpoint, const char *soap_action, int rows, int columns, std::string type, std::string &OutputMatFilename)
{	struct ns__zeros soap_tmp_ns__zeros;
	struct ns__zerosResponse *soap_tmp_ns__zerosResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/BasicStructuresServer";
	soap->encodingStyle = "";
	soap_tmp_ns__zeros.rows = rows;
	soap_tmp_ns__zeros.columns = columns;
	soap_tmp_ns__zeros.type = type;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__zeros(soap, &soap_tmp_ns__zeros);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__zeros(soap, &soap_tmp_ns__zeros, "ns:zeros", NULL)
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
	 || soap_put_ns__zeros(soap, &soap_tmp_ns__zeros, "ns:zeros", NULL)
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
	soap_tmp_ns__zerosResponse = soap_get_ns__zerosResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__zerosResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__ones(struct soap *soap, const char *soap_endpoint, const char *soap_action, int rows, int columns, int fillWith, std::string type, std::string &OutputMatFilename)
{	struct ns__ones soap_tmp_ns__ones;
	struct ns__onesResponse *soap_tmp_ns__onesResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/BasicStructuresServer";
	soap->encodingStyle = "";
	soap_tmp_ns__ones.rows = rows;
	soap_tmp_ns__ones.columns = columns;
	soap_tmp_ns__ones.fillWith = fillWith;
	soap_tmp_ns__ones.type = type;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__ones(soap, &soap_tmp_ns__ones);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__ones(soap, &soap_tmp_ns__ones, "ns:ones", NULL)
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
	 || soap_put_ns__ones(soap, &soap_tmp_ns__ones, "ns:ones", NULL)
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
	soap_tmp_ns__onesResponse = soap_get_ns__onesResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__onesResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__getMatDetail(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, ns__MatDetail &detail)
{	struct ns__getMatDetail soap_tmp_ns__getMatDetail;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/BasicStructuresServer";
	soap->encodingStyle = "";
	soap_tmp_ns__getMatDetail.InputMatFilename = InputMatFilename;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__getMatDetail(soap, &soap_tmp_ns__getMatDetail);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__getMatDetail(soap, &soap_tmp_ns__getMatDetail, "ns:getMatDetail", NULL)
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
	 || soap_put_ns__getMatDetail(soap, &soap_tmp_ns__getMatDetail, "ns:getMatDetail", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&detail)
		return soap_closesock(soap);
	detail.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	detail.soap_get(soap, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__printAllMatValue(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, std::string &OutputMat)
{	struct ns__printAllMatValue soap_tmp_ns__printAllMatValue;
	struct ns__printAllMatValueResponse *soap_tmp_ns__printAllMatValueResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/BasicStructuresServer";
	soap->encodingStyle = "";
	soap_tmp_ns__printAllMatValue.InputMatFilename = InputMatFilename;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__printAllMatValue(soap, &soap_tmp_ns__printAllMatValue);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__printAllMatValue(soap, &soap_tmp_ns__printAllMatValue, "ns:printAllMatValue", NULL)
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
	 || soap_put_ns__printAllMatValue(soap, &soap_tmp_ns__printAllMatValue, "ns:printAllMatValue", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&OutputMat)
		return soap_closesock(soap);
	soap_default_std__string(soap, &OutputMat);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns__printAllMatValueResponse = soap_get_ns__printAllMatValueResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMat = soap_tmp_ns__printAllMatValueResponse->OutputMat;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__accessPixelValue(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::string InputMatFilename, std::string returnType, int intToSet, float floatToSet, int pixelI, int pixelJ, int channel, std::string &OutputMatFilename)
{	struct ns__accessPixelValue soap_tmp_ns__accessPixelValue;
	struct ns__accessPixelValueResponse *soap_tmp_ns__accessPixelValueResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/cgi-bin/BasicStructuresServer";
	soap->encodingStyle = "";
	soap_tmp_ns__accessPixelValue.InputMatFilename = InputMatFilename;
	soap_tmp_ns__accessPixelValue.returnType = returnType;
	soap_tmp_ns__accessPixelValue.intToSet = intToSet;
	soap_tmp_ns__accessPixelValue.floatToSet = floatToSet;
	soap_tmp_ns__accessPixelValue.pixelI = pixelI;
	soap_tmp_ns__accessPixelValue.pixelJ = pixelJ;
	soap_tmp_ns__accessPixelValue.channel = channel;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__accessPixelValue(soap, &soap_tmp_ns__accessPixelValue);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__accessPixelValue(soap, &soap_tmp_ns__accessPixelValue, "ns:accessPixelValue", NULL)
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
	 || soap_put_ns__accessPixelValue(soap, &soap_tmp_ns__accessPixelValue, "ns:accessPixelValue", NULL)
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
	soap_tmp_ns__accessPixelValueResponse = soap_get_ns__accessPixelValueResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	OutputMatFilename = soap_tmp_ns__accessPixelValueResponse->OutputMatFilename;
	return soap_closesock(soap);
}

#if defined(__BORLANDC__)
#pragma option pop
#pragma option pop
#endif

/* End of soapClient.cpp */
