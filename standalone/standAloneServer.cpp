#include "headerfile.cpp"

#define BASE_DIR "/home/lluu/thesis/RESULT/"
#define FILENAME_SIZE 75
#define MAX_THREAD 4
#define SERVERPORT 8080

//namespace
using namespace std;
using namespace cv;

/* Helper Function */
int saveMat( const char *filename, const Mat& M);
int readMat( const char *filename, Mat& M);
int getMatType (const char *typeName);
int getThresholdType ( const char *typeName);
int getColorFlag(int colorflag);
int getMorphOperation ( const char *typeName);
int ByteArrayToANN(char *annfile, CvANN_MLP* ann);
void getOutputFilename (char **filename, const char *toAppend);

Mat globalMat;
int matNo;
int writeProtected;

int main(int argc, char **argv) 
{
    SOAP_SOCKET master, slave; /* master and slave sockets */
    struct soap soap;
    soap_init(&soap);
    if (argc < 2)
            soap_serve(&soap);	/* serve as CGI application */
    else{ 
        master = soap_bind(&soap, NULL, SERVERPORT, 100);
        if (!soap_valid_socket(master)){ 
            soap_print_fault(&soap, stderr);
            exit(-1);
        }
        fprintf(stderr, "Socket connection successful: master socket = %d\n", master);
        for ( ; ; )
        { 
            slave = soap_accept(&soap);
            fprintf(stderr, "Socket connection successful: slave socket = %d\n", slave);
            if (!soap_valid_socket(slave))
            { 
                soap_print_fault(&soap, stderr);
                exit(-1);
            } 
            soap_serve(&soap);
            soap_end(&soap);
        }
    }
}




/* Load image data to Mat, save to binary file */
int ns__loadMat (struct soap *soap,
                char *InputImageFilename,
                int colorflag=0,
                char *types="CV_32FC1",
                int *response=0)
{
    double start, end;
    start = omp_get_wtime();

    Mat src;

    /* load image data */
    src = imread(InputImageFilename,getColorFlag(colorflag));
    if(src.empty()) {
        cerr<<"loadMat:: can not load image" << endl;
        return soap_receiver_fault(soap, "loadMat:: can not load image", NULL);
    }

    /* convert Mat to required type */
    if(src.type()!= getMatType(types))
    {
        src.convertTo(src,getMatType(types));
    }

    
    globalMat = src.clone();
    src.release();
    *response = 1; 

    end = omp_get_wtime();
    cerr<<"ns__loadMat "<<"time elapsed "<<end-start<<endl;

    return SOAP_OK;
}


//
// name: MatToJPG
// - convert nat to 8U and save as JPG
// @param char *InputMatFilename
// @return char **OutputMatFilename

int ns__MatToJPG (struct soap *soap, int status=0, char **OutputMatFilename=NULL)
{
    double start, end;
    start = omp_get_wtime();

    if( status != 1){
        return soap_receiver_fault(soap, "MatToJPG:: Service Error. Please check the previous service result.", NULL);
    }
    
    Mat src = globalMat.clone();
    
    /* check if it is not 8U then convert to 8UC(n) */
    int chan = src.channels();
    if( src.type() != 0 || src.type() != 8 || src.type() != 16 )
    {
       src.convertTo(src, CV_8UC(chan));
    }

    /* generate output file name */
    *OutputMatFilename = (char*)soap_malloc(soap, FILENAME_SIZE);
    getOutputFilename(OutputMatFilename,".jpg");

    if(!imwrite(*OutputMatFilename, src))
    {
        cerr<< "MatToJPG:: can not save mat to jpg file" << endl;
        return soap_receiver_fault(soap, "MatToJPG:: can not save mat to jpg file", NULL);
    }
    globalMat = src.clone();
    src.release();

    end = omp_get_wtime();
    cerr<<"ns__MatToJPG "<<"time elapsed "<<end-start<<endl;

    return SOAP_OK;
}


//
// name: convertTo
// @param char *inputMatFilename
// @return
//      char *types="CV_32FC1",
//      char **outputMatFilename
int ns__convertTo( struct soap *soap, char *types="CV_32FC1", int *response=0)
{
    double start, end;
    start = omp_get_wtime();

    Mat src = globalMat.clone();
    
    int MatType = getMatType(types);
    int cols = src.cols ;

    if(src.type()!= MatType)
    {
        src.convertTo(src, MatType);
    }

    *response = 1; 
    globalMat = src.clone();
    src.release();

    end = omp_get_wtime();
    cerr<<"ns__ConvertTo "<<"time elapsed "<<end-start<<endl;
    return SOAP_OK;
}


