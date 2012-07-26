//
// name: ns__erode
// @param
//		- src Source image.
//		- element Structuring element used for erosion.
//		- iteration  Number of times erosion is applied.
// @return
// 		- OutputMatFilename


int ns__erode(  struct soap *soap, char *InputMatFilename,
				char *elementFilename,
				int iteration=1,
				char **OutputMatFilename=NULL)
{
    double start, end;
    start = omp_get_wtime();

	Mat src;
    if(!readMat(InputMatFilename, src))
    {
        cerr << "erode :: can not read bin file" << endl;
        return soap_receiver_fault(soap, "erode :: can not read bin file", NULL);
    }

    Mat dst;
    Mat element;

    if(!readMat(elementFilename, element))
    {
		cerr<<"erode: use default element"<<endl;
        element.release();
        erode(src, dst, Mat(), Point(-1, -1), iteration);
    } else {
		cerr<<"erode: use defined element"<<endl;
        erode(src, dst, element, Point(-1, -1), iteration);
    }

    /* generate output file name */
    *OutputMatFilename = (char*)soap_malloc(soap, 60);
    getOutputFilename(OutputMatFilename,"_erode");

    /* save to bin */
    if(!saveMat(*OutputMatFilename, dst))
    {
        cerr << "erode:: save mat to binary file" << endl;
        return soap_receiver_fault(soap, "erode :: save mat to binary file", NULL);
    }

    src.release();
    dst.release();
    element.release();

    return SOAP_OK;
}
