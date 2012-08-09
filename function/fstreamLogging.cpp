#include <fstream>
#include <string>
#include <iostream>

class Log {
	public:
		Log () : enabled(false) {}
		void enableLog () { enabled = true; }
		void disableLog () { enabled = false; }
		
		Log& operator<< (std::) {
			if (enabled)
			{ 
				stream.open(fname, std::ios::in | std::ios::app);
				std::cout<<"wrote to test";
				stream << rsh << "\n";
			}
			return *this;
		}
		
		~Log()
		{
			stream.close();
		}
		
		void initLog(std::string& f) 
		{
			fname = f;
			enableLog();
		}
	
	private:
		std::ostream &stream;
		bool enabled;
		std::string fname;
};

int main ()
{	
	//~ std::fstream ss;
	Log log;
	std::string fname = "test";
	log.initLog(fname);
	log<<"test";
	return 0;
}