/* soaphelloProxy.cpp
   Generated by gSOAP 2.7.17 from hello.h
   Copyright(C) 2000-2010, Robert van Engelen, Genivia Inc. All Rights Reserved.
   This part of the software is released under one of the following licenses:
   GPL, the gSOAP public license, or Genivia's license for commercial use.
*/

#include "soaphelloProxy.h"

helloProxy::helloProxy()
{	helloProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

helloProxy::helloProxy(const struct soap &_soap) : soap(_soap)
{ }

helloProxy::helloProxy(soap_mode iomode)
{	helloProxy_init(iomode, iomode);
}

helloProxy::helloProxy(soap_mode imode, soap_mode omode)
{	helloProxy_init(imode, omode);
}

void helloProxy::helloProxy_init(soap_mode imode, soap_mode omode)
{	soap_imode(this, imode);
	soap_omode(this, omode);
	soap_endpoint = NULL;
	static const struct Namespace namespaces[] =
{
	{"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
	{"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"ns", "urn:hello", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};
	this->namespaces = namespaces;
}

helloProxy::~helloProxy()
{ }

void helloProxy::destroy()
{	soap_destroy(this);
	soap_end(this);
}

void helloProxy::soap_noheader()
{	header = NULL;
}

const SOAP_ENV__Fault *helloProxy::soap_fault()
{	return this->fault;
}

const char *helloProxy::soap_fault_string()
{	return *soap_faultstring(this);
}

const char *helloProxy::soap_fault_detail()
{	return *soap_faultdetail(this);
}

int helloProxy::soap_close_socket()
{	return soap_closesock(this);
}

void helloProxy::soap_print_fault(FILE *fd)
{	::soap_print_fault(this, fd);
}

#ifndef WITH_LEAN
void helloProxy::soap_stream_fault(std::ostream& os)
{	::soap_stream_fault(this, os);
}

char *helloProxy::soap_sprint_fault(char *buf, size_t len)
{	return ::soap_sprint_fault(this, buf, len);
}
#endif

int helloProxy::hello(struct soap *_param_1, char *&_param_2)
{	struct soap *soap = this;
	struct ns__hello soap_tmp_ns__hello;
	struct ns__helloResponse *soap_tmp_ns__helloResponse;
	const char *soap_action = NULL;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost/cgi-bin/hello";
	soap->encodingStyle = "";
	soap_tmp_ns__hello._param_1 = _param_1;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__hello(soap, &soap_tmp_ns__hello);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__hello(soap, &soap_tmp_ns__hello, "ns:hello", NULL)
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
	 || soap_put_ns__hello(soap, &soap_tmp_ns__hello, "ns:hello", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	_param_2 = NULL;
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns__helloResponse = soap_get_ns__helloResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	_param_2 = soap_tmp_ns__helloResponse->_param_2;
	return soap_closesock(soap);
}
/* End of client proxy code */
