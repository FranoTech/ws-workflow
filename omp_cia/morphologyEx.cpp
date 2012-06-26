//
// name: ns__MorphologyEx
// @param
//      char *InputMatFilename,
//      char *morphOperation="MORPH_OPEN",
// @return
//      char **OutputMatFilename=NULL

int ns__MorphologyEx( struct soap *soap,
                    char *InputMatFilename,
                    char *morphOperation="MORPH_OPEN",
                    char **OutputMatFilename=NULL)
{
    double start, end;
    start = omp_get_wtime();

    /* read from bin */
    Mat src;
    if(!readMat(InputMatFilename, src))
    {
        cerr << "MorphologyEx:: can not read bin file" << endl;
        return soap_receiver_fault(soap, "MorphologyEx:: can not read bin file", NULL);
    }

    Mat dst(src.rows, src.cols, src.depth());
    Mat se;
    Size seSize(3, 3);
    Point seAnc(1, 1);
    int opt = getMorphOperation(morphOperation);

    se = getStructuringElement(MORPH_ELLIPSE, seSize, seAnc);
    morphologyEx(src, dst, opt, se, seAnc);

    if(src.empty()) {
			cerr << "MorphologyEx :: something's wrong" << endl;
            return soap_receiver_fault(soap, "MorphologyEx:: something's wrong", NULL);
    }

    /* generate output file name */
    *OutputMatFilename = (char*)soap_malloc(soap, FILENAME_SIZE);
    getOutputFilename(OutputMatFilename,"_MorphologyEx");

    /* save to bin */
    if(!saveMat(*OutputMatFilename, dst))
    {
        cerr << "MorphologyEx:: can not save mat to binary file" << endl;
        return soap_receiver_fault(soap, "MorphologyEx:: can not save mat to binary file", NULL);
    }

    src.release();
    dst.release();
    se.release();

    end = omp_get_wtime();
    cerr<<"ns__MorphologyEx time elapsed "<<end-start<<endl;

    return SOAP_OK;
}
