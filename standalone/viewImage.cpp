
int ns__viewImage(  struct soap *soap, 
                    char *inputMatFilename, 
                    ns__base64Binary &image)
{
    double start, end;
    start = omp_get_wtime();

    Mat src;
    if(!readMat(inputMatFilename, src))
    {
        cerr << "viewImage:: can not read bin file" << endl;
        return soap_receiver_fault(soap, "viewImage:: can not read bin file", NULL);
    }

    /* check if it is not 8U then convert to 8UC(n) */
    int chan = src.channels();
    if( src.type() != 0 || src.type() != 8 || src.type() != 16 )
    {
       src.convertTo(src, CV_8UC(chan));
    }

    if(!imwrite( BASE_DIR"output.jpg", src))
    {
        cerr<< "viewImage:: can not save mat to jpg file" << endl;
    }

    FILE *fd = fopen( BASE_DIR"output.jpg", "r");
    if(fd){
        int i =0, c = 0;
        fseek(fd,0,SEEK_END); // seek to end of file
        int size = ftell(fd); // get current file pointer
        fseek(fd, 0, SEEK_SET); // seek back to beginning of file
        
        image.__ptr = (unsigned char*)soap_malloc(soap, size);
        for (i = 0; i < size; i++)
        { if ((c = fgetc(fd)) == EOF)
            break;
          image.__ptr[i] = c;
        }
        image.__size = i;
    } else {
        cerr<<"viewImage:: image file read error"<<endl;
    }
    
    return SOAP_OK;
}

