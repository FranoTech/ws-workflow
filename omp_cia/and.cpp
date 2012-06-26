
//
// name: ns__And
// @param char *src1, char *src2,
// @return char **OutputMatFilename

int ns__And(  struct soap *soap, char *src1,
				char *src2,
				char **OutputMatFilename)
{
    double start, end;
    start = omp_get_wtime();
    
	Mat matSrc1;
    if(!readMat(src1, matSrc1))
    {
        cerr << "And :: src1 can not read bin file" << endl;
        return soap_receiver_fault(soap, "And :: src1 can not read bin file", NULL);
    }

    Mat matSrc2;
    if(!readMat(src2, matSrc2))
    {
        cerr << "And :: src2 can not read bin file" << endl;
        return soap_receiver_fault(soap, "And :: src2 can not read bin file", NULL);
    }

    int cols = matSrc1.cols ;
    int srcType1 = matSrc1.type();
    int srcType2 = matSrc2.type();
    
    if(srcType1 != srcType2 )
    {
        #pragma omp parallel shared ( matSrc2, cols, srcType1)
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
            
            Mat tmpSrc2 = matSrc2.colRange(start, end);
            tmpSrc2.convertTo(tmpSrc2, srcType1);
        }
	}

    Mat dst;
    
    #pragma omp parallel shared (matSrc1, matSrc2, cols)
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
            
            Mat tmpSrc1 = matSrc1.colRange(start, end);
            Mat tmpSrc2 = matSrc2.colRange(start, end);
            Mat tmpDst = dst.colRange(start, end);
    
            bitwise_and(tmpSrc1, tmpSrc2, tmpDst);
    }
    
    /* generate output file name */
    *OutputMatFilename = (char*)soap_malloc(soap, 60);
    getOutputFilename(OutputMatFilename,"_bitwiseAnd");
    
    /* save to bin */
    if(!saveMat(*OutputMatFilename, dst))
    {
        cerr << "And:: save mat to binary file" << endl;
        return soap_receiver_fault(soap, "And :: save mat to binary file", NULL);
    }

    matSrc1.release();
    matSrc2.release();
    dst.release();
    
    end = omp_get_wtime();
    cerr<<"ns__And time elapsed "<<end-start<<endl;
    return SOAP_OK;
}
