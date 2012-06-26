/* gsoap */
#include "soapH.h"
#include "standAlone.nsmap"
/* opencv */
#include <cv.h>
#include <ml.h>
/* STL */
#include <sstream>
#include <iostream>
#include <string.h>
#include <cstring>
#include <fstream>
/* system */
#include <sys/types.h>
#include <sys/stat.h> //time_t fstat
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
/* omp */
#include <omp.h>

/* service from OpenCV */
#include "loadMat.cpp"
#include "MatToJPG.cpp" 
#include "convertTo.cpp" 
#include "bitwiseNot.cpp" 
#include "bitwiseOr.cpp" 
#include "bitwiseAnd.cpp" 
#include "viewImage.cpp" 
#include "dilate.cpp" 
#include "erode.cpp" 
#include "morphologyEx.cpp" 
#include "threshold.cpp"

/* service based on case study*/ 
#include "trainANN.cpp" 
#include "scanningCell.cpp" 
#include "separateCell.cpp" 
#include "removeSmallCell.cpp" 
#include "prepareResult.cpp"

 
