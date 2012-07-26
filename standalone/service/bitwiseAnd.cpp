//
// name: ns__And
// @param char *src1, char *src2,
// @return char **OutputMatFilename

int ns__bitwiseAnd(  struct soap *soap, char *src1,
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
        matSrc2.convertTo(matSrc2, srcType1);
	}

    Mat dst;
    bitwise_and(matSrc1, matSrc2, dst);

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
