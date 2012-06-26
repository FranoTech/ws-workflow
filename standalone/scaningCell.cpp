int ns__scanningCell(struct soap *soap,
						char *biggerArea,
                        char *keepArea,
						char **OutputMatFilename)
{
    double start, end;
    start = omp_get_wtime();

	Mat src; //input_morph
    if(!readMat(biggerArea, src))
    {
        cerr << "scanningCell :: can not read bin file" << endl;
        return soap_receiver_fault(soap, "scanningCell :: can not read bin file", NULL);
    }
    
    Mat out_single;
    if(!readMat(keepArea, out_single))
    {
        cerr << "scanningCell :: can not read bin file" << endl;
        return soap_receiver_fault(soap, "scanningCell :: can not read bin file", NULL);
    }
    
    
    Mat srcTmp;
    Mat src32FC1;
    src.convertTo(src32FC1, CV_32FC1);
    //~ Mat output = Mat::zeros(src.rows,src.cols, CV_32FC1);

    int nContour = 1;
    int prevContour = 0;
    int sameCount = 0;
    double area = 0;
    const Point* p;
    int n = 0;
    vector<vector<Point> > contours;

    while(nContour != 0)
    {
        src32FC1.convertTo(srcTmp, CV_8UC1); //cvConvert(input_morph, tmp8UC1);

        findContours( srcTmp, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0,0));
        nContour = contours.size();

        if( nContour == 0){ break; }
        if( nContour == prevContour ){
            erode( src32FC1, src32FC1, Mat());
            sameCount++;
        }else {
            sameCount = 0;
        }

        prevContour = nContour;

        for(size_t i = 0; i< contours.size(); i++)
        {
            p = &contours[i][0];
            n = (int)contours[i].size();
            area = fabs(contourArea(Mat(contours[i])));

            if((area < 3000.0) || (sameCount > 10))
            {
                fillPoly( src32FC1, &p, &n, 1, Scalar(0, 0, 0)); // remove from src
                fillPoly( out_single, &p, &n, 1, Scalar(255, 255, 255));
            }
        }
    }

	/* generate output file name */
    *OutputMatFilename = (char*)soap_malloc(soap, FILENAME_SIZE);
    getOutputFilename(OutputMatFilename,"_scanningCell");

    /* save to bin */
    if(!saveMat(*OutputMatFilename, out_single))
    {
        cerr << "scanningCell:: save mat to binary file" << endl;
        return soap_receiver_fault(soap, "scanningCell:: save mat to binary file", NULL);
    }

    src.release();
    srcTmp.release();
    src32FC1.release();
    out_single.release();

    end = omp_get_wtime();
    cerr<<"ns__scanningCell time elapsed "<<end-start<<endl;

    return SOAP_OK;
}