//
// name: Threshold
// @param
// @return

int ns__threshold(struct soap *soap,
                    double thresholdValue=127.0,
                    double maxValue=255.0,
                    char *thresholdType="THRESH_BINARY",
                    int *response=0)
{
    double start, end;
    start = omp_get_wtime();

    /* read from bin */
    Mat src = globalMat.clone();

    int threstype = getThresholdType (thresholdType);
    threshold(src, src, thresholdValue, maxValue, threstype);
    
    globalMat = src.clone();
    src.release();
    *response = 1; 
    
    end = omp_get_wtime();
    cerr<<"ns__Threshold time elapsed "<<end-start<<endl;
    return SOAP_OK;
}


//
// name: ns__MorphologyEx
// @param
//      char *InputMatFilename,
//      char *morphOperation="MORPH_OPEN",
// @return
//      char **OutputMatFilename=NULL

int ns__morphologyEx( struct soap *soap,
                    int status,
                    char *morphOperation="MORPH_OPEN",
                    int *response)
{
    double start, end;
    start = omp_get_wtime();

    /* read from bin */
    Mat src = globalMat;
    
    //~ Mat dst(src.rows, src.cols, src.depth());
    Mat se;
    Size seSize(3, 3);
    Point seAnc(1, 1);
    int opt = getMorphOperation(morphOperation);

    se = getStructuringElement(MORPH_ELLIPSE, seSize, seAnc);
    morphologyEx(src, src, opt, se, seAnc);

    if(src.empty()) {
			cerr << "MorphologyEx :: something's wrong" << endl;
            return soap_receiver_fault(soap, "MorphologyEx:: something's wrong", NULL);
    }

    globalMat = src.clone();
    src.release();
    //~ dst.release();
    se.release();

    end = omp_get_wtime();
    cerr<<"ns__MorphologyEx time elapsed "<<end-start<<endl;

    return SOAP_OK;
}


//
// name: ns__erode
// @param
//		- src Source image.
//		- element Structuring element used for erosion.
//		- iteration  Number of times erosion is applied.
// @return
// 		- OutputMatFilename


int ns__erode(  struct soap *soap,
                int status,
				char *elementFilename,
				int iteration=1,
				int *response)
{
    double start, end;
    start = omp_get_wtime();

	Mat src = globalMat.clone();
    Mat element;

    if(!readMat(elementFilename, element))
    {
		cerr<<"erode: use default element"<<endl;
        element.release();
        erode(src, src, Mat(), Point(-1, -1), iteration);
    } else {
		cerr<<"erode: use defined element"<<endl;
        erode(src, src, element, Point(-1, -1), iteration);
    }

    globalMat = src.clone();
    src.release();
    element.release();

    return SOAP_OK;
}


//
// name: ns__dilate
// @param
//		- src Source image.
//		- element Structuring element used for dilation.
//		- iteration  Number of times erosion is applied.
// @return
// 		- OutputMatFilename


int ns__dilate(  struct soap *soap, int status,
				char *elementFilename,
				int iteration=1,
				int *response)
{
    double start, end;
    start = omp_get_wtime();

	Mat src;
    Mat element;

    if(!readMat(elementFilename, element))
    {
		cerr<<"dilate :: use default element"<<endl;
        element.release();
        dilate(src, src, Mat(), Point(-1, -1), iteration);
    } else {
		cerr<<"dilate :: use defined element"<<endl;
        dilate(src, src, element, Point(-1, -1), iteration);
    }

    globalMat = src.clone();
    src.release();
    element.release();

    return SOAP_OK;
}


////
//// name: ns__Or
//// @param char *src1, char *src2
//// @return char **OutputMatFilename

//int ns__bitwiseOr(  struct soap *soap, char *src1,
				//char *src2,
				//char **OutputMatFilename)
