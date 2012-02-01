#include <cv.h>
//#include <highgui.h>
#include <omp.h>
#include <fstream>

using namespace std;
using namespace cv;

int saveMat( const char *filename, const Mat& M);
int readMat( const char *filename, Mat& M);

int main(int argc, char **argv)
{

    double start, end;
    start = omp_get_wtime();

    //~ Mat src = imread(argv[1],0);
    Mat src = imread(argv[1],0);

    cout<<"1"<<endl;
    threshold(src, src, 127.0, 255.0, CV_THRESH_BINARY);
    Mat se;
    Mat dst = Mat(src.rows, src.cols, src.type());
    //Mat tmpdst;
    Size seSize(3, 3);
    Point seAnc(1, 1);

    se = getStructuringElement(MORPH_ELLIPSE, seSize, seAnc);
    morphologyEx(src, dst,MORPH_OPEN, se, seAnc);
        
    /* convert src type to 8UC1 */

    dst.convertTo(dst, CV_8UC1);
    cout<<"dst.type = "<<dst.type()<<endl;
    Mat tmp = Mat(dst.rows, dst.cols, CV_32FC1);
    Mat outSingle = Mat::zeros(dst.rows, dst.cols, CV_32FC1);
    vector<vector<Point> > contours;
    double area = 0;
    const Point* p;
    int n = 0;
    size_t i = 0;
    findContours(dst, contours, CV_RETR_EXTERNAL,
                    CV_CHAIN_APPROX_SIMPLE, Point(0,0));
    cout<<"2"<<endl;
    #pragma omp parallel for private(i, n, p, area) shared(contours, tmp)
    for(i = 0; i< contours.size(); i++)  
    {
        p = &contours[i][0];
        n = (int)contours[i].size();
        area = fabs(contourArea(Mat(contours[i])));
        cout<<"tid = "<<omp_get_thread_num()<<endl;
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
    cout<<"3"<<endl;
    contours.clear();
    
    /* save to bin */
    if(!saveMat("keepArea", outSingle))
    {
        cerr << "removeSmallCell:: save mat to binary file" << endl;
    }

    if(!saveMat("biggerArea", tmp))
    {
        cerr << "removeSmallCell:: save mat to binary file" << endl;
    }
    dst.release();
    src.release();
    tmp.release();
    outSingle.release();

    end = omp_get_wtime();
    cerr<<"ns__removeSmallCell"<<"time elapsed "<<end-start<<endl;
    
    return 0;
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

