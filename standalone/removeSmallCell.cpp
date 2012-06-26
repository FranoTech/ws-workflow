//
// name: removeSmallCell
// @param
// @return
//

int ns__removeSmallCell(struct soap *soap,
						char *inputMatFilename,
						ns__RemoveSmallCell &out)
{
    double start, end;
    start = omp_get_wtime();

	Mat src; //input_morph
    if(!readMat(inputMatFilename, src))
    {
        cerr << "removeSmallCell :: can not read bin file" << endl;
        return soap_receiver_fault(soap, "removeSmallCell :: can not read bin file", NULL);
    }

    Mat tmp = Mat(src.rows, src.cols, CV_32FC1);

    if( src.type() != CV_8UC1)
    {
        src.convertTo(src, CV_8UC1);
    }

    Mat outSingle = Mat::zeros(src.rows, src.cols, CV_32FC1);
	vector<vector<cv::Point> > contours;
    double area = 0;
    const cv::Point* p;
    int n = 0;
    
    
    try{
    findContours(src, contours, CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE, Point(0,0));
	} catch (std::exception& e) { 
		cerr<<"error "<<e.what()<<endl; 
	}

    for(size_t i = 0; i< contours.size(); i++)
    {
		p = &contours[i][0];
        n = (int)contours[i].size();
		area = fabs(contourArea(Mat(contours[i])));

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
    strftime(out.keepedArea, sizeof(out.keepedArea)*FILENAME_SIZE, BASE_DIR"%Y%m%d_%H%M%S_keepedArea", localtime(&now));
    strftime(out.biggerArea, sizeof(out.biggerArea)*FILENAME_SIZE, BASE_DIR"%Y%m%d_%H%M%S_biggerArea", localtime(&now));

	
    /* save to bin */
    if(!saveMat(out.keepedArea, outSingle))
    {
        cerr << "removeSmallCell:: save mat to binary file" << endl;
        return soap_receiver_fault(soap, "removeSmallCell:: save mat to binary file", NULL);
    }

    if(!saveMat(out.biggerArea, tmp))
    {
        cerr << "removeSmallCell:: save mat to binary file" << endl;
        return soap_receiver_fault(soap, "removeSmallCell:: save mat to binary file", NULL);
    }

    src.release();
    tmp.release();
    outSingle.release();

    end = omp_get_wtime();
    cerr<<"ns__removeSmallCell"<<"time elapsed "<<end-start<<endl;
    return SOAP_OK;
}
