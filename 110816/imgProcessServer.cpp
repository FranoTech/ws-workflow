//แตกมาจาก 110729 with tmpfs
// เปลี่ยนกลับมาใช้การ save เป็น jpg

#include "soapH.h"
#include "imgProcess.nsmap"
#include <iostream>
#include "cv.h"
#include "highgui.h"
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <time.h>
#include <string.h>
#include <cstring>

//init variable
#define BASE_DIR "/home/lluu/dir/"
#define LOGNAME_SIZE 60
#define int64 long long
using namespace std;
static timeval start_time, t;


//function
void init_time();
void get_time(char);
//void get_Filename(char*&); 


int main(int argc, char **argv)
{ 
    struct soap soap;
    soap_init(&soap);
    if (argc < 2)		// no args: assume this is a CGI application
    { 
        soap_serve(&soap);	// serve request
        soap_destroy(&soap);// cleanup class instances
        soap_end(&soap);	// cleanup
    }
    return 0;
}

void init_time() {
    gettimeofday(&start_time, NULL);
    time_t init = time(0);
    tm* tm = localtime(&init);
    cerr<<"***Time :"<<1900+tm->tm_year<<'-'<<1+tm->tm_mon<<'-'<<tm->tm_mday<<" "<<tm->tm_hour<<':'<<tm->tm_min<<"***"<<endl;
}

void get_time(char *msg) {
    timeval t;
    gettimeofday(&t, NULL);
    cerr<<(int64) (t.tv_sec - start_time.tv_sec) + (t.tv_usec -start_time.tv_usec)/1000000.0<<" "<<msg;
}

int ns__getImage(struct soap *soap, char *name, ns__ImageData &image)
{ 
    init_time();
    cerr<<"getImage started"<<endl;
    if(name)
    { 
        // load image from directory
        FILE *fd = fopen(name, "r");
        if(fd!=NULL){
            fseek(fd,0,SEEK_END); // seek to end of file
            int size = ftell(fd); // get current file pointer
            fseek(fd, 0, SEEK_SET); // seek back to beginning of file

            image.__ptr = (unsigned char*)soap_malloc(soap, size);
            int i, c;
            for (i = 0; i < size; i++)
            { 
                if ((c = fgetc(fd)) == EOF)
                break;
                image.__ptr[i] = c;
            }
            image.__size = i;
        } else {
            soap_fault(soap);
            cerr<<"Can not read file"<<endl;
            soap->fault->faultstring = "Cannot read file";
            return SOAP_FAULT;
        }
        get_time("sent output to taverna client\n");
        
    }
    else
    { 
    cerr<<"Name require"<<endl;
    soap_fault(soap);
    soap->fault->faultstring = "Name required";
    return SOAP_FAULT;
    }
    return SOAP_OK;
}


int ns__Ipl1ChToMat(struct soap *soap, char *InputFilename, char *&OutputFilename) // can't change image solution
{ 
    gettimeofday(&start_time, NULL);
    if(InputFilename)
    { 
        // load image from directory
        IplImage* src = cvLoadImage(InputFilename,CV_LOAD_IMAGE_GRAYSCALE);
        if (!src)
        { 	
            soap_fault(soap);
            cerr<<"Ipl1ChToMat::Can not open image file"<<endl;
            soap->fault->faultstring = "Ipl1ChToMat::Cannot open image file";
            return SOAP_FAULT;
        }
    
        CvMat *output1Ch = cvCreateMat(src->height, src->width, CV_32FC1);
        cvConvertScale(src, output1Ch);
        
        //preparing filename to save
		ostringstream sout;
        time_t init = time(0);
        tm* tm = localtime(&init);
        sout<<BASE_DIR<<1900+tm->tm_year<<1+tm->tm_mon<<tm->tm_mday<<tm->tm_hour<<tm->tm_min<<":Ipl1ChToMat.xml";
        size_t len = sout.str().length();
		OutputFilename = new char[len+1];
        memcpy(OutputFilename,sout.str().c_str(),len);
        
        cvSave(OutputFilename, output1Ch);
        if(!OutputFilename)
        { 	
            soap_fault(soap);
            cerr<<"Ipl1ChToMat::Can not save to new image"<<endl;
            soap->fault->faultstring = "Ipl1ChToMat::Can not save to new image";
            return SOAP_FAULT;
        }
        
        cvReleaseImage(&src);
        cvReleaseMat(&output1Ch);

        gettimeofday(&t, NULL);
		cerr<<(int64) (t.tv_sec - start_time.tv_sec) + (t.tv_usec -start_time.tv_usec)/1000000.0<<" secs ::Ipl1ChToMat"<<endl;
        
    }
    else
    { 
        cerr<<"Ipl1ChToMat::File Name require"<<endl;
        soap_fault(soap);
        soap->fault->faultstring = "Ipl1ChToMat:: filename required";
        return SOAP_FAULT;
    }
    return SOAP_OK;
}


