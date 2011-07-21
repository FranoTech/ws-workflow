/* soapH.h
   Generated by gSOAP 2.7.17 from imgProcess.h
   Copyright(C) 2000-2010, Robert van Engelen, Genivia Inc. All Rights Reserved.
   This part of the software is released under one of the following licenses:
   GPL, the gSOAP public license, or Genivia's license for commercial use.
*/

#ifndef soapH_H
#define soapH_H
#include "soapStub.h"
#ifndef WITH_NOIDREF

#ifdef __cplusplus
extern "C" {
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_markelement(struct soap*, const void*, int);
SOAP_FMAC3 int SOAP_FMAC4 soap_putelement(struct soap*, const void*, const char*, int, int);
SOAP_FMAC3 void *SOAP_FMAC4 soap_getelement(struct soap*, int*);

#ifdef __cplusplus
}
#endif
SOAP_FMAC3 int SOAP_FMAC4 soap_putindependent(struct soap*);
SOAP_FMAC3 int SOAP_FMAC4 soap_getindependent(struct soap*);
#endif
SOAP_FMAC3 int SOAP_FMAC4 soap_ignore_element(struct soap*);

SOAP_FMAC3 void * SOAP_FMAC4 soap_instantiate(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 int SOAP_FMAC4 soap_fdelete(struct soap_clist*);
SOAP_FMAC3 void* SOAP_FMAC4 soap_class_id_enter(struct soap*, const char*, void*, int, size_t, const char*, const char*);

#ifndef SOAP_TYPE_byte
#define SOAP_TYPE_byte (3)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_byte(struct soap*, char *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_byte(struct soap*, const char*, int, const char *, const char*);
SOAP_FMAC3 char * SOAP_FMAC4 soap_in_byte(struct soap*, const char*, char *, const char*);

#define soap_write_byte(soap, data) ( soap_begin_send(soap) || soap_put_byte(soap, data, NULL, NULL) || soap_end_send(soap) )


SOAP_FMAC3 int SOAP_FMAC4 soap_put_byte(struct soap*, const char *, const char*, const char*);

#define soap_read_byte(soap, data) ( soap_begin_recv(soap) || !soap_get_byte(soap, data, NULL, NULL) || soap_end_recv(soap) )

SOAP_FMAC3 char * SOAP_FMAC4 soap_get_byte(struct soap*, char *, const char*, const char*);

#ifndef SOAP_TYPE_int
#define SOAP_TYPE_int (1)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_int(struct soap*, int *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_int(struct soap*, const char*, int, const int *, const char*);
SOAP_FMAC3 int * SOAP_FMAC4 soap_in_int(struct soap*, const char*, int *, const char*);

#define soap_write_int(soap, data) ( soap_begin_send(soap) || soap_put_int(soap, data, NULL, NULL) || soap_end_send(soap) )


SOAP_FMAC3 int SOAP_FMAC4 soap_put_int(struct soap*, const int *, const char*, const char*);

#define soap_read_int(soap, data) ( soap_begin_recv(soap) || !soap_get_int(soap, data, NULL, NULL) || soap_end_recv(soap) )

SOAP_FMAC3 int * SOAP_FMAC4 soap_get_int(struct soap*, int *, const char*, const char*);

#ifndef SOAP_TYPE_unsignedByte
#define SOAP_TYPE_unsignedByte (9)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_unsignedByte(struct soap*, unsigned char *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_unsignedByte(struct soap*, const char*, int, const unsigned char *, const char*);
SOAP_FMAC3 unsigned char * SOAP_FMAC4 soap_in_unsignedByte(struct soap*, const char*, unsigned char *, const char*);

#define soap_write_unsignedByte(soap, data) ( soap_begin_send(soap) || soap_put_unsignedByte(soap, data, NULL, NULL) || soap_end_send(soap) )


SOAP_FMAC3 int SOAP_FMAC4 soap_put_unsignedByte(struct soap*, const unsigned char *, const char*, const char*);

#define soap_read_unsignedByte(soap, data) ( soap_begin_recv(soap) || !soap_get_unsignedByte(soap, data, NULL, NULL) || soap_end_recv(soap) )

SOAP_FMAC3 unsigned char * SOAP_FMAC4 soap_get_unsignedByte(struct soap*, unsigned char *, const char*, const char*);

#ifndef SOAP_TYPE_unsignedInt
#define SOAP_TYPE_unsignedInt (8)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_unsignedInt(struct soap*, unsigned int *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_unsignedInt(struct soap*, const char*, int, const unsigned int *, const char*);
SOAP_FMAC3 unsigned int * SOAP_FMAC4 soap_in_unsignedInt(struct soap*, const char*, unsigned int *, const char*);

#define soap_write_unsignedInt(soap, data) ( soap_begin_send(soap) || soap_put_unsignedInt(soap, data, NULL, NULL) || soap_end_send(soap) )


SOAP_FMAC3 int SOAP_FMAC4 soap_put_unsignedInt(struct soap*, const unsigned int *, const char*, const char*);

#define soap_read_unsignedInt(soap, data) ( soap_begin_recv(soap) || !soap_get_unsignedInt(soap, data, NULL, NULL) || soap_end_recv(soap) )

SOAP_FMAC3 unsigned int * SOAP_FMAC4 soap_get_unsignedInt(struct soap*, unsigned int *, const char*, const char*);

#ifndef SOAP_TYPE_ns__ImageData
#define SOAP_TYPE_ns__ImageData (7)
#endif
SOAP_FMAC3 int SOAP_FMAC4 soap_out_ns__ImageData(struct soap*, const char*, int, const ns__ImageData *, const char*);
SOAP_FMAC3 ns__ImageData * SOAP_FMAC4 soap_in_ns__ImageData(struct soap*, const char*, ns__ImageData *, const char*);

#define soap_write_ns__ImageData(soap, data) ( soap_begin_send(soap) || ((data)->soap_serialize(soap), 0) || (data)->soap_put(soap, NULL, NULL) || soap_end_send(soap) )


#define soap_read_ns__ImageData(soap, data) ( soap_begin_recv(soap) || !soap_get_ns__ImageData(soap, data, NULL, NULL) || soap_end_recv(soap) )

SOAP_FMAC3 ns__ImageData * SOAP_FMAC4 soap_get_ns__ImageData(struct soap*, ns__ImageData *, const char*, const char*);

#define soap_new_ns__ImageData(soap, n) soap_instantiate_ns__ImageData(soap, n, NULL, NULL, NULL)


#define soap_delete_ns__ImageData(soap, p) soap_delete(soap, p)

SOAP_FMAC1 ns__ImageData * SOAP_FMAC2 soap_instantiate_ns__ImageData(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_ns__ImageData(struct soap*, int, int, void*, size_t, const void*, size_t);

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Fault
#define SOAP_TYPE_SOAP_ENV__Fault (26)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_SOAP_ENV__Fault(struct soap*, struct SOAP_ENV__Fault *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_SOAP_ENV__Fault(struct soap*, const struct SOAP_ENV__Fault *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_SOAP_ENV__Fault(struct soap*, const char*, int, const struct SOAP_ENV__Fault *, const char*);
SOAP_FMAC3 struct SOAP_ENV__Fault * SOAP_FMAC4 soap_in_SOAP_ENV__Fault(struct soap*, const char*, struct SOAP_ENV__Fault *, const char*);

#define soap_write_SOAP_ENV__Fault(soap, data) ( soap_begin_send(soap) || (soap_serialize_SOAP_ENV__Fault(soap, data), 0) || soap_put_SOAP_ENV__Fault(soap, data, NULL, NULL) || soap_end_send(soap) )


SOAP_FMAC3 int SOAP_FMAC4 soap_put_SOAP_ENV__Fault(struct soap*, const struct SOAP_ENV__Fault *, const char*, const char*);

#define soap_read_SOAP_ENV__Fault(soap, data) ( soap_begin_recv(soap) || !soap_get_SOAP_ENV__Fault(soap, data, NULL, NULL) || soap_end_recv(soap) )

SOAP_FMAC3 struct SOAP_ENV__Fault * SOAP_FMAC4 soap_get_SOAP_ENV__Fault(struct soap*, struct SOAP_ENV__Fault *, const char*, const char*);

#define soap_new_SOAP_ENV__Fault(soap, n) soap_instantiate_SOAP_ENV__Fault(soap, n, NULL, NULL, NULL)


#define soap_delete_SOAP_ENV__Fault(soap, p) soap_delete(soap, p)

SOAP_FMAC1 struct SOAP_ENV__Fault * SOAP_FMAC2 soap_instantiate_SOAP_ENV__Fault(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_SOAP_ENV__Fault(struct soap*, int, int, void*, size_t, const void*, size_t);

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Reason
#define SOAP_TYPE_SOAP_ENV__Reason (25)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_SOAP_ENV__Reason(struct soap*, struct SOAP_ENV__Reason *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_SOAP_ENV__Reason(struct soap*, const struct SOAP_ENV__Reason *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_SOAP_ENV__Reason(struct soap*, const char*, int, const struct SOAP_ENV__Reason *, const char*);
SOAP_FMAC3 struct SOAP_ENV__Reason * SOAP_FMAC4 soap_in_SOAP_ENV__Reason(struct soap*, const char*, struct SOAP_ENV__Reason *, const char*);

#define soap_write_SOAP_ENV__Reason(soap, data) ( soap_begin_send(soap) || (soap_serialize_SOAP_ENV__Reason(soap, data), 0) || soap_put_SOAP_ENV__Reason(soap, data, NULL, NULL) || soap_end_send(soap) )


SOAP_FMAC3 int SOAP_FMAC4 soap_put_SOAP_ENV__Reason(struct soap*, const struct SOAP_ENV__Reason *, const char*, const char*);

#define soap_read_SOAP_ENV__Reason(soap, data) ( soap_begin_recv(soap) || !soap_get_SOAP_ENV__Reason(soap, data, NULL, NULL) || soap_end_recv(soap) )

SOAP_FMAC3 struct SOAP_ENV__Reason * SOAP_FMAC4 soap_get_SOAP_ENV__Reason(struct soap*, struct SOAP_ENV__Reason *, const char*, const char*);

#define soap_new_SOAP_ENV__Reason(soap, n) soap_instantiate_SOAP_ENV__Reason(soap, n, NULL, NULL, NULL)


#define soap_delete_SOAP_ENV__Reason(soap, p) soap_delete(soap, p)

SOAP_FMAC1 struct SOAP_ENV__Reason * SOAP_FMAC2 soap_instantiate_SOAP_ENV__Reason(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_SOAP_ENV__Reason(struct soap*, int, int, void*, size_t, const void*, size_t);

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Detail
#define SOAP_TYPE_SOAP_ENV__Detail (22)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_SOAP_ENV__Detail(struct soap*, struct SOAP_ENV__Detail *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_SOAP_ENV__Detail(struct soap*, const struct SOAP_ENV__Detail *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_SOAP_ENV__Detail(struct soap*, const char*, int, const struct SOAP_ENV__Detail *, const char*);
SOAP_FMAC3 struct SOAP_ENV__Detail * SOAP_FMAC4 soap_in_SOAP_ENV__Detail(struct soap*, const char*, struct SOAP_ENV__Detail *, const char*);

#define soap_write_SOAP_ENV__Detail(soap, data) ( soap_begin_send(soap) || (soap_serialize_SOAP_ENV__Detail(soap, data), 0) || soap_put_SOAP_ENV__Detail(soap, data, NULL, NULL) || soap_end_send(soap) )


SOAP_FMAC3 int SOAP_FMAC4 soap_put_SOAP_ENV__Detail(struct soap*, const struct SOAP_ENV__Detail *, const char*, const char*);

#define soap_read_SOAP_ENV__Detail(soap, data) ( soap_begin_recv(soap) || !soap_get_SOAP_ENV__Detail(soap, data, NULL, NULL) || soap_end_recv(soap) )

SOAP_FMAC3 struct SOAP_ENV__Detail * SOAP_FMAC4 soap_get_SOAP_ENV__Detail(struct soap*, struct SOAP_ENV__Detail *, const char*, const char*);

#define soap_new_SOAP_ENV__Detail(soap, n) soap_instantiate_SOAP_ENV__Detail(soap, n, NULL, NULL, NULL)


#define soap_delete_SOAP_ENV__Detail(soap, p) soap_delete(soap, p)

SOAP_FMAC1 struct SOAP_ENV__Detail * SOAP_FMAC2 soap_instantiate_SOAP_ENV__Detail(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_SOAP_ENV__Detail(struct soap*, int, int, void*, size_t, const void*, size_t);

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Code
#define SOAP_TYPE_SOAP_ENV__Code (20)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_SOAP_ENV__Code(struct soap*, struct SOAP_ENV__Code *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_SOAP_ENV__Code(struct soap*, const struct SOAP_ENV__Code *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_SOAP_ENV__Code(struct soap*, const char*, int, const struct SOAP_ENV__Code *, const char*);
SOAP_FMAC3 struct SOAP_ENV__Code * SOAP_FMAC4 soap_in_SOAP_ENV__Code(struct soap*, const char*, struct SOAP_ENV__Code *, const char*);

#define soap_write_SOAP_ENV__Code(soap, data) ( soap_begin_send(soap) || (soap_serialize_SOAP_ENV__Code(soap, data), 0) || soap_put_SOAP_ENV__Code(soap, data, NULL, NULL) || soap_end_send(soap) )


SOAP_FMAC3 int SOAP_FMAC4 soap_put_SOAP_ENV__Code(struct soap*, const struct SOAP_ENV__Code *, const char*, const char*);

#define soap_read_SOAP_ENV__Code(soap, data) ( soap_begin_recv(soap) || !soap_get_SOAP_ENV__Code(soap, data, NULL, NULL) || soap_end_recv(soap) )

SOAP_FMAC3 struct SOAP_ENV__Code * SOAP_FMAC4 soap_get_SOAP_ENV__Code(struct soap*, struct SOAP_ENV__Code *, const char*, const char*);

#define soap_new_SOAP_ENV__Code(soap, n) soap_instantiate_SOAP_ENV__Code(soap, n, NULL, NULL, NULL)


#define soap_delete_SOAP_ENV__Code(soap, p) soap_delete(soap, p)

SOAP_FMAC1 struct SOAP_ENV__Code * SOAP_FMAC2 soap_instantiate_SOAP_ENV__Code(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_SOAP_ENV__Code(struct soap*, int, int, void*, size_t, const void*, size_t);

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Header
#define SOAP_TYPE_SOAP_ENV__Header (19)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_SOAP_ENV__Header(struct soap*, struct SOAP_ENV__Header *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_SOAP_ENV__Header(struct soap*, const struct SOAP_ENV__Header *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_SOAP_ENV__Header(struct soap*, const char*, int, const struct SOAP_ENV__Header *, const char*);
SOAP_FMAC3 struct SOAP_ENV__Header * SOAP_FMAC4 soap_in_SOAP_ENV__Header(struct soap*, const char*, struct SOAP_ENV__Header *, const char*);

#define soap_write_SOAP_ENV__Header(soap, data) ( soap_begin_send(soap) || (soap_serialize_SOAP_ENV__Header(soap, data), 0) || soap_put_SOAP_ENV__Header(soap, data, NULL, NULL) || soap_end_send(soap) )


SOAP_FMAC3 int SOAP_FMAC4 soap_put_SOAP_ENV__Header(struct soap*, const struct SOAP_ENV__Header *, const char*, const char*);

#define soap_read_SOAP_ENV__Header(soap, data) ( soap_begin_recv(soap) || !soap_get_SOAP_ENV__Header(soap, data, NULL, NULL) || soap_end_recv(soap) )

SOAP_FMAC3 struct SOAP_ENV__Header * SOAP_FMAC4 soap_get_SOAP_ENV__Header(struct soap*, struct SOAP_ENV__Header *, const char*, const char*);

#define soap_new_SOAP_ENV__Header(soap, n) soap_instantiate_SOAP_ENV__Header(soap, n, NULL, NULL, NULL)


#define soap_delete_SOAP_ENV__Header(soap, p) soap_delete(soap, p)

SOAP_FMAC1 struct SOAP_ENV__Header * SOAP_FMAC2 soap_instantiate_SOAP_ENV__Header(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_SOAP_ENV__Header(struct soap*, int, int, void*, size_t, const void*, size_t);

#endif

#ifndef SOAP_TYPE_ns__Ipl1ChToMat
#define SOAP_TYPE_ns__Ipl1ChToMat (18)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_ns__Ipl1ChToMat(struct soap*, struct ns__Ipl1ChToMat *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_ns__Ipl1ChToMat(struct soap*, const struct ns__Ipl1ChToMat *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_ns__Ipl1ChToMat(struct soap*, const char*, int, const struct ns__Ipl1ChToMat *, const char*);
SOAP_FMAC3 struct ns__Ipl1ChToMat * SOAP_FMAC4 soap_in_ns__Ipl1ChToMat(struct soap*, const char*, struct ns__Ipl1ChToMat *, const char*);

#define soap_write_ns__Ipl1ChToMat(soap, data) ( soap_begin_send(soap) || (soap_serialize_ns__Ipl1ChToMat(soap, data), 0) || soap_put_ns__Ipl1ChToMat(soap, data, NULL, NULL) || soap_end_send(soap) )


SOAP_FMAC3 int SOAP_FMAC4 soap_put_ns__Ipl1ChToMat(struct soap*, const struct ns__Ipl1ChToMat *, const char*, const char*);

#define soap_read_ns__Ipl1ChToMat(soap, data) ( soap_begin_recv(soap) || !soap_get_ns__Ipl1ChToMat(soap, data, NULL, NULL) || soap_end_recv(soap) )

SOAP_FMAC3 struct ns__Ipl1ChToMat * SOAP_FMAC4 soap_get_ns__Ipl1ChToMat(struct soap*, struct ns__Ipl1ChToMat *, const char*, const char*);

#define soap_new_ns__Ipl1ChToMat(soap, n) soap_instantiate_ns__Ipl1ChToMat(soap, n, NULL, NULL, NULL)


#define soap_delete_ns__Ipl1ChToMat(soap, p) soap_delete(soap, p)

SOAP_FMAC1 struct ns__Ipl1ChToMat * SOAP_FMAC2 soap_instantiate_ns__Ipl1ChToMat(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_ns__Ipl1ChToMat(struct soap*, int, int, void*, size_t, const void*, size_t);

#ifndef SOAP_TYPE_ns__Ipl1ChToMatResponse
#define SOAP_TYPE_ns__Ipl1ChToMatResponse (17)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_ns__Ipl1ChToMatResponse(struct soap*, struct ns__Ipl1ChToMatResponse *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_ns__Ipl1ChToMatResponse(struct soap*, const struct ns__Ipl1ChToMatResponse *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_ns__Ipl1ChToMatResponse(struct soap*, const char*, int, const struct ns__Ipl1ChToMatResponse *, const char*);
SOAP_FMAC3 struct ns__Ipl1ChToMatResponse * SOAP_FMAC4 soap_in_ns__Ipl1ChToMatResponse(struct soap*, const char*, struct ns__Ipl1ChToMatResponse *, const char*);

#define soap_write_ns__Ipl1ChToMatResponse(soap, data) ( soap_begin_send(soap) || (soap_serialize_ns__Ipl1ChToMatResponse(soap, data), 0) || soap_put_ns__Ipl1ChToMatResponse(soap, data, NULL, NULL) || soap_end_send(soap) )


SOAP_FMAC3 int SOAP_FMAC4 soap_put_ns__Ipl1ChToMatResponse(struct soap*, const struct ns__Ipl1ChToMatResponse *, const char*, const char*);

#define soap_read_ns__Ipl1ChToMatResponse(soap, data) ( soap_begin_recv(soap) || !soap_get_ns__Ipl1ChToMatResponse(soap, data, NULL, NULL) || soap_end_recv(soap) )

SOAP_FMAC3 struct ns__Ipl1ChToMatResponse * SOAP_FMAC4 soap_get_ns__Ipl1ChToMatResponse(struct soap*, struct ns__Ipl1ChToMatResponse *, const char*, const char*);

#define soap_new_ns__Ipl1ChToMatResponse(soap, n) soap_instantiate_ns__Ipl1ChToMatResponse(soap, n, NULL, NULL, NULL)


#define soap_delete_ns__Ipl1ChToMatResponse(soap, p) soap_delete(soap, p)

SOAP_FMAC1 struct ns__Ipl1ChToMatResponse * SOAP_FMAC2 soap_instantiate_ns__Ipl1ChToMatResponse(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_ns__Ipl1ChToMatResponse(struct soap*, int, int, void*, size_t, const void*, size_t);

#ifndef SOAP_TYPE_ns__getImage
#define SOAP_TYPE_ns__getImage (14)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_ns__getImage(struct soap*, struct ns__getImage *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_ns__getImage(struct soap*, const struct ns__getImage *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_ns__getImage(struct soap*, const char*, int, const struct ns__getImage *, const char*);
SOAP_FMAC3 struct ns__getImage * SOAP_FMAC4 soap_in_ns__getImage(struct soap*, const char*, struct ns__getImage *, const char*);

#define soap_write_ns__getImage(soap, data) ( soap_begin_send(soap) || (soap_serialize_ns__getImage(soap, data), 0) || soap_put_ns__getImage(soap, data, NULL, NULL) || soap_end_send(soap) )


SOAP_FMAC3 int SOAP_FMAC4 soap_put_ns__getImage(struct soap*, const struct ns__getImage *, const char*, const char*);

#define soap_read_ns__getImage(soap, data) ( soap_begin_recv(soap) || !soap_get_ns__getImage(soap, data, NULL, NULL) || soap_end_recv(soap) )

SOAP_FMAC3 struct ns__getImage * SOAP_FMAC4 soap_get_ns__getImage(struct soap*, struct ns__getImage *, const char*, const char*);

#define soap_new_ns__getImage(soap, n) soap_instantiate_ns__getImage(soap, n, NULL, NULL, NULL)


#define soap_delete_ns__getImage(soap, p) soap_delete(soap, p)

SOAP_FMAC1 struct ns__getImage * SOAP_FMAC2 soap_instantiate_ns__getImage(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_ns__getImage(struct soap*, int, int, void*, size_t, const void*, size_t);

#ifndef SOAP_TYPE_ns__getImageResponse
#define SOAP_TYPE_ns__getImageResponse (13)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_ns__getImageResponse(struct soap*, struct ns__getImageResponse *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_ns__getImageResponse(struct soap*, const struct ns__getImageResponse *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_ns__getImageResponse(struct soap*, const char*, int, const struct ns__getImageResponse *, const char*);
SOAP_FMAC3 struct ns__getImageResponse * SOAP_FMAC4 soap_in_ns__getImageResponse(struct soap*, const char*, struct ns__getImageResponse *, const char*);

#define soap_write_ns__getImageResponse(soap, data) ( soap_begin_send(soap) || (soap_serialize_ns__getImageResponse(soap, data), 0) || soap_put_ns__getImageResponse(soap, data, NULL, NULL) || soap_end_send(soap) )


SOAP_FMAC3 int SOAP_FMAC4 soap_put_ns__getImageResponse(struct soap*, const struct ns__getImageResponse *, const char*, const char*);

#define soap_read_ns__getImageResponse(soap, data) ( soap_begin_recv(soap) || !soap_get_ns__getImageResponse(soap, data, NULL, NULL) || soap_end_recv(soap) )

SOAP_FMAC3 struct ns__getImageResponse * SOAP_FMAC4 soap_get_ns__getImageResponse(struct soap*, struct ns__getImageResponse *, const char*, const char*);

#define soap_new_ns__getImageResponse(soap, n) soap_instantiate_ns__getImageResponse(soap, n, NULL, NULL, NULL)


#define soap_delete_ns__getImageResponse(soap, p) soap_delete(soap, p)

SOAP_FMAC1 struct ns__getImageResponse * SOAP_FMAC2 soap_instantiate_ns__getImageResponse(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_ns__getImageResponse(struct soap*, int, int, void*, size_t, const void*, size_t);

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_PointerToSOAP_ENV__Reason
#define SOAP_TYPE_PointerToSOAP_ENV__Reason (28)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_PointerToSOAP_ENV__Reason(struct soap*, struct SOAP_ENV__Reason *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_PointerToSOAP_ENV__Reason(struct soap*, const char *, int, struct SOAP_ENV__Reason *const*, const char *);
SOAP_FMAC3 struct SOAP_ENV__Reason ** SOAP_FMAC4 soap_in_PointerToSOAP_ENV__Reason(struct soap*, const char*, struct SOAP_ENV__Reason **, const char*);

#define soap_write_PointerToSOAP_ENV__Reason(soap, data) ( soap_begin_send(soap) || (soap_serialize_PointerToSOAP_ENV__Reason(soap, data), 0) || soap_put_PointerToSOAP_ENV__Reason(soap, data, NULL, NULL) || soap_end_send(soap) )

SOAP_FMAC3 int SOAP_FMAC4 soap_put_PointerToSOAP_ENV__Reason(struct soap*, struct SOAP_ENV__Reason *const*, const char*, const char*);

#define soap_read_PointerToSOAP_ENV__Reason(soap, data) ( soap_begin_recv(soap) || !soap_get_PointerToSOAP_ENV__Reason(soap, data, NULL, NULL) || soap_end_recv(soap) )

SOAP_FMAC3 struct SOAP_ENV__Reason ** SOAP_FMAC4 soap_get_PointerToSOAP_ENV__Reason(struct soap*, struct SOAP_ENV__Reason **, const char*, const char*);

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_PointerToSOAP_ENV__Detail
#define SOAP_TYPE_PointerToSOAP_ENV__Detail (27)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_PointerToSOAP_ENV__Detail(struct soap*, struct SOAP_ENV__Detail *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_PointerToSOAP_ENV__Detail(struct soap*, const char *, int, struct SOAP_ENV__Detail *const*, const char *);
SOAP_FMAC3 struct SOAP_ENV__Detail ** SOAP_FMAC4 soap_in_PointerToSOAP_ENV__Detail(struct soap*, const char*, struct SOAP_ENV__Detail **, const char*);

#define soap_write_PointerToSOAP_ENV__Detail(soap, data) ( soap_begin_send(soap) || (soap_serialize_PointerToSOAP_ENV__Detail(soap, data), 0) || soap_put_PointerToSOAP_ENV__Detail(soap, data, NULL, NULL) || soap_end_send(soap) )

SOAP_FMAC3 int SOAP_FMAC4 soap_put_PointerToSOAP_ENV__Detail(struct soap*, struct SOAP_ENV__Detail *const*, const char*, const char*);

#define soap_read_PointerToSOAP_ENV__Detail(soap, data) ( soap_begin_recv(soap) || !soap_get_PointerToSOAP_ENV__Detail(soap, data, NULL, NULL) || soap_end_recv(soap) )

SOAP_FMAC3 struct SOAP_ENV__Detail ** SOAP_FMAC4 soap_get_PointerToSOAP_ENV__Detail(struct soap*, struct SOAP_ENV__Detail **, const char*, const char*);

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_PointerToSOAP_ENV__Code
#define SOAP_TYPE_PointerToSOAP_ENV__Code (21)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_PointerToSOAP_ENV__Code(struct soap*, struct SOAP_ENV__Code *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_PointerToSOAP_ENV__Code(struct soap*, const char *, int, struct SOAP_ENV__Code *const*, const char *);
SOAP_FMAC3 struct SOAP_ENV__Code ** SOAP_FMAC4 soap_in_PointerToSOAP_ENV__Code(struct soap*, const char*, struct SOAP_ENV__Code **, const char*);

#define soap_write_PointerToSOAP_ENV__Code(soap, data) ( soap_begin_send(soap) || (soap_serialize_PointerToSOAP_ENV__Code(soap, data), 0) || soap_put_PointerToSOAP_ENV__Code(soap, data, NULL, NULL) || soap_end_send(soap) )

SOAP_FMAC3 int SOAP_FMAC4 soap_put_PointerToSOAP_ENV__Code(struct soap*, struct SOAP_ENV__Code *const*, const char*, const char*);

#define soap_read_PointerToSOAP_ENV__Code(soap, data) ( soap_begin_recv(soap) || !soap_get_PointerToSOAP_ENV__Code(soap, data, NULL, NULL) || soap_end_recv(soap) )

SOAP_FMAC3 struct SOAP_ENV__Code ** SOAP_FMAC4 soap_get_PointerToSOAP_ENV__Code(struct soap*, struct SOAP_ENV__Code **, const char*, const char*);

#endif

#ifndef SOAP_TYPE_PointerTounsignedByte
#define SOAP_TYPE_PointerTounsignedByte (10)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_PointerTounsignedByte(struct soap*, unsigned char *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_PointerTounsignedByte(struct soap*, const char *, int, unsigned char *const*, const char *);
SOAP_FMAC3 unsigned char ** SOAP_FMAC4 soap_in_PointerTounsignedByte(struct soap*, const char*, unsigned char **, const char*);

#define soap_write_PointerTounsignedByte(soap, data) ( soap_begin_send(soap) || (soap_serialize_PointerTounsignedByte(soap, data), 0) || soap_put_PointerTounsignedByte(soap, data, NULL, NULL) || soap_end_send(soap) )

SOAP_FMAC3 int SOAP_FMAC4 soap_put_PointerTounsignedByte(struct soap*, unsigned char *const*, const char*, const char*);

#define soap_read_PointerTounsignedByte(soap, data) ( soap_begin_recv(soap) || !soap_get_PointerTounsignedByte(soap, data, NULL, NULL) || soap_end_recv(soap) )

SOAP_FMAC3 unsigned char ** SOAP_FMAC4 soap_get_PointerTounsignedByte(struct soap*, unsigned char **, const char*, const char*);

#ifndef SOAP_TYPE__QName
#define SOAP_TYPE__QName (5)
#endif

#define soap_default__QName(soap, a) soap_default_string(soap, a)


#define soap_serialize__QName(soap, a) soap_serialize_string(soap, a)

SOAP_FMAC3 int SOAP_FMAC4 soap_out__QName(struct soap*, const char*, int, char*const*, const char*);
SOAP_FMAC3 char * * SOAP_FMAC4 soap_in__QName(struct soap*, const char*, char **, const char*);

#define soap_write__QName(soap, data) ( soap_begin_send(soap) || (soap_serialize__QName(soap, data), 0) || soap_put__QName(soap, data, NULL, NULL) || soap_end_send(soap) )

SOAP_FMAC3 int SOAP_FMAC4 soap_put__QName(struct soap*, char *const*, const char*, const char*);

#define soap_read__QName(soap, data) ( soap_begin_recv(soap) || !soap_get__QName(soap, data, NULL, NULL) || soap_end_recv(soap) )

SOAP_FMAC3 char ** SOAP_FMAC4 soap_get__QName(struct soap*, char **, const char*, const char*);

#ifndef SOAP_TYPE_string
#define SOAP_TYPE_string (4)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_string(struct soap*, char **);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_string(struct soap*, char *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_string(struct soap*, const char*, int, char*const*, const char*);
SOAP_FMAC3 char * * SOAP_FMAC4 soap_in_string(struct soap*, const char*, char **, const char*);

#define soap_write_string(soap, data) ( soap_begin_send(soap) || (soap_serialize_string(soap, data), 0) || soap_put_string(soap, data, NULL, NULL) || soap_end_send(soap) )

SOAP_FMAC3 int SOAP_FMAC4 soap_put_string(struct soap*, char *const*, const char*, const char*);

#define soap_read_string(soap, data) ( soap_begin_recv(soap) || !soap_get_string(soap, data, NULL, NULL) || soap_end_recv(soap) )

SOAP_FMAC3 char ** SOAP_FMAC4 soap_get_string(struct soap*, char **, const char*, const char*);

#endif

/* End of soapH.h */