//{
    //double start, end;
    //start = omp_get_wtime();

	//Mat matSrc1;
    //if(!readMat(src1, matSrc1))
    //{
        //cerr << "Or :: src1 can not read bin file" << endl;
        //return soap_receiver_fault(soap, "Or :: src1 can not read bin file", NULL);
    //}

    //Mat matSrc2;
    //if(!readMat(src2, matSrc2))
    //{
        //cerr << "Or :: src2 can not read bin file" << endl;
        //return soap_receiver_fault(soap, "Or :: src2 can not read bin file", NULL);
    //}

    //int srcType1 = matSrc1.type();
    //int srcType2 = matSrc2.type();

    //if(srcType1 != srcType2)
    //{
        //matSrc2.convertTo(matSrc2, srcType1);
	//}

    //Mat dst;
    //bitwise_or(matSrc1, matSrc2, dst);


    ///* generate output file name */
    //*OutputMatFilename = (char*)soap_malloc(soap, 60);
    //getOutputFilename(OutputMatFilename,"_bitwiseOr");

    ///* save to bin */
    //if(!saveMat(*OutputMatFilename, dst))
    //{
        //cerr << "Or:: save mat to binary file" << endl;
        //return soap_receiver_fault(soap, "Or :: save mat to binary file", NULL);
    //}

    //matSrc1.release();
    //matSrc2.release();
    //dst.release();

    //end = omp_get_wtime();
    //cerr<<"ns__Or time elapsed "<<end-start<<endl;

    //return SOAP_OK;
//}


////
//// name: ns__And
//// @param char *src1, char *src2,
//// @return char **OutputMatFilename

//int ns__bitwiseAnd(  struct soap *soap, char *src1,
				//char *src2,
				//char **OutputMatFilename)
//{
    //double start, end;
    //start = omp_get_wtime();

	//Mat matSrc1;
    //if(!readMat(src1, matSrc1))
    //{
        //cerr << "And :: src1 can not read bin file" << endl;
        //return soap_receiver_fault(soap, "And :: src1 can not read bin file", NULL);
    //}

    //Mat matSrc2;
    //if(!readMat(src2, matSrc2))
    //{
        //cerr << "And :: src2 can not read bin file" << endl;
        //return soap_receiver_fault(soap, "And :: src2 can not read bin file", NULL);
    //}

    //int cols = matSrc1.cols ;
    //int srcType1 = matSrc1.type();
    //int srcType2 = matSrc2.type();

    //if(srcType1 != srcType2 )
    //{
        //matSrc2.convertTo(matSrc2, srcType1);
	//}

    //Mat dst;
    //bitwise_and(matSrc1, matSrc2, dst);

    ///* generate output file name */
    //*OutputMatFilename = (char*)soap_malloc(soap, 60);
    //getOutputFilename(OutputMatFilename,"_bitwiseAnd");

    ///* save to bin */
    //if(!saveMat(*OutputMatFilename, dst))
    //{
        //cerr << "And:: save mat to binary file" << endl;
        //return soap_receiver_fault(soap, "And :: save mat to binary file", NULL);
    //}

    //matSrc1.release();
    //matSrc2.release();
    //dst.release();

    //end = omp_get_wtime();
    //cerr<<"ns__And time elapsed "<<end-start<<endl;
    //return SOAP_OK;
//}


////
//// name: ns__Not
//// @param char *src
//// @return char **OutputMatFilename


int ns__bitwiseNot(  struct soap *soap, char *src,
			  char **OutputMatFilename)
{
    double start, end;
    start = omp_get_wtime();

	Mat matSrc = globalMat.clone();

    bitwise_not(matSrc, matSrc);
    
    globalMat = matSrc.clone();
    matSrc.release();

    end = omp_get_wtime();
    cerr<<"ns__Not time elapsed "<<end-start<<endl;

    return SOAP_OK;
}


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

	Mat src = globalMat.clone(); //input_morph

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
    strftime(out.keepedArea, sizeof(out.keepedArea)*FILENAME_SIZE, "/home/lluu/thesis/RESULT/%Y%m%d_%H%M%S_keepedArea", localtime(&now));
    strftime(out.biggerArea, sizeof(out.biggerArea)*FILENAME_SIZE, "/home/lluu/thesis/RESULT/%Y%m%d_%H%M%S_biggerArea", localtime(&now));

	
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

//
// name: ns__scanningCell
// @param char *inputMatFilename
// @return char **outputMatFilename
//

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


