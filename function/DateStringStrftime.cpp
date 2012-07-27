#include <string>
#include <iostream>

using namespace std;

void getDate (string& d)
{
	time_t now = time(0);
	char tmp[60] = {0};
    strftime(tmp, sizeof(tmp),"%Y%m%d_%H%M%S", localtime(&now));
	
	//~ d = tmp;
	string test = ".txt";
	d = tmp + test;
	}	

int main ()
{
	string date;
	getDate(date);
	cout<<date<<endl;
	cout<<date.size()<<endl;

	return 0;
}