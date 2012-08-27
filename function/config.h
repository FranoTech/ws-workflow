#ifndef __CONFIGURGE_H__
#define __CONFIGURGE_H__
#endif


class Configure {
	public:
		bool timeChecking;
		bool memoryChecking;
		
		friend std::ostream& operator<<(std::ostream& os, const Configure& c)
		{
			os << c.timeChecking << '\n';
			os << c.memoryChecking;
			return os;
		}
		
		friend std:: istream& operator>>(std::istream& is, Configure& c)
		{
			is >> c.timeChecking >> c.memoryChecking;
			return is;
		}
 };
 
bool readConfig ()
 {
	//~ Configure config;
	std::ifstream inConfig(CONFIG_FILE.c_str(), std::ios::in | std::ios::binary);
	if(!inConfig)
	{
		std::cerr << "Config File could not be opened. Please run InitialService first." << std::endl;
		exit(1);
	}
	inConfig >> config;
	
	timeChecking = config.timeChecking;
	memoryChecking = config.memoryChecking;