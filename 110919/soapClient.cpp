/* soapClient.cpp
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

SOAP_SOURCE_STAMP("@(#) soapClient.cpp ver 2.7.17 2011-10-11 03:34:22 GMT")


SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__loadMat(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *InputImageFilename, int loadparam, char **OutputMatFilename)
{	struct ns__loadMat soap_tmp_ns__loadMat;
	struct ns__loadMatResponse *soap_tmp_ns__loadMatResponse;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost/cgi-bin/imgProcessServer";
	soap->encodingStyle = "";
	soap_tmp_ns__loadMat.InputImageFilename = InputImageFilename;
	soap_tmp_ns__loadMat.loadparam = loadparam;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__loadMat(soap, &soap_tmp_ns__loadMat);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__loadMat(soap, &soap_tmp_ns__loadMat, "ns:loadMat", NULL)
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
	 || soap_put_ns__loadMat(soap, &soap_tmp_ns__loadMat, "ns:loadMat", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!OutputMatFilename)
		return soap_closesock(soap);
	*OutputMatFilename = NULL;
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns__loadMatResponse = soap_get_ns__loadMatResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	if (OutputMatFilename && soap_tmp_ns__loadMatResponse->OutputMatFilename)
		*OutputMatFilename = *soap_tmp_ns__loadMatResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__binaryThreshold(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *InputMatFilename, double thresholdValue, double maxValue, char **OutputMatFilename)
{	struct ns__binaryThreshold soap_tmp_ns__binaryThreshold;
	struct ns__binaryThresholdResponse *soap_tmp_ns__binaryThresholdResponse;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost/cgi-bin/imgProcessServer";
	soap->encodingStyle = "";
	soap_tmp_ns__binaryThreshold.InputMatFilename = InputMatFilename;
	soap_tmp_ns__binaryThreshold.thresholdValue = thresholdValue;
	soap_tmp_ns__binaryThreshold.maxValue = maxValue;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__binaryThreshold(soap, &soap_tmp_ns__binaryThreshold);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__binaryThreshold(soap, &soap_tmp_ns__binaryThreshold, "ns:binaryThreshold", NULL)
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
	 || soap_put_ns__binaryThreshold(soap, &soap_tmp_ns__binaryThreshold, "ns:binaryThreshold", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!OutputMatFilename)
		return soap_closesock(soap);
	*OutputMatFilename = NULL;
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns__binaryThresholdResponse = soap_get_ns__binaryThresholdResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	if (OutputMatFilename && soap_tmp_ns__binaryThresholdResponse->OutputMatFilename)
		*OutputMatFilename = *soap_tmp_ns__binaryThresholdResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__morphOpen(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *InpuMattFilename, char **OutputMatFilename)
{	struct ns__morphOpen soap_tmp_ns__morphOpen;
	struct ns__morphOpenResponse *soap_tmp_ns__morphOpenResponse;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost/cgi-bin/imgProcessServer";
	soap->encodingStyle = "";
	soap_tmp_ns__morphOpen.InpuMattFilename = InpuMattFilename;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__morphOpen(soap, &soap_tmp_ns__morphOpen);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__morphOpen(soap, &soap_tmp_ns__morphOpen, "ns:morphOpen", NULL)
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
	 || soap_put_ns__morphOpen(soap, &soap_tmp_ns__morphOpen, "ns:morphOpen", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!OutputMatFilename)
		return soap_closesock(soap);
	*OutputMatFilename = NULL;
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns__morphOpenResponse = soap_get_ns__morphOpenResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	if (OutputMatFilename && soap_tmp_ns__morphOpenResponse->OutputMatFilename)
		*OutputMatFilename = *soap_tmp_ns__morphOpenResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__MatToJPG(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *InputMatFilename, char **OutputMatFilename)
{	struct ns__MatToJPG soap_tmp_ns__MatToJPG;
	struct ns__MatToJPGResponse *soap_tmp_ns__MatToJPGResponse;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost/cgi-bin/imgProcessServer";
	soap->encodingStyle = "";
	soap_tmp_ns__MatToJPG.InputMatFilename = InputMatFilename;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__MatToJPG(soap, &soap_tmp_ns__MatToJPG);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__MatToJPG(soap, &soap_tmp_ns__MatToJPG, "ns:MatToJPG", NULL)
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
	 || soap_put_ns__MatToJPG(soap, &soap_tmp_ns__MatToJPG, "ns:MatToJPG", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!OutputMatFilename)
		return soap_closesock(soap);
	*OutputMatFilename = NULL;
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns__MatToJPGResponse = soap_get_ns__MatToJPGResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	if (OutputMatFilename && soap_tmp_ns__MatToJPGResponse->OutputMatFilename)
		*OutputMatFilename = *soap_tmp_ns__MatToJPGResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__findContoursAndFillpoly(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *InputMatFilename, int lowerBound, ns__FindContours &out)
{	struct ns__findContoursAndFillpoly soap_tmp_ns__findContoursAndFillpoly;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost/cgi-bin/imgProcessServer";
	soap->encodingStyle = "";
	soap_tmp_ns__findContoursAndFillpoly.InputMatFilename = InputMatFilename;
	soap_tmp_ns__findContoursAndFillpoly.lowerBound = lowerBound;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__findContoursAndFillpoly(soap, &soap_tmp_ns__findContoursAndFillpoly);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__findContoursAndFillpoly(soap, &soap_tmp_ns__findContoursAndFillpoly, "ns:findContoursAndFillpoly", NULL)
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
	 || soap_put_ns__findContoursAndFillpoly(soap, &soap_tmp_ns__findContoursAndFillpoly, "ns:findContoursAndFillpoly", NULL)
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

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__erode(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *src, char *element, int iteration, char **OutputMatFilename)
{	struct ns__erode soap_tmp_ns__erode;
	struct ns__erodeResponse *soap_tmp_ns__erodeResponse;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost/cgi-bin/imgProcessServer";
	soap->encodingStyle = "";
	soap_tmp_ns__erode.src = src;
	soap_tmp_ns__erode.element = element;
	soap_tmp_ns__erode.iteration = iteration;
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
	if (!OutputMatFilename)
		return soap_closesock(soap);
	*OutputMatFilename = NULL;
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
	if (OutputMatFilename && soap_tmp_ns__erodeResponse->OutputMatFilename)
		*OutputMatFilename = *soap_tmp_ns__erodeResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__dilate(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *src, char *element, int iteration, char **OutputMatFilename)
{	struct ns__dilate soap_tmp_ns__dilate;
	struct ns__dilateResponse *soap_tmp_ns__dilateResponse;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost/cgi-bin/imgProcessServer";
	soap->encodingStyle = "";
	soap_tmp_ns__dilate.src = src;
	soap_tmp_ns__dilate.element = element;
	soap_tmp_ns__dilate.iteration = iteration;
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
	if (!OutputMatFilename)
		return soap_closesock(soap);
	*OutputMatFilename = NULL;
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
	if (OutputMatFilename && soap_tmp_ns__dilateResponse->OutputMatFilename)
		*OutputMatFilename = *soap_tmp_ns__dilateResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__Or(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *src1, char *src2, char **OutputMatFilename)
{	struct ns__Or soap_tmp_ns__Or;
	struct ns__OrResponse *soap_tmp_ns__OrResponse;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost/cgi-bin/imgProcessServer";
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
	if (!OutputMatFilename)
		return soap_closesock(soap);
	*OutputMatFilename = NULL;
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
	if (OutputMatFilename && soap_tmp_ns__OrResponse->OutputMatFilename)
		*OutputMatFilename = *soap_tmp_ns__OrResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__And(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *src1, char *src2, char **OutputMatFilename)
{	struct ns__And soap_tmp_ns__And;
	struct ns__AndResponse *soap_tmp_ns__AndResponse;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost/cgi-bin/imgProcessServer";
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
	if (!OutputMatFilename)
		return soap_closesock(soap);
	*OutputMatFilename = NULL;
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
	if (OutputMatFilename && soap_tmp_ns__AndResponse->OutputMatFilename)
		*OutputMatFilename = *soap_tmp_ns__AndResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__Not(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *src, char **OutputMatFilename)
{	struct ns__Not soap_tmp_ns__Not;
	struct ns__NotResponse *soap_tmp_ns__NotResponse;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost/cgi-bin/imgProcessServer";
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
	if (!OutputMatFilename)
		return soap_closesock(soap);
	*OutputMatFilename = NULL;
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
	if (OutputMatFilename && soap_tmp_ns__NotResponse->OutputMatFilename)
		*OutputMatFilename = *soap_tmp_ns__NotResponse->OutputMatFilename;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__removeSmallCell(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *inputMatFilename, ns__RemoveSmallCell &out)
{	struct ns__removeSmallCell soap_tmp_ns__removeSmallCell;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost/cgi-bin/imgProcessServer";
	soap->encodingStyle = "";
	soap_tmp_ns__removeSmallCell.inputMatFilename = inputMatFilename;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__removeSmallCell(soap, &soap_tmp_ns__removeSmallCell);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__removeSmallCell(soap, &soap_tmp_ns__removeSmallCell, "ns:removeSmallCell", NULL)
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
	 || soap_put_ns__removeSmallCell(soap, &soap_tmp_ns__removeSmallCell, "ns:removeSmallCell", NULL)
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

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__scanningCell(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *inputMatFilename, char **outputMatFilename)
{	struct ns__scanningCell soap_tmp_ns__scanningCell;
	struct ns__scanningCellResponse *soap_tmp_ns__scanningCellResponse;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost/cgi-bin/imgProcessServer";
	soap->encodingStyle = "";
	soap_tmp_ns__scanningCell.inputMatFilename = inputMatFilename;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__scanningCell(soap, &soap_tmp_ns__scanningCell);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__scanningCell(soap, &soap_tmp_ns__scanningCell, "ns:scanningCell", NULL)
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
	 || soap_put_ns__scanningCell(soap, &soap_tmp_ns__scanningCell, "ns:scanningCell", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!outputMatFilename)
		return soap_closesock(soap);
	*outputMatFilename = NULL;
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns__scanningCellResponse = soap_get_ns__scanningCellResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	if (outputMatFilename && soap_tmp_ns__scanningCellResponse->outputMatFilename)
		*outputMatFilename = *soap_tmp_ns__scanningCellResponse->outputMatFilename;
	return soap_closesock(soap);
}

#if defined(__BORLANDC__)
#pragma option pop
#pragma option pop
#endif

/* End of soapClient.cpp */
