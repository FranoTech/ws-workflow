
//
// name: ns__dilate
// @param
//		- src Source image.
//		- element Structuring element used for dilation.
//		- iteration  Number of times erosion is applied.
// @return
// 		- OutputMatFilename


int ns__dilate(  struct soap *soap, char *InputMatFilename,
				char *elementFilename,
				int iteration=1,
				char **OutputMatFilename=NULL)
{
    double start, end;
    start = omp_get_wtime();

	Mat src;
    if(!readMat(InputMatFilename, src))
    {
        cerr << "dilate :: can not read bin file" << endl;
        return soap_receiver_fault(soap, "dilate :: can not read bin file", NULL);
    }

    Mat dst;
    Mat element;

    if(!readMat(elementFilename, element))
    {
		cerr<<"dilate :: use default element"<<endl;
        element.release();
        dilate(src, dst, Mat(), Point(-1, -1), iteration);
    } else {
		cerr<<"dilate :: use defined element"<<endl;
        dilate(src, dst, element, Point(-1, -1), iteration);
    }

    /* generate output file name */
    *OutputMatFilename = (char*)soap_malloc(soap, 60);
    getOutputFilename(OutputMatFilename,"_dilate");

    /* save to bin */
    if(!saveMat(*OutputMatFilename, dst))
    {
        cerr << "dilate :: save mat to binary file" << endl;
        return soap_receiver_fault(soap, "dilate :: save mat to binary file", NULL);
    }

    src.release();
    dst.release();
    element.release();

    return SOAP_OK;
}
