//
// name: Threshold
// @param
// @return

int ns__Threshold(struct soap *soap,
                        char *InputMatFilename,
                        double thresholdValue=127.0,
                        double maxValue=255.0,
                        char *thresholdType="THRESH_BINARY",
                        char **OutputMatFilename=NULL)
{
    double start, end;
    start = omp_get_wtime();

    /* read from bin */
    Mat src;
	if(!readMat(InputMatFilename, src))
    {
        cerr<< "Threshold:: can not read bin file" << endl;
        return soap_receiver_fault(soap, "Threshold:: can not read bin file", NULL);
    }
    
    int threstype = getThresholdType (thresholdType);
    int rows = src.rows ;
    
    #pragma omp parallel shared(src, cols, thresholdValue, maxValue, threstype)
    {
        int numt = omp_get_num_threads();
        int tid = omp_get_thread_num();
        int start = tid*(rows/numt); 
        int end = (tid+1)*(rows/numt);
        if( tid == (numt-1))
        {
            end = rows;
        }
        
        Mat tmpSrc = src.rowRange(start, end);
        threshold(tmpSrc, tmpSrc, thresholdValue, maxValue, threstype);
    }
    
    /* generate output file name and save to binary file */
	*OutputMatFilename = (char*)soap_malloc(soap, FILENAME_SIZE);
    getOutputFilename(OutputMatFilename,"_Threshold");
    if(!saveMat(*OutputMatFilename, src))
    {
        cerr << "Threshold:: can not save mat to binary file" << endl;
        return soap_receiver_fault(soap, "Threshold:: can not save mat to binary file", NULL);
    }

    src.release();
    end = omp_get_wtime();
    cerr<<"ns__Threshold time elapsed "<<end-start<<endl;
    return SOAP_OK;
}
