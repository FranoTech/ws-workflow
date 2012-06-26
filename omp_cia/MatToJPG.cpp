//
// name: MatToJPG
// - convert nat to 8U and save as JPG
// @param char *InputMatFilename
// @return char **OutputMatFilename

int ns__MatToJPG (struct soap *soap, char *InputMatFilename, char **OutputMatFilename)
{
    double start, end;
    start = omp_get_wtime();

    Mat src;

    /* check if it is not 8U then convert to 8UC(n) */
    int chan = src.channels();
    if( src.type() != 0 || src.type() != 8 || src.type() != 16 )
    {
       src.convertTo(src, CV_8UC(chan));
    }

    /* generate output file name */
	*OutputMatFilename = (char*)soap_malloc(soap, FILENAME_SIZE);
    getOutputFilename(OutputMatFilename,".jpg");

    if(!imwrite(*OutputMatFilename, src))
    {
        cerr<< "MatToJPG:: can not save mat to jpg file" << endl;
        return soap_receiver_fault(soap, "MatToJPG:: can not save mat to jpg file", NULL);
    }

    src.release();

    end = omp_get_wtime();
    cerr<<"ns__MatToJPG "<<"time elapsed "<<end-start<<endl;

    return SOAP_OK;
}