int ns__MatToJPG(struct soap *soap, char *InputFilename, char *&OutputFilename)
{ 
    gettimeofday(&start_time, NULL);
    if(InputFilename)
    { 
        
        CvMat* output1Ch;
        output1Ch = (CvMat*)cvLoad(InputFilename);
        
        if (!output1Ch)
        { 	
            soap_fault(soap);
            cerr<<"MatToIpl1Ch::Can not open image file"<<endl;
            soap->fault->faultstring = "MatToIpl1Ch::Can not open image file";
            return SOAP_FAULT;
        }
        IplImage *tmp8UC1 = cvCreateImage(cvGetSize(output1Ch), IPL_DEPTH_8U, 1);
        cvConvert(output1Ch, tmp8UC1);
        
        ostringstream sout;
        time_t init = time(0);
        tm* tm = localtime(&init);
        sout<<BASE_DIR<<1900+tm->tm_year<<1+tm->tm_mon<<tm->tm_mday<<tm->tm_hour<<tm->tm_min<<":MatToIpl1Ch.jpg";
        size_t len = sout.str().length();
		OutputFilename = new char[len+1];
        memcpy(OutputFilename,sout.str().c_str(),len);
        
        cvSaveImage(OutputFilename, tmp8UC1);
        if(!OutputFilename)
        { 	
            soap_fault(soap);
            cerr<<"MatToIpl1Ch::Can not save to new image"<<endl;
            soap->fault->faultstring = "MatToIpl1Ch::Can not save to new image";
            return SOAP_FAULT;
        }
        
        cvReleaseImage(&tmp8UC1);
        cvReleaseMat(&output1Ch);
        
        gettimeofday(&t, NULL);
		cerr<<(int64) (t.tv_sec - start_time.tv_sec) + (t.tv_usec -start_time.tv_usec)/1000000.0<<" secs ::MatToJPG"<<endl;

  }
  else
  { 
    cerr<<"MatToIpl1Ch::File Name require"<<endl;
    soap_fault(soap);
    soap->fault->faultstring = "MatToIpl1Ch::Name required";
    return SOAP_FAULT;
  }
  return SOAP_OK;
}


