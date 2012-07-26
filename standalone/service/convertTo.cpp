//
// name: convertTo
// @param char *inputMatFilename
// @return
//      char *types="CV_32FC1",
//      char **outputMatFilename
int ns__convertTo( struct soap *soap, char *InputMatFilename,
                    char *types="CV_32FC1",
                    char **OutputMatFilename=NULL)
{
    double start, end;
    start = omp_get_wtime();

    Mat src;
    if(!readMat(InputMatFilename, src))
    {
        cerr<< "ConvertTo:: can not read bin file" << endl;
        return soap_receiver_fault(soap, "ConvertTo:: can not read bin file", NULL);
    }

    int MatType = getMatType(types);
    int cols = src.cols ;

    if(src.type()!= MatType)
    {
        src.convertTo(src, MatType);
    }

    /* generate output file name */
	*OutputMatFilename = (char*)soap_malloc(soap, FILENAME_SIZE);
    getOutputFilename(OutputMatFilename,"_ConvertTo");

	/* save to bin */
    if(!saveMat(*OutputMatFilename, src))
    {
        cerr<<"ConvertTo:: can not save mat to binary file" << endl;
		return soap_receiver_fault(soap, "ConvertTo:: can not save mat to binary file", NULL);
    }

    src.release();

    end = omp_get_wtime();
    cerr<<"ns__ConvertTo "<<"time elapsed "<<end-start<<endl;
    return SOAP_OK;
}
