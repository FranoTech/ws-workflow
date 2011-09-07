#include <iostream>
#include <string.h>
#include <cstring>

using namespace std;
void editSrc( string& );
void testConst (const char*);
void ref (char*&);
void refAgain (char*&);

int main( int argc, char** argv )
{
	/* //edit string 
	string src = "test from source";
	cout << src << endl;
	editSrc(src);
	cout << src << endl;
	*/
	/* //test const char
	const char *s = "test";
	testConst(s);
	*/
	
	char *s = "test in main";
	cout << s <<endl;
	ref(s);
	
	cout << s <<endl;

	return 0;
	
}

void editSrc (string &dst)
{
	dst = "edited";
	
}

void testConst(const char* cs)
{
	cout<<cs<<endl;
	
}

void ref(char *&sr)
{
	sr = "test in ref";
	cout << sr << endl;
	
	refAgain(sr);

}

void refAgain(char *&srr)
{
	srr = "test in refAgain";
	cout << srr << endl;
}
