#include <fstream>
#include <iostream>
#include <sstream>

class Configure
{
	public:
		bool timeChecking;
		bool memChecking;
		bool keepLoging;
		
		friend std::ostream& operator<<(std::ostream& os, const Configure& c)
		{
			os << c.timeChecking << '\n';
			os << c.memChecking << '\n';
			os << c.keepLoging;
			return os;
		}
		
		friend std:: istream& operator>>(std::istream& is, Configure& c)
		{
			is >> c.timeChecking >> c.memChecking >> c.keepLoging;
			return is;
		}
};

int main()
{
	Configure c1;
	Configure c2;

	c1.timeChecking = true;
	c1.memChecking = false;
	c1.keepLoging = true;
	
	std::ofstream ofs("iostream.txt", std::ios::out|std::ios::binary);
	ofs << c1; // store the object to file
	ofs.close();

	std::ifstream ifs("iostream.txt", std::ios::in|std::ios::binary);
	// read the object back in
	if(ifs >> c2)
	{
		// read was successful therefore s2 is valid
		std::cout << c2 << '\n'; // print s2 to console
	}

	return 0;
}
