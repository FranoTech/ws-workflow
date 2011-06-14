// แตกมาจาก 060111
// แยกฟังก์ชันแล้ว
// src1Ch = source image/mat 1Ch
// output1Ch = output mat 1Ch

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
#define int64 long long
using namespace std;
static timeval start_time;


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
    cerr<<"******Start Time :"<<1900+tm->tm_year<<'-'<<1+tm->tm_mon<<'-'<<tm->tm_mday<<' time'<<tm->tm_hour<<':'<<tm->tm_min<<"******"<<endl;
}

void get_time(char *msg) {
    timeval t;
    gettimeofday(&t, NULL);
    cerr<<(int64) (t.tv_sec - start_time.tv_sec) + (t.tv_usec -start_time.tv_usec)/1000000.0<<" "<<msg;
}

int ns__getImage(struct soap *soap, char *name, ns__ImageData &image)
{ 
    init_time();
    cerr<<"imgProcessServer started\n"<<endl;
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
        get_time("Readed out to taverna client\n");
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


int ns__Ipl1ChToMat(struct soap *soap, char *InputFilename, 
                    char *filename, char *&OutputFilename) 
// can't change image solution
{ 
    init_time();
    cerr<<"imgProcessServer started\n"<<endl;
    if(InputFilename)
    { 
        // load image from directory
        IplImage* src = cvLoadImage(InputFilename,CV_LOAD_IMAGE_GRAYSCALE);
        if (!src)
        { 	
            soap_fault(soap);
            cerr<<"Can not open image file"<<endl;
            soap->fault->faultstring = "Cannot open image file";
            return SOAP_FAULT;
        }
    
        CvMat *output1Ch = cvCreateMat(src->height, src->width, CV_32FC1);
        cvConvertScale(src, output1Ch);
        cvSave(filename,output1Ch);
    
        if(!filename)
        { 	
            soap_fault(soap);
            cerr<<"Can not save to mat"<<endl;
            soap->fault->faultstring = "Cannot save to mat";
            return SOAP_FAULT;
        }
        cvReleaseImage(&src); 
        cvReleaseMat(&output1Ch);

        OutputFilename = new char[strlen(filename)+1];
        memcpy(OutputFilename,filename,strlen(filename)+1);
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


int ns__MatToIpl1Ch(struct soap *soap, char *InputFilename, 
                    char *filename, char *&OutputFilename)
{ 
    init_time();
    cerr<<"imgProcessServer started\n"<<endl;
    if(InputFilename)
    { 
        
        CvMat* output1Ch;
        output1Ch = (CvMat*)cvLoad(filename);
        
        if (!output1Ch)
        { 	
            soap_fault(soap);
            cerr<<"Can not open image file"<<endl;
            soap->fault->faultstring = "Cannot open image file";
            return SOAP_FAULT;
        }
        IplImage *tmp8UC1 = cvCreateImage(cvGetSize(output1Ch), IPL_DEPTH_8U, 1);
        cvConvert(output1Ch, tmp8UC1);
        cvSave(filename,tmp8UC1);
        
        if(!filename)
        { 	
            soap_fault(soap);
            cerr<<"Can not save to new image"<<endl;
            soap->fault->faultstring = "Cannot save to new image";
            return SOAP_FAULT;
        }
        
        if(!cvSaveImage(filename, tmp8UC1))
        { 	
            soap_fault(soap);
            cerr<<"Can not save to new image"<<endl;
            soap->fault->faultstring = "Cannot save to new image";
            return SOAP_FAULT;
        }
        
        cvReleaseImage(&tmp8UC1);

        OutputFilename = new char[strlen(filename)+1];
        memcpy(OutputFilename,filename,strlen(filename)+1);
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


int ns__BinaryThreshold(struct soap *soap, char *InputFilename, 
                        double threshold, double maxValue, 
                        char *filename, char *&OutputFilename)
{ 
    init_time();
    cerr<<"imgProcessServer started\n"<<endl;
    if(InputFilename)
    { 
        // load image from directory
        CvMat* src1Ch;
        src1Ch = (CvMat*)cvLoad(InputFileName);
        if (!src1Ch)
        { 	
            soap_fault(soap);
            cerr<<"Can not open image file"<<endl;
            soap->fault->faultstring = "Cannot open image file";
            return SOAP_FAULT;
        }
    
        CvMat *matThreshold = cvCreateMat(src1Ch->height, src1Ch->width, CV_32FC1);
        cvThreshold(src1Ch, matThreshold, threshold, maxValue, CV_THRESH_BINARY);
        cvSave(filename,matThreshold);
    
        if(!filename)
        { 	
            soap_fault(soap);
            cerr<<"Can not save to mat"<<endl;
            soap->fault->faultstring = "Cannot save to mat";
            return SOAP_FAULT;
        }
        cvReleaseImage(&src1Ch);
        cvReleaseMat(&matThreshold);

        OutputFilename = new char[strlen(filename)+1];
        memcpy(OutputFilename,filename,strlen(filename)+1);
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




int ns__Morph(  struct soap *soap, char *InputFilename, 
                char *filename, char *&OutputFilename)
{ 
    init_time();
    cerr<<"imgProcessServer started\n"<<endl;
    if(InputFilename)
    { 
        // load image from directory
        CvMat* input_morph;
        input_morph = (CvMat*)cvLoad(InputFileName);
        if (!input_morph)
        { 	
            soap_fault(soap);
            cerr<<"Can not open image file"<<endl;
            soap->fault->faultstring = "Cannot open image file";
            return SOAP_FAULT;
        }
    
        IplConvKernel *se1 = cvCreateStructuringElementEx(3, 3, 1, 1, CV_SHAPE_ELLIPSE);
        cvMorphologyEx(input_morph, input_morph, NULL, se1, CV_MOP_OPEN);
        
        cvSave(filename,input_morph);
        if(!filename)
        { 	
            soap_fault(soap);
            cerr<<"Can not save to mat"<<endl;
            soap->fault->faultstring = "Cannot save to mat";
            return SOAP_FAULT;
        }
        
        cvReleaseMat(&input_morph);

        OutputFilename = new char[strlen(filename)+1];
        memcpy(OutputFilename,filename,strlen(filename)+1);
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

//new adding 19/5/54
// removed input filename
int ns__FindContours(	struct soap *soap, char *InputFilename, 
						char *&OutputFilename)
{

}

//convert mat(xml) to ipl
//fixing output channel, good or bad ?
int ns__ConvertFromMatToIpl8UC1(  	struct soap *soap, char *InputFilename, 
					char *&OutputFilename)
{
	init_time();
    if(InputFilename)
    { 
        // load image from directory
        CvMat* src;
        src = (CvMat*)cvLoad(InputFileName);
        if (!src)
        { 	
            soap_fault(soap);
            cerr<<"Can not open image file"<<endl;
            soap->fault->faultstring = "Cannot open file";
            return SOAP_FAULT;
        }
// do anything
        
        IplImage *dst8UC1 = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
        cvConvert(src, dst8UC1);

// end  

        //preparing filename to save
        ostringstream sout;
        char* filename;
        time_t init = time(0);
        tm* tm = localtime(&init);
        sout<<1900+tm->tm_year<<1+tm->tm_mon<<tm->tm_mday<<tm->tm_hour<<tm->tm_min<<"ConvertFromMatToIpl8UC1"<<<<".xml";
        filename = sout.str();
        
        //save result
        cvSave(filename,dst8UC1);
        if(!filename)
        { 	
            soap_fault(soap);
            cerr<<"Can not save to mat"<<endl;
            soap->fault->faultstring = "Cannot save to mat";
            return SOAP_FAULT;
        }
        
        cvReleaseMat(&input_morph);

        OutputFilename = new char[strlen(filename)+1];
        memcpy(OutputFilename,filename,strlen(filename)+1);
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


//convert from ipl(xml) to mat 32FC1
int ns__ConvertFromIplToMat32FC1(  	struct soap *soap, char *InputFilename, 
					char *&OutputFilename)
{
	init_time();
    if(InputFilename)
    { 
        // load image from directory
        IplImage *src;
        src = (IplImage*)cvLoad(InputFileName);
        if (!src)
        { 	
            soap_fault(soap);
            cerr<<"Can not open image file"<<endl;
            soap->fault->faultstring = "Cannot open file";
            return SOAP_FAULT;
        }
// do anything
        
        IplImage *dst32FC1 = cvCreateMat(src->height, src->width, CV_32FC1);
        cvConvertScale(src,dst32FC1);

// end  

        //preparing filename to save
        ostringstream sout;
        char* filename;
        time_t init = time(0);
        tm* tm = localtime(&init);
        sout<<1900+tm->tm_year<<1+tm->tm_mon<<tm->tm_mday<<tm->tm_hour
			<<tm->tm_min<<"ConvertFromIplToMat32FC1"<<<<".xml";
        filename = sout.str();
        
        //save result
        cvSave(filename,dst8UC1);
        if(!filename)
        { 	
            soap_fault(soap);
            cerr<<"Can not save to mat"<<endl;
            soap->fault->faultstring = "Cannot save to mat";
            return SOAP_FAULT;
        }
        
        cvReleaseMat(&input_morph);

        OutputFilename = new char[strlen(filename)+1];
        memcpy(OutputFilename,filename,strlen(filename)+1);
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

