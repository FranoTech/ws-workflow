#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h> // time
#include <stdlib.h>  //rand()
#include <unistd.h>
#include <time.h>
#include <string.h>

using namespace std;

clock_t startm, stopm;
#define START if ( (startm = clock()) == -1) {cerr<<"Error calling clock"<<endl; exit(1);}
#define STOP if ( (stopm = clock()) == -1) {cerr<<"Error calling clock"<<endl; exit(1);}
#define PRINTTIME cerr<<((double)stopm-startm)/CLOCKS_PER_SEC<<" seconds used by the processor."<<endl;



int main(int argc, char **argv)
{ 		
		START;
		ostringstream sout;
        char* filename;
        time_t init = time(0);
        tm* tm = localtime(&init);
        sout<<"/home/lluu/dir/"<<1900+tm->tm_year<<1+tm->tm_mon<<tm->tm_mday<<tm->tm_hour<<tm->tm_min<<":MatToJPG.xml";
        size_t len = sout.str().length();
		filename = new char[len+1];
        memcpy(filename,sout.str().c_str(),len);
        cout<<filename<<endl;
		STOP;
		PRINTTIME;
		//ostringstream sout;
        //sout<<filename<<".jpg";
        //size_t len = sout.str().length();
        //OutputFilename = new char[len+1];
        //memcpy(OutputFilename,sout.str().c_str(),len);
		
		
		return 0;
}
