#include "../headerfile.cpp"
#include "../myLog.h"
#include "../config.h"
#include "soapH.h"
#include "CIA.nsmap"

#define FILENAME_SIZE 75
#define MAX_THREAD 4

using namespace cv;

/* helper function */
int saveMat( const std::string& filename, const Mat& M);
int readMat( const std::string& filename, Mat& M);
int getMatType (const std::string& typeName);
int getColorFlag(int colorflag);
void getOutputFilename (std::string& filename, std::string& toAppend);
void getMemoryUsage (double& vm_usage, double& resident_set);
void getConfig (bool &timeChecking, bool &memoryChecking);
int getMatDepth (const std::string& depth);
bool fileExists(const std::string& filename)
{
    struct stat buf;
    if (stat(filename.c_str(), &buf) != -1)
    {
        return true;
    }
    return false;
}
template <typename T>
std::string NumberToString ( T Number )
{
	std::stringstream ss;
	ss << Number;
	return ss.str();
}


/* Global Configuration */
std::string BASE_DIR = "/home/lluu/thesis/result/";
std::string ERROR_FILENAME = "";
std::string DEFAULTVAL = "";
std::string CONFIG_FILE = "/home/lluu/thesis/result/config.cfg";
double start, end; /* time checking */


int main(int argc, char **argv)
{
	LOG_FILENAME = "/home/lluu/thesis/result/SERVICE_LOG";
    struct soap soap;
    soap_init(&soap);
	
    if (argc < 2)		// no args: assume this is a CGI application
    {
        soap_serve(&soap);	// serve request
        soap_destroy(&soap);// cleanup class instances
        soap_end(&soap);	// cleanup
    }
    return 0;
}


