
//
// name: ns__Not
// @param char *src
// @return char **OutputMatFilename


int ns__Not(  struct soap *soap, char *src,
			  char **OutputMatFilename)
{
    double start, end;
    start = omp_get_wtime();
    
	Mat matSrc;
    if(!readMat(src, matSrc))
    {
        cerr << "And :: src1 can not read bin file" << endl;
        return soap_receiver_fault(soap, "And :: src1 can not read bin file", NULL);
    }

    int cols = matSrc.cols;
    #pragma omp parallel shared(matSrc, cols)
    {
            int numt = omp_get_num_threads();
            int tid = omp_get_thread_num();
            int start;
            if(tid == 0)
            {
                start = tid*(cols/numt);
            } else {
                start = (tid*(cols/numt))+1;
            }
            int end = (tid+1)*(cols/numt);
            
            Mat tmpSrc = matSrc.colRange(start, end);
            bitwise_not(tmpSrc, tmpSrc);
    }
    
    /* generate output file name */
    *OutputMatFilename = (char*)soap_malloc(soap, 60);
    getOutputFilename(OutputMatFilename,"_bitwiseNot");
    
    /* save to bin */
    if(!saveMat(*OutputMatFilename, matSrc))
    {
        cerr << "Not:: save mat to binary file" << endl;
        return soap_receiver_fault(soap, "Not :: save mat to binary file", NULL);
    }

    matSrc.release();
    
    end = omp_get_wtime();
    cerr<<"ns__Not time elapsed "<<end-start<<endl;
    
    return SOAP_OK;
}

