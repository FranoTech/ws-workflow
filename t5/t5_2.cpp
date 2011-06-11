#include <iostream>
#include "cv.h"
#include "highgui.h"
#include <stdio.h>
#define MAXSIZE (10000)
using namespace std;

int main()
{
	char* src = "img.jpg";
//	char* dst = "img3.jpg";
	unsigned char image[MAXSIZE] = {};
	
	FILE *fs = fopen(src,"r");
	int i;
	unsigned char c;	
	if(!fs){
		cout<<"can not open file"<<endl;
	}

    for(i = 0; i < MAXSIZE; i++){
		if((c = fgetc(fs)) == EOF){
			break;
		}
		image[i] = c;
	}
	
//	cout<<"image = "<<image<<endl;

//	IplImage* img = cvLoadImage(src,0);
//	cout<<"img->imageData = "<<img->imageData<<endl;

	return 0;
}