int ns__prepareResult(struct soap *soap,
						char *inputMatFilename,
                        char *afterthresNN,
						char **OutputMatFilename)
{
    double start, end;
    start = omp_get_wtime();

    Mat src;
    if(!readMat(inputMatFilename, src))
    {
        cerr << "prepareResult :: can not read bin file" << endl;
        return soap_receiver_fault(soap, "prepareResult :: can not read bin file", NULL);
    }

    // convert src to CvMat to use an old-school function
    CvMat tmp = src;
    CV_Assert(tmp.cols == src.cols && tmp.rows == src.rows &&
        tmp.data.ptr == (uchar*)src.data && tmp.step == src.step);
    
    CvMat *output_morph = cvCreateMat(src.rows, src.cols, CV_32FC1);
    cvConvert(&tmp, output_morph);
    
    //***************************//
    Mat output1ChSrc;
    if(!readMat(afterthresNN, output1ChSrc))
    {
        cerr << "output1Ch:: can not read bin file" << endl;
        return soap_receiver_fault(soap, "output1Ch :: can not read bin file", NULL);
    }

    // convert src to CvMat to use an old-school function
    CvMat tmp2 = output1ChSrc;
    CV_Assert(tmp2.cols == output1ChSrc.cols && tmp2.rows == output1ChSrc.rows &&
        tmp2.data.ptr == (uchar*)output1ChSrc.data && tmp2.step == output1ChSrc.step);
    
    CvMat *output1Ch = cvCreateMat(tmp2.rows, tmp2.cols, CV_32FC1);
    cvConvert(&tmp2, output1Ch);
    
    //**********************//
    
    
    IplImage *tmp8UC1 = cvCreateImage(cvGetSize(output_morph), IPL_DEPTH_8U, 1);
    cvConvertScale(output_morph, tmp8UC1);
    
    CvMemStorage *storage = cvCreateMemStorage();
	CvSeq *first_con = NULL;
	CvSeq *cur = NULL;
    
    cvFindContours(tmp8UC1, storage, &first_con, sizeof(CvContour), CV_RETR_EXTERNAL);
    
    IplImage *tmpImage = cvCreateImage(cvSize(tmp8UC1->width, tmp8UC1->height), IPL_DEPTH_8U, 3);
    cvSet(tmpImage, CV_RGB(0,0,255)); // Background, blue

    cvSetZero(tmp8UC1);
    CvScalar pixel;
    cur = first_con;
    //~ int ncell = 0; // total cells
    
    while (cur != NULL) {
        if ((cur->total > 2) && (fabs(cvContourArea(cur)) > 1500.0)) { // remove small area
            int npts = cur->total;
            CvPoint *p = new CvPoint[npts];
            cvCvtSeqToArray(cur, p);
            cvFillPoly(tmp8UC1, &p, &npts, 1, cvScalar(255)); // set mask
            pixel = cvAvg(output1Ch, tmp8UC1);
            cvFillPoly(tmp8UC1, &p, &npts, 1, cvScalar(0)); // clear mask
            if (pixel.val[0] > 0.5) { // Negative, green
                if (tmpImage != NULL)
                    cvFillPoly(tmpImage, &p, &npts, 1, CV_RGB(0,255,0));
                    
            } else if (pixel.val[0] > -0.5) { // Positive, red
                if (tmpImage != NULL)
                    cvFillPoly(tmpImage, &p, &npts, 1, CV_RGB(255,0,0));
            }
            delete[] p;
        }
        cur = cur->h_next;
    }
    
    Mat result = cvarrToMat(tmpImage, false);

	/* generate output file name */
    *OutputMatFilename = (char*)soap_malloc(soap, FILENAME_SIZE);
    getOutputFilename(OutputMatFilename,"_result");

    /* save to bin */
    if(!saveMat(*OutputMatFilename, result))
    {
        cerr << "result:: save mat to binary file" << endl;
        return soap_receiver_fault(soap, "result:: save mat to binary file", NULL);
    }

    src.release();

    end = omp_get_wtime();
    cerr<<"ns__waterShed"<<"time elapsed "<<end-start<<endl;
    return SOAP_OK;
}




//
// name: trainANN
// @param   char *inputMatFilename,
//          char *neuralFile
// @return  char **OutputMatFilename

