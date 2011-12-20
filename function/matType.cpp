
//result
/*
CV_8UC1=0
CV_8UC2=8
CV_8UC3=16
CV_32FC1=5
CV_32FC2=13
CV_32FC3=21
*/

#include <iostream>
#include <fstream>
#include <string.h>
#include <cv.h>
#include <highgui.h>

using namespace std;
using namespace cv;

int getMatType ( const char *typeName);
int main (int argc, char** argv){


    cout<<"CV_8UC1="<<CV_8UC1<<endl;
    cout<<"CV_8UC2="<<CV_8UC2<<endl;
    cout<<"CV_8UC3="<<CV_8UC3<<endl;
    cout<<"CV_32FC1="<<CV_32FC1<<endl;
    cout<<"CV_32FC2="<<CV_32FC2<<endl;
    cout<<"CV_32FC3="<<CV_32FC3<<endl; 
 

/* 
    char type[10];
    cout<<"type : ";
    cin.getline(type, 10);
    cout<<getMatType(type);
*/
    return 0;
    
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