int ns__removeSmallCell(struct soap *soap,
                        char  *InputMatFilename,
                        ns__RemoveSmallCell &out)
{
    bool timeChecking, memoryChecking;
    getConfig(timeChecking, memoryChecking);
    
    if(timeChecking){
        start = omp_get_wtime();
    }

    Mat src; //input_morph
    if(!readMat(inputMatFilename, src))
    {
        Log(logERROR) << "removeSmallCell :: can not read bin file" << std::endl;
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
    } catch( cv::Exception& e ) {
            Log(logERROR) << e.what() << std::endl;
            return soap_receiver_fault(soap, e.what(), NULL);
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
    out->keepedArea = (char*)soap_malloc(soap, FILENAME_SIZE);
    out->biggerArea = (char*)soap_malloc(soap, FILENAME_SIZE);

    time_t now = time(0);
    strftime(out.keepedArea, sizeof(out.keepedArea)*FILENAME_SIZE, "/home/lluu/thesis/result/%Y%m%d_%H%M%S_keepedArea", localtime(&now));
    strftime(out.biggerArea, sizeof(out.biggerArea)*FILENAME_SIZE, "/home/lluu/thesis/result/%Y%m%d_%H%M%S_biggerArea", localtime(&now));
    
    
    
    /* save to bin */
    if(!saveMat(out.keepedArea, outSingle))
    {
        Log(logERROR) << "removeSmallCell:: saved mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "removeSmallCell:: saved mat to binary file", NULL);
    }

    if(!saveMat(out.biggerArea, tmp))
    {
        Log(logERROR) << "removeSmallCell:: saved mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "removeSmallCell:: saved mat to binary file", NULL);
    }

    src.release();
    tmp.release();
    outSingle.release();

    src.release();

    if(timeChecking) 
    { 
        end = omp_get_wtime();
        Log(logINFO) << "removeSmallCell :: " << "time elapsed " << end-start << std::endl;
    }
    
    if(memoryChecking)
    {   
        double vm, rss;
        getMemoryUsage(vm, rss);
        Log(logINFO)<< "removeSmallCell :: VM usage :" << vm << std::endl 
                    << "Resident set size :" << rss << std::endl;
    }

    return SOAP_OK;
}


int ns__scanningCell(struct soap *soap,
                        char *biggerArea,
                        char *keepArea,
                        char **OutputMatFilename)
{

    bool timeChecking, memoryChecking;
    getConfig(timeChecking, memoryChecking);
    if(timeChecking){
        start = omp_get_wtime();
    }

    Mat src; //input_morph
    if(!readMat(biggerArea, src))
    {
        Log(logERROR) << "scanningCell :: can not read bin file" << std::endl;
        return soap_receiver_fault(soap, "scanningCell :: can not read bin file", NULL);
    }
    
    Mat out_single;
    if(!readMat(keepArea, out_single))
    {
        Log(logERROR) << "scanningCell :: can not read bin file" << std::endl;
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
        Log(logERROR) << "scanningCell :: save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "scanningCell :: save mat to binary file", NULL);
    }

    src.release();
    srcTmp.release();
    src32FC1.release();
    out_single.release();

    if(timeChecking) 
    { 
        end = omp_get_wtime();
        Log(logINFO) << "scanningCell :: " << "time elapsed " << end-start << std::endl;
    }
    
    if(memoryChecking)
    {   
        double vm, rss;
        getMemoryUsage(vm, rss);
        Log(logINFO)<< "scanningCell :: VM usage :" << vm << std::endl 
                    << "Resident set size :" << rss << std::endl;
    }

    return SOAP_OK;
}

int ns__separateCell(struct soap *soap,
                        char *input1, //outSingle
                        char *input2, //outMorph
                        char **OutputMatFilename)
{
    bool timeChecking, memoryChecking;
    getConfig(timeChecking, memoryChecking);
    if(timeChecking){
        start = omp_get_wtime();
    }

    Mat outSingle;
    if(!readMat(input1, outSingle))
    {
        Log(logERROR) "sep :: can not read bin file" << std::endl;
        return soap_receiver_fault(soap, "sep :: can not read bin file", NULL);
    }

    Mat tmp;
    outSingle.convertTo(tmp, CV_8UC1);
    
    int count = 1;
    int c = 0;
    int n = 0;
    const Point *p;
    vector<vector<Point> > contours;
    findContours(   tmp, contours, CV_RETR_EXTERNAL,
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
        Log(logERROR) << "sep :: can not read bin file" << std::endl;
        return soap_receiver_fault(soap, "sep :: can not read bin file", NULL);

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
        Log(logERROR) "can not save mat to jpg file" << std::endl;
        return soap_receiver_fault(soap, "sep:: save mat to binary file", NULL);
    }

    /* generate output file name */
    *OutputMatFilename = (char*)soap_malloc(soap, FILENAME_SIZE);
    getOutputFilename(OutputMatFilename,"_sep");

    /* save to bin */
    if(!saveMat(*OutputMatFilename, cell))
    {
        Log(logERROR) << "sep:: save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "sep:: save mat to binary file", NULL);
    }

    tmp8UC1.release();
    cell.release();
    outSingle.release();

    if(timeChecking) 
    { 
        end = omp_get_wtime();
        Log(logINFO) << "sep :: " << "time elapsed " << end-start << std::endl;
    }
    
    if(memoryChecking)
    {   
        double vm, rss;
        getMemoryUsage(vm, rss);
        Log(logINFO)<< "sep:: VM usage :" << vm << std::endl 
                    << "Resident set size :" << rss << std::endl;
    }

    return SOAP_OK;
    
}

int ns__prepareResult(struct soap *soap,
                        char *inputMatFilename,
                        char *afterthresNN,
                        char **OutputMatFilename)
{
    bool timeChecking, memoryChecking;
    getConfig(timeChecking, memoryChecking);
    if(timeChecking){
        start = omp_get_wtime();
    }


    Mat src;
    if(!readMat(inputMatFilename, src))
    {
        Log(logERROR) << "prepareResult :: can not read bin file" << std::endl;
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
        Log(logERROR) << "output1Ch:: can not read bin file" << std::endl;
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
        Log(logERROR) << "prepareResult :: save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "result:: save mat to binary file", NULL);
    }

    src.release();

    if(timeChecking) 
    { 
        end = omp_get_wtime();
        Log(logINFO) << "prepareResult :: " << "time elapsed " << end-start << std::endl;
    }
    
    if(memoryChecking)
    {   
        double vm, rss;
        getMemoryUsage(vm, rss);
        Log(logINFO)<< "prepareResult :: VM usage :" << vm << std::endl 
                    << "Resident set size :" << rss << std::endl;
    }

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
    bool timeChecking, memoryChecking;
    getConfig(timeChecking, memoryChecking);
    if(timeChecking){
        start = omp_get_wtime();
    }

    Mat src; //must be 3ch image
    if(!readMat(inputMatFilename, src))
    {
        Log(logERROR) << "trainANN :: can not read bin file" << std::endl;
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
        Log(logERROR) << "trainANN :: can not load byte array to neural" << std::endl;
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
        Log(logERROR) << "trainANN :: save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "trainANN :: save mat to binary file", NULL);
    }

    src.release();
    resultNN.release();
    cvReleaseMat(&output1Ch);


    if(timeChecking) 
    { 
        end = omp_get_wtime();
        Log(logINFO) << "trainANN :: " << "time elapsed " << end-start << std::endl;
    }
    
    if(memoryChecking)
    {   
        double vm, rss;
        getMemoryUsage(vm, rss);
        Log(logINFO)<< "trainANN :: VM usage :" << vm << std::endl 
                    << "Resident set size :" << rss << std::endl;
    }

    return SOAP_OK;
}


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
    strftime(*filename, sizeof(filename)*60,"%Y%m%d_%H%M%S", localtime(&now));
    strcat(*filename,toAppend);
    
    char* temp;
    temp = (char*)malloc(strlen(*filename) + strlen(BASE_DIR) + 1);
    
    strcpy(temp, BASE_DIR);
    strcat(temp, *filename);
    strcpy(*filename, temp);
    free(temp);
}


void getMemoryUsage (double& vm_usage, double& resident_set)
{
    /* virtual mamory usage */
    vm_usage     = 0.0;
    /* The resident set size is the portion of a process's memory that is held in RAM */
    resident_set = 0.0;

    std::ifstream stat_stream("/proc/self/stat",std::ios::in);
    std::string pid, comm, state, ppid, pgrp, session, tty_nr;
    std::string tpgid, flags, minflt, cminflt, majflt, cmajflt;
    std::string utime, stime, cutime, cstime, priority, nice;
    std::string O, itrealvalue, starttime;

    unsigned long vsize;
    long rss;

    stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr
               >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt
               >> utime >> stime >> cutime >> cstime >> priority >> nice
               >> O >> itrealvalue >> starttime >> vsize >> rss;

    stat_stream.close();

    long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
    vm_usage     = vsize / 1024.0;
    resident_set = rss * page_size_kb;
}



void getConfig (bool &timeChecking, bool &memoryChecking)
{
    ConfigFile cfg( CONFIG_FILE.c_str() );
    timeChecking = cfg.getValueOfKey<bool>("timeChecking", false);
    memoryChecking = cfg.getValueOfKey<bool>("memoryChecking", false);
}