int ns__trainANN(struct soap *soap,
                char *inputMatFilename,
                char *neuralFile,
                char **OutputMatFilename)
{
    double start, end;
    start = omp_get_wtime();

	Mat src; //must be 3ch image
    if(!readMat(inputMatFilename, src))
    {
        cerr << "trainANN :: can not read bin file" << endl;
        return soap_receiver_fault(soap, "trainANN :: can not read bin file", NULL);
    }

    // convert src to CvMat to use an old-school function
    CvMat tmp = src;
    CV_Assert(tmp.cols == src.cols && tmp.rows == src.rows &&
        tmp.data.ptr == (uchar*)src.data && tmp.step == src.step);

    CvMat *input3Ch = cvCreateMat(src.rows, src.cols, CV_32FC3);
    cvConvert(&tmp, input3Ch);
    CvMat *output1Ch = cvCreateMat(src.rows, src.cols, CV_32FC1);

    CvANN_MLP* neuron = NULL ;
    if (neuron == NULL )
        neuron = new CvANN_MLP();
	else
        neuron->clear();

    if(!ByteArrayToANN(neuralFile, neuron)){
        cerr << "trainANN :: can not load byte array to neural" << endl;
        return soap_receiver_fault(soap, "trainANN :: can not load byte array to neural", NULL);
    }

    CvMat input_nn = cvMat(input3Ch->height*input3Ch->width, 3, CV_32FC1, input3Ch->data.fl);
    CvMat output_nn = cvMat(output1Ch->height*output1Ch->width, 1, CV_32FC1, output1Ch->data.fl);
    neuron->predict(&input_nn, &output_nn);

    Mat resultNN = cvarrToMat(output1Ch, false);

    /* generate output file name */
    *OutputMatFilename = (char*)soap_malloc(soap, FILENAME_SIZE);

    getOutputFilename(OutputMatFilename,"_trainANN");

    /* save to bin */
    if(!saveMat(*OutputMatFilename, resultNN))
    {
        cerr << "trainANN :: save mat to binary file" << endl;
        return soap_receiver_fault(soap, "trainANN :: save mat to binary file", NULL);
    }

    src.release();
    resultNN.release();
    cvReleaseMat(&output1Ch);

    end = omp_get_wtime();
    cerr<<"ns__trainANN  time elapsed "<<end-start<<endl;

    return SOAP_OK;
}


int ns__viewImage(  struct soap *soap, 
                    int status, 
                    ns__base64Binary &image)
{
    double start, end;
    start = omp_get_wtime();

    Mat src = globalMat.clone();
    //~ if(!readMat(inputMatFilename, src))
    //~ {
        //~ cerr << "viewImage:: can not read bin file" << endl;
        //~ return soap_receiver_fault(soap, "viewImage:: can not read bin file", NULL);
    //~ }
    
    /* check if it is not 8U then convert to 8UC(n) */
    int chan = src.channels();
    if( src.type() != 0 || src.type() != 8 || src.type() != 16 )
    {
       src.convertTo(src, CV_8UC(chan));
    }

    if(!imwrite("/home/lluu/thesis/RESULT/output.jpg", src))
    {
        cerr<< "viewImage:: can not save mat to jpg file" << endl;
    }

    FILE *fd = fopen("/home/lluu/thesis/RESULT/output.jpg", "r");
    if(fd){
        int i =0, c = 0;
        fseek(fd,0,SEEK_END); // seek to end of file
        int size = ftell(fd); // get current file pointer
        fseek(fd, 0, SEEK_SET); // seek back to beginning of file
        
        image.__ptr = (unsigned char*)soap_malloc(soap, size);
        for (i = 0; i < size; i++)
        { if ((c = fgetc(fd)) == EOF)
            break;
          image.__ptr[i] = c;
        }
        image.__size = i;
    } else {
        cerr<<"viewImage:: image file read error"<<endl;
    }
    
    return SOAP_OK;
}


int ns__showMatSerialOut( struct soap *soap,
                            int status,
                            )



/* helper function */
/* Save matrix to binary file */
int saveMat( const char *filename, const Mat& M){
    if (M.empty()){
       return 0;
    }
    ofstream out(filename, ios::out|ios::binary);
    if (!out)
       return 0;

    int cols = M.cols;
    int rows = M.rows;
    int chan = M.channels();
    int eSiz = (M.dataend-M.datastart)/(cols*rows*chan);

    /* Write header */
    out.write((char*)&cols,sizeof(cols));
    out.write((char*)&rows,sizeof(rows));
    out.write((char*)&chan,sizeof(chan));
    out.write((char*)&eSiz,sizeof(eSiz));

    /* Write data. */
    if (M.isContinuous()){
       out.write((char *)M.data,cols*rows*chan*eSiz);
    }
    else{
       return 0;
    }
    out.close();
    return 1;
}

