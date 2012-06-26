
/* Load image data to Mat, save to binary file */
int ns__loadMat (struct soap *soap,
                char *InputImageFilename,
                int colorflag=0,
                char *types="CV_32FC1",
                char **OutputMatFilename=NULL)
{
    double start, end;
    start = omp_get_wtime();

    Mat src;

    /* load image data */
    src = imread(InputImageFilename,getColorFlag(colorflag));
    if(src.empty()) {
        cerr<<"loadMat:: can not load image" << endl;
        return soap_receiver_fault(soap, "loadMat:: can not load image", NULL);
    }

    /* convert Mat to required type */
    if(src.type()!= getMatType(types))
    {
        src.convertTo(src,getMatType(types));
    }


	/* generate output file name  and save to bin*/
	*OutputMatFilename = (char*)soap_malloc(soap, FILENAME_SIZE);
    getOutputFilename(OutputMatFilename,"_loadMat");
    if(!saveMat(*OutputMatFilename, src))
    {
        cerr<<"loadMat:: can not save mat to binary file" << endl;
        return soap_receiver_fault(soap, "loadMat:: can not save mat to binary file", NULL);
    }

    src.release();

    end = omp_get_wtime();
    cerr<<"ns__loadMat "<<"time elapsed "<<end-start<<endl;

    return SOAP_OK;
}
