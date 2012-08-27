#include <iostream>
#include <string>
#include <typeinfo>

#include "config.h"

int main()
{
	ConfigFile cfg("config.cfg");

	bool time = cfg.getValueOfKey<bool>("timeChecking", true);
	std::cout << "value of time: " << time << "\n";
	
	int mem = cfg.getValueOfKey<int>("memoryChecking", 1);
	std::cout << "value of mem: " << mem << "\n";
	
	if(mem){
		std::cout<<"true\n";
	} else {
		std::cout<<"false\n";
	}
	
	return 0;
}