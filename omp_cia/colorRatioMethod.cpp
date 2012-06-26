
//
// name: colorRatioMethod
// @param
// @return
//

int ns__colorRatioMethod(struct soap *soap,
						char *inputMatFilename,
						char **OutputMatFilename)
{
    double start, end;
    start = omp_get_wtime();

	Mat src;
    if(!readMat(inputMatFilename, src))
    {
        soap_fault(soap);
        cerr << "colorRatioMethod :: can not read bin file" << endl;
        soap->fault->faultstring = "colorRatioMethod :: can not read bin file";
        return SOAP_FAULT;
    }

    src.convertTo(src, CV_32FC3);
    vector<Mat> splited;

    cv::split(src, splited);

    /* splited[0] = B
    * splited[1] = G
    * splited[2] = R
    */

    Mat RB (splited[0].rows, splited[0].cols, CV_32FC1);
    Mat BR (splited[0].rows, splited[0].cols, CV_32FC1);
    Mat result = Mat::zeros(splited[0].rows, splited[0].cols, CV_32FC1);

    /* find R:B */
    cv::divide(splited[2], splited[0], RB, 1);

    /* find B:R */
    cv::divide(splited[0], splited[2], BR, 1);

    /* Find POS Cell */
    for( int y = 0; y < RB.rows; y++ )
    {   for( int x = 0; x < RB.cols; x++ ){
            if(RB.at<float>(y,x) >= 1.2 && BR.at<float>(y,x) < 1)
                result.at<float>(y,x) = 0;   // pos cell is black
            else
                result.at<float>(y,x) = 255;
        }
    }


    /* generate output file name */
	*OutputMatFilename = (char*)soap_malloc(soap, FILENAME_SIZE);
    time_t now = time(0);
    strftime(*OutputMatFilename, sizeof(OutputMatFilename)*FILENAME_SIZE, "/home/lluu/dir/%Y%m%d_%H%M%S_posCells", localtime(&now));

	/* save to bin */
    if(!saveMat(*OutputMatFilename, result))
    {
        soap_fault(soap);
        cerr << "colorRatioMethod :: can not save mat to binary file" << endl;
		soap->fault->faultstring = "colorRatioMethod :: can not save mat to binary file";
        return SOAP_FAULT;
    }

    src.release();
    splited.clear();
    RB.release();
    BR.release();
    result.release();

    end = omp_get_wtime();
    cerr<<"ns__colorRatioMethod "<<"time elapsed "<<end-start<<endl;
    return SOAP_OK;
}
