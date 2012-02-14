#include <stdio.h>
#include <time.h>

#define LOGNAME_FORMAT "/home/lluu/dir/%Y%m%d_%H%M%S/morp"
#define LOGNAME_SIZE 40

int main(int argc, char **argv)
{ 
    static char name[LOGNAME_SIZE];
    time_t now = time(0);
    strftime(name, sizeof(name), LOGNAME_FORMAT, localtime(&now));
    
    OutputFilename = new char[50];
    time_t now = time(0);
    strftime(OutputFilename, sizeof(OutputFilename), "/home/lluu/dir/%Y%m%d_%H%M%S_biThreshold.jpg", localtime(&now));
        
    //printf("%s\n",name);
    printf("%s\n",OutputFilename);
    return 0;
}
