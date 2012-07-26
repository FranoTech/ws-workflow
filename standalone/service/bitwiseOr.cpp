//
// name: ns__bitwiseOr
// @param char *src1, char *src2
// @return char **OutputMatFilename

int ns__bitwiseOr(  struct soap *soap, char *src1,
				char *src2,
				char **OutputMatFilename)
{
    double start, end;
    start = omp_get_wtime();

	Mat matSrc1;
    if(!readMat(src1, matSrc1))
    {
        cerr << "bitwiseOr :: src1 can not read bin file" << endl;
        return soap_receiver_fault(soap, "bitwiseOr :: src1 can not read bin file", NULL);
    }

    Mat matSrc2;
    if(!readMat(src2, matSrc2))
    {
        cerr << "bitwiseOr :: src2 can not read bin file" << endl;
        return soap_receiver_fault(soap, "bitwiseOr :: src2 can not read bin file", NULL);
    }

    int srcType1 = matSrc1.type();
    int srcType2 = matSrc2.type();

    if(srcType1 != srcType2)
    {
        matSrc2.convertTo(matSrc2, srcType1);
	}

    Mat dst;
    bitwise_or(matSrc1, matSrc2, dst);


    /* generate output file name */
    *OutputMatFilename = (char*)soap_malloc(soap, 60);
    getOutputFilename(OutputMatFilename,"_bitwiseOr");

    /* save to bin */
    if(!saveMat(*OutputMatFilename, dst))
    {
        cerr << "bitwiseOr:: save mat to binary file" << endl;
        return soap_receiver_fault(soap, "bitwiseOr :: save mat to binary file", NULL);
    }

    matSrc1.release();
    matSrc2.release();
    dst.release();

    end = omp_get_wtime();
    cerr<<"ns__bitwiseOr time elapsed "<<end-start<<endl;

    return SOAP_OK;
}
