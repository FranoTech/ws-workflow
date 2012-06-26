
//
// name: ns__scanningCell
// @param char *inputMatFilename
// @return char **outputMatFilename
//

int ns__scanningCell(struct soap *soap,
						char *inputMatFilename,
						char **OutputMatFilename)
{
    double start, end;
    start = omp_get_wtime();

	Mat src;
    if(!readMat(inputMatFilename, src))
    {
        soap_fault(soap);
        cerr << "scanningCell :: can not read bin file" << endl;
        soap->fault->faultstring = "scanningCell :: can not read bin file";
        return SOAP_FAULT;
    }

    Mat srcTmp;
    Mat src32FC1;
    src.convertTo(src32FC1, CV_32FC1);
    Mat output = Mat::zeros(src.rows,src.cols, CV_32FC1);

    int nContour = 1;
    int prevContour = 0;
    int sameCount = 0;
    double area = 0;
    vector<vector<Point> > contours;

    while(nContour != 0)
    {
        src32FC1.convertTo(srcTmp, CV_8UC1);

        findContours( srcTmp, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0,0));
        nContour = contours.size();

        if( nContour == 0){ break; }
        if( nContour == prevContour ){
            erode( src32FC1, src32FC1, Mat() );
            sameCount++;
        }else {
            sameCount = 0;
        }

        prevContour = nContour;

        for(size_t i = 0; i< contours.size(); i++)
        {
            const Point* p = &contours[i][0];
            int n = (int)contours[i].size();
            area = contourArea(Mat(contours[i]));

            if((area < 3000.0) || (sameCount > 10))
            {
                fillPoly( src32FC1, &p, &n, 1, Scalar(0, 0, 0)); // remove from src
                fillPoly( output, &p, &n, 1, Scalar(255, 255, 255));
            }
        }
    }

	/* generate output file name */
    *OutputMatFilename = (char*)soap_malloc(soap, FILENAME_SIZE);

    time_t now = time(0);
    strftime(*OutputMatFilename, sizeof(OutputMatFilename)*FILENAME_SIZE, "/home/lluu/dir/%Y%m%d_%H%M%S_scaningCell", localtime(&now));

    /* save to bin */
    if(!saveMat(*OutputMatFilename, output))
    {
        soap_fault(soap);
        cerr << "scanningCell:: save mat to binary file" << endl;
        soap->fault->faultstring = "scanningCell:: save mat to binary file";
        return SOAP_FAULT;
    }

    src.release();
    srcTmp.release();
    src32FC1.release();
    output.release();

    end = omp_get_wtime();
    cerr<<"ns__scanningCell"<<"time elapsed "<<end-start<<endl;

    return SOAP_OK;
}
