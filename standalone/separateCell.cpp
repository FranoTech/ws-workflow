
//
// name: ns__separateCell
// @param char *inputMatFilename
// @return char **outputMatFilename
//

int ns__separateCell(struct soap *soap,
						char *input1, //outSingle
                        char *input2, //outMorph
						char **OutputMatFilename)
{
    double start, end;
    start = omp_get_wtime();

	Mat outSingle;
    if(!readMat(input1, outSingle))
    {
        cerr << "sep :: can not read bin file" << endl;
        return soap_receiver_fault(soap, "sep :: can not read bin file", NULL);
    }

    Mat tmp;
    outSingle.convertTo(tmp, CV_8UC1);
    
    int count = 1;
    int c = 0;
    int n = 0;
    const Point *p;
	vector<vector<Point> > contours;
    findContours(	tmp, contours, CV_RETR_EXTERNAL,
					CV_CHAIN_APPROX_SIMPLE, Point(0,0));

    for(size_t i = 0; i< contours.size(); i++)
    {
		p = &contours[i][0]; 
        n = (int)contours[i].size();
        c = ((count++)%254)+1;
        fillPoly( outSingle, &p, &n, 1, Scalar(c, c, c)); 
	}
	contours.clear();
    
    Mat inwater = Mat(outSingle.rows, outSingle.cols, CV_8UC3);
    //~ Mat outwater = Mat(outSingle.size(),CV_32SC1,outSingle.data);  //Is it correct?
    //Mat outwater;
    //outSingle.convertTo(outwater,CV_32SC1);
    outSingle.convertTo(outSingle,CV_32SC1);
    
    Mat cell; //output_morph
    if(!readMat(input2, cell))
    {
        cerr << "sepl :: can not read bin file" << endl;
    }
    
    Mat tmp8UC1;
    cell.convertTo(tmp8UC1,CV_8UC1);
    
    vector<Mat> wt;
    wt.push_back(tmp8UC1);
    wt.push_back(tmp8UC1);
    wt.push_back(tmp8UC1);

    merge(wt, inwater);  
    watershed(inwater, outSingle);
    
    outSingle.convertTo(outSingle,CV_32FC1);
    erode(outSingle, outSingle, Mat(), Point(-1, -1), 2); 
    
    cell.convertTo(tmp8UC1,CV_8UC1);
    subtract(cell, outSingle, cell, tmp8UC1);

    if(!imwrite("result_sepCell_3.jpg", cell))
    {
        cerr<< "can not save mat to jpg file" << endl;
    }

	/* generate output file name */
    *OutputMatFilename = (char*)soap_malloc(soap, FILENAME_SIZE);
    getOutputFilename(OutputMatFilename,"_sep");

    /* save to bin */
    if(!saveMat(*OutputMatFilename, cell))
    {
        cerr << "result:: save mat to binary file" << endl;
        return soap_receiver_fault(soap, "result:: save mat to binary file", NULL);
    }

    tmp8UC1.release();
    cell.release();
    outSingle.release();

    end = omp_get_wtime();
    cerr<<"ns__sep"<<"time elapsed "<<end-start<<endl;
    return SOAP_OK;
    
}
