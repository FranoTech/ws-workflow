#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#define limit 9999

using namespace std;

int rand_lim() {
/* return a random number between 0 and limit inclusive.
 */

    int divisor = RAND_MAX/(limit+1);
    int retval;

    do { 
        retval = rand() / divisor;
    } while (retval > limit);

    return retval;
}

int ran_key(){
    srand(time(NULL));  
    return rand()%10000;
}

int main (){
    
    int r;
    int *ran = &r;
    //*key = rand_lim();
    //cout<<"key = "<<*key<<endl;
    
    *ran = ran_key();
    
    cout<<"rand = "<<*ran<<endl; 

    return 0;
}
