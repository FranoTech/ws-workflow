
//name: removeSmallCell
//@param
//@return

int ns__removeSmallCell(struct soap *soap,
						char *inputMatFilename,
						ns__RemoveSmallCell &out)
{
    double start, end;
    start = omp_get_wtime();

	Mat src;
    if(!readMat(inputMatFilename, src))
    {
        cerr << "removeSmallCell :: can not read bin file" << endl;
        return soap_receiver_fault(soap, "removeSmallCell :: can not read bin file", NULL);
    }

    //~ Mat tmp = Mat(src.rows, src.cols, CV_32FC1);
    
    /* convert src type to 8UC1 */
    if( src.type() != CV_8UC1)
    {
        #pragma omp parallel
        {
            int numt = omp_get_num_threads();
            int tid = omp_get_thread_num();
            int start;
            if(tid == 0)
            {
                start = tid*(src.cols/numt);
            } else {
                start = (tid*(src.cols/numt))+1;
            }
            int end = (tid+1)*(src.cols/numt);
            
            Mat tmpSrc = src.colRange(start, end);
            tmpSrc.convertTo(tmpSrc, CV_8UC1);
        }
    }

    Mat outSingle = Mat::zeros(src.rows, src.cols, CV_32FC1);
	vector<vector<Point> > contours;
    double area = 0;
    findContours(	src, contours, CV_RETR_EXTERNAL,
					CV_CHAIN_APPROX_SIMPLE, Point(0,0));
/*        check this          */
    //~ #pragma omp parallel for shared()
    for(size_t i = 0; i< contours.size(); i++)
    {
		const Point* p = &contours[i][0];
        int n = (int)contours[i].size();
		area = contourArea(Mat(contours[i]));

		if(area < 1500.0) //lower bound
		{
			fillPoly( tmp, &p, &n, 1, Scalar(0, 0, 0)); // remove from src (put black area instead the old one)

		} else if (area < 7500.0) {
			fillPoly(outSingle, &p, &n, 1, Scalar(255, 255, 255)); // keep small area here with white color
			fillPoly( tmp, &p, &n, 1, Scalar(0, 0, 0)); // remove from src

		} else {
			fillPoly( tmp, &p, &n, 1, Scalar(255, 255, 255)); //left the bigger area in src

		}
	}

	contours.clear();

	/* generate output file name */
    out.keepedArea = (char*)soap_malloc(soap, FILENAME_SIZE);
    out.biggerArea = (char*)soap_malloc(soap, FILENAME_SIZE);

    time_t now = time(0);
    strftime(out.keepedArea, sizeof(out.keepedArea)*FILENAME_SIZE, "/home/lluu/dir/%Y%m%d_%H%M%S_keepedArea", localtime(&now));
    strftime(out.biggerArea, sizeof(out.biggerArea)*FILENAME_SIZE, "/home/lluu/dir/%Y%m%d_%H%M%S_biggerArea", localtime(&now));

    /* save to bin */
    if(!saveMat(out.keepedArea, outSingle))
    {
        soap_fault(soap);
        cerr << "removeSmallCell:: save mat to binary file" << endl;
        soap->fault->faultstring = "error:: save mat to binary file";
        return SOAP_FAULT;
    }

    if(!saveMat(out.biggerArea, tmp))
    {
        soap_fault(soap);
        cerr << "removeSmallCell:: save mat to binary file" << endl;
        soap->fault->faultstring = "error:: save mat to binary file";
        return SOAP_FAULT;
    }

    src.release();
    tmp.release();
    outSingle.release();

    end = omp_get_wtime();
    cerr<<"ns__removeSmallCell"<<"time elapsed "<<end-start<<endl;
    return SOAP_OK;
}