int ns__BinaryThreshold(struct soap *soap, char *InputFilename, 
                        double threshold, double maxValue, char *&OutputFilename)
{ 
    gettimeofday(&start_time, NULL);
    if(InputFilename)
    { 
        // load image from directory
        //CvMat* src1Ch;
        //src1Ch = (CvMat*)cvLoad(InputFilename);
        
		IplImage* src = cvLoadImage(InputFilename,CV_LOAD_IMAGE_GRAYSCALE);
        if (!src)
        { 	
            soap_fault(soap);
            cerr<<"Ipl1ChToMat::Can not open image file"<<endl;
            soap->fault->faultstring = "Ipl1ChToMat::Cannot open image file";
            return SOAP_FAULT;
        }
    
        CvMat *src1Ch = cvCreateMat(src->height, src->width, CV_32FC1);
        cvConvertScale(src, src1Ch);
    
        CvMat *matThreshold = cvCreateMat(src1Ch->height, src1Ch->width, CV_32FC1);
        cvThreshold(src1Ch, matThreshold, threshold, maxValue, CV_THRESH_BINARY);
        
        *&OutputFilename = (char*)soap_malloc(soap, 60);
        time_t now = time(0);
        strftime(OutputFilename, sizeof(OutputFilename)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_bi_threshold.jpg", localtime(&now));
		
		cvSetZero(src);
		cvConvert(matThreshold, src);
        
		cvSaveImage(OutputFilename, src);
        if(!OutputFilename)
        { 	
            soap_fault(soap);
            cerr<<"MatToIpl1Ch::Can not save to new image"<<endl;
            soap->fault->faultstring = "MatToIpl1Ch::Can not save to new image";
            return SOAP_FAULT;
        }
        
        cvReleaseImage(&src);
        cvReleaseMat(&src1Ch);
        cvReleaseMat(&matThreshold);
        
        gettimeofday(&t, NULL);
		cerr<<(int64) (t.tv_sec - start_time.tv_sec) + (t.tv_usec -start_time.tv_usec)/1000000.0<<" secs ::BinaryThreshold"<<endl;
        
    }
    else
    { 
        cerr<<"File Name require"<<endl;
        soap_fault(soap);
        soap->fault->faultstring = "Name required";
        return SOAP_FAULT;
    }
    return SOAP_OK;
}




int ns__MorphOpen(  struct soap *soap, char *InputFilename, char *&OutputFilename)
{ 
    if(InputFilename)
    { 
        IplImage* src = cvLoadImage(InputFilename,CV_LOAD_IMAGE_GRAYSCALE);
        if (!src)
        { 	
            soap_fault(soap);
            cerr<<"Ipl1ChToMat::Can not open image file"<<endl;
            soap->fault->faultstring = "Ipl1ChToMat::Cannot open image file";
            return SOAP_FAULT;
        }
		CvMat *input_morph = cvCreateMat(src->height, src->width, CV_32FC1);
        cvConvertScale(src, input_morph);
        
        IplConvKernel *se1 = cvCreateStructuringElementEx(3, 3, 1, 1, CV_SHAPE_ELLIPSE);
        cvMorphologyEx(input_morph, input_morph, NULL, se1, CV_MOP_OPEN);
        
        *&OutputFilename = (char*)soap_malloc(soap, 60);
        time_t now = time(0);
        strftime(OutputFilename, sizeof(OutputFilename)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_morp_open.jpg", localtime(&now));
        
		cvSetZero(src);
		cvConvert(input_morph, src);
        
		cvSaveImage(OutputFilename, src);
        if(!OutputFilename)
        { 	
            soap_fault(soap);
            cerr<<"MatToIpl1Ch::Can not save to new image"<<endl;
            soap->fault->faultstring = "MatToIpl1Ch::Can not save to new image";
            return SOAP_FAULT;
        }
        
        cvReleaseMat(&input_morph);
        cvReleaseImage(&src);
        //cvReleaseMat(&src1Ch);
        
        gettimeofday(&t, NULL);
		cerr<<(int64) (t.tv_sec - start_time.tv_sec) + (t.tv_usec -start_time.tv_usec)/1000000.0<<" secs ::MorphOpen"<<endl;

    }
    else
    { 
        cerr<<"File Name require"<<endl;
        soap_fault(soap);
        soap->fault->faultstring = "Name required";
        return SOAP_FAULT;
    }
    return SOAP_OK;
}



//hadn't finished yet

int ns__RemoveSmallCell(  struct soap *soap, char *InputFilename, float discard_area, float large_area, char *&OutputFilename)
{ 
    if(InputFilename)
    { 
        // load image from directory
        //CvMat* input_morph;
        //input_morph = (CvMat*)cvLoad(InputFilename);
        
        IplImage* src8UC1 = cvLoadImage(InputFilename,CV_LOAD_IMAGE_GRAYSCALE);
        if (!src8UC1)
        { 	
            soap_fault(soap);
            cerr<<"RemoveSmallCell::Can not open image file"<<endl;
            soap->fault->faultstring = "RemoveSmallCell::Cannot open image file";
            return SOAP_FAULT;
        }
        
        CvMat *in_tmp = cvCreateMat(src8UC1->height, src8UC1->width, CV_32FC1);
        cvConvertScale(src, in_tmp);
        CvMat *out_tmp = cvCreateMat(src8UC1->height, src8UC1->width, CV_32FC1);
        cvSetZero(out_tmp);
        
        cvFindContours(src8UC1, storage, &first_con, sizeof(CvContour), CV_RETR_EXTERNAL);
        CvSeq *first_con = nullptr;
        CvSeq *cur = nullptr;
		cur = first_con;
		while (cur != nullptr) {
			double area = fabs(cvContourArea(cur));
			int npts = cur->total;
			CvPoint *p = new CvPoint[npts];
			cvCvtSeqToArray(cur, p);
			if (area < discard_area) // remove small area 1500.0
				cvFillPoly(in_tmp, &p, &npts, 1, cvScalar(0.0)); // remove from input
			else if (area < large_area) { // 7500.0
				cvFillPoly(out_tmp, &p, &npts, 1, cvScalar(255.0)); // move to single
				cvFillPoly(in_tmp, &p, &npts, 1, cvScalar(0.0)); // remove from input
			}else
				cvFillPoly(in_tmp, &p, &npts, 1, cvScalar(255.0)); // fill hole
			delete[] p;
			cur = cur->h_next;
		}
        CvMat *output_morph = cvCreateMat(input_morph->height, input_morph->width, CV_32FC1);
		cvOr(in_tmp, out_single, output_morph);
		cvReleaseStructuringElement(&se1);
        
        *&OutputFilename = (char*)soap_malloc(soap, 60);
        time_t now = time(0);
        strftime(OutputFilename, sizeof(OutputFilename)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_morp_open.jpg", localtime(&now));
        
        cvSetZero(src);
		cvConvert(input_morph, src);
        
		cvSaveImage(OutputFilename, src);
        if(!OutputFilename)
        { 	
            soap_fault(soap);
            cerr<<"MatToIpl1Ch::Can not save to new image"<<endl;
            soap->fault->faultstring = "MatToIpl1Ch::Can not save to new image";
            return SOAP_FAULT;
        }
        
        cvReleaseMat(&input_morph);
        cvReleaseImage(&src);
        //cvReleaseMat(&src1Ch);
        
        gettimeofday(&t, NULL);
		cerr<<(int64) (t.tv_sec - start_time.tv_sec) + (t.tv_usec -start_time.tv_usec)/1000000.0<<" secs ::MorphOpen"<<endl;

    }
    else
    { 
        cerr<<"File Name require"<<endl;
        soap_fault(soap);
        soap->fault->faultstring = "Name required";
        return SOAP_FAULT;
    }
    return SOAP_OK;
}



int ns__ScanCell(  struct soap *soap, char *InputFilename, char *&OutputFilename)
{ 
    if(InputFilename)
    { 
        IplImage* src = cvLoadImage(InputFilename,CV_LOAD_IMAGE_GRAYSCALE);
        if (!src)
        { 	
            soap_fault(soap);
            cerr<<"Ipl1ChToMat::Can not open image file"<<endl;
            soap->fault->faultstring = "Ipl1ChToMat::Cannot open image file";
            return SOAP_FAULT;
        }
		CvMat *input_morph = cvCreateMat(src->height, src->width, CV_32FC1);
        cvConvertScale(src, input_morph);
        
        IplConvKernel *se1 = cvCreateStructuringElementEx(3, 3, 1, 1, CV_SHAPE_ELLIPSE);
        cvMorphologyEx(input_morph, input_morph, NULL, se1, CV_MOP_OPEN);
        
        *&OutputFilename = (char*)soap_malloc(soap, 60);
        time_t now = time(0);
        strftime(OutputFilename, sizeof(OutputFilename)*60, "/home/lluu/dir/%Y%m%d_%H%M%S_morp_open.jpg", localtime(&now));
        
		cvSetZero(src);
		cvConvert(input_morph, src);
        
		cvSaveImage(OutputFilename, src);
        if(!OutputFilename)
        { 	
            soap_fault(soap);
            cerr<<"MatToIpl1Ch::Can not save to new image"<<endl;
            soap->fault->faultstring = "MatToIpl1Ch::Can not save to new image";
            return SOAP_FAULT;
        }
        
        cvReleaseMat(&input_morph);
        cvReleaseImage(&src);
        //cvReleaseMat(&src1Ch);
        
        gettimeofday(&t, NULL);
		cerr<<(int64) (t.tv_sec - start_time.tv_sec) + (t.tv_usec -start_time.tv_usec)/1000000.0<<" secs ::MorphOpen"<<endl;

    }
    else
    { 
        cerr<<"File Name require"<<endl;
        soap_fault(soap);
        soap->fault->faultstring = "Name required";
        return SOAP_FAULT;
    }
    return SOAP_OK;
}