/* Read matrix from binary file */
int readMat( const char *filename, Mat& M)
{
    ifstream in(filename, ios::in|ios::binary);
    if (!in){
       M.data = NULL;
       return 0;
    }
    int cols;
    int rows;
    int chan;
    int eSiz;

    /* Read header */
    in.read((char*)&cols,sizeof(cols));
    in.read((char*)&rows,sizeof(rows));
    in.read((char*)&chan,sizeof(chan));
    in.read((char*)&eSiz,sizeof(eSiz));

    /* Determine type of the matrix */
    int type = 0;
    switch (eSiz){
    case sizeof(char):
         type = CV_8UC(chan);
         break;
    case sizeof(float):
         type = CV_32FC(chan);
         break;
    case sizeof(double):
         type = CV_64FC(chan);
         break;
    }

    /* Alocate Matrix. */
    M = Mat(rows,cols,type,Scalar(1));

    /* Read data. */
    if (M.isContinuous()){
       in.read((char *)M.data,cols*rows*chan*eSiz);
    }
    else{
       return 0;
    }
    in.close();
    return 1;
}

int getMatType ( const char *typeName)
{
    if(strcmp("CV_8UC1", typeName) == 0)
        return 0;
    else if(strcmp("CV_8UC2", typeName) == 0)
        return 8;
    else if(strcmp("CV_8UC3", typeName) == 0)
        return 16;
    else if(strcmp("CV_32FC1", typeName) == 0)
        return 5;
    else if(strcmp("CV_32FC2", typeName) == 0)
        return 13;
    else if(strcmp("CV_32FC3", typeName) == 0)
        return 21;
}

int getThresholdType ( const char *typeName)
{
    if(strcmp("THRESH_BINARY", typeName) == 0)
        return THRESH_BINARY;
    else if(strcmp("THRESH_BINARY_INV", typeName) == 0)
        return THRESH_BINARY_INV;
    else if(strcmp("THRESH_TRUNC", typeName) == 0)
        return THRESH_TRUNC;
    else if(strcmp("THRESH_TOZERO", typeName) == 0)
        return THRESH_TOZERO;
    else if(strcmp("THRESH_TOZERO_INV", typeName) == 0)
        return THRESH_TOZERO_INV;
}

int getColorFlag(int colorflag)
{
    switch (colorflag){
			case 0:
                return CV_LOAD_IMAGE_GRAYSCALE;
				break;
			case 1:
                return CV_LOAD_IMAGE_COLOR;
				break;
			case -1:
				return CV_LOAD_IMAGE_UNCHANGED;
				break;
			default :
				return CV_LOAD_IMAGE_COLOR;
	    }
}

int getMorphOperation ( const char *typeName)
{
    if(strcmp("MORPH_OPEN", typeName) == 0)
        return MORPH_OPEN;
    else if(strcmp("MORPH_CLOSE", typeName) == 0)
        return MORPH_CLOSE;
    else if(strcmp("MORPH_GRADIENT", typeName) == 0)
        return MORPH_GRADIENT;
    else if(strcmp("MORPH_TOPHAT", typeName) == 0)
        return MORPH_TOPHAT;
    else if(strcmp("MORPH_BLACKHAT", typeName) == 0)
        return MORPH_BLACKHAT;
}

int ByteArrayToANN(char *annfile, CvANN_MLP* ann)
{
    char *buffer;
    long size;
	ifstream file (annfile, ios::in|ios::binary|ios::ate);
    if(!file){ return 0; }

    size = file.tellg();
    file.seekg (0, ios::beg);
    buffer = new char [size];
    file.read (buffer, size);
    file.close();

	CvFileStorage *cvfs = cvOpenFileStorage(annfile, NULL, CV_STORAGE_READ);
	if (cvfs != NULL) {
		ann->read(cvfs, cvGetFileNodeByName(cvfs, NULL, "CIA_Neuron"));
		cvReleaseFileStorage(&cvfs);
	} else {
        return 0;
    }
}

void getOutputFilename (char **filename, const char *toAppend)
{

    time_t now = time(0);
    strftime(*filename, sizeof(filename)*60,"/home/lluu/thesis/RESULT/%Y%m%d_%H%M%S", localtime(&now));
    /* to do
     * do check if there's no data in toAppend
     */
    //strcat(BASE_DIR,*filename); 
    //if(!toAppend)
    strcat(*filename,toAppend);
}



