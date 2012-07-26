//
// name: ns__Not
// @param char *src
// @return char **OutputMatFilename


int ns__bitwiseNot(  struct soap *soap, char *src,
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

    bitwise_not(matSrc, matSrc);

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
