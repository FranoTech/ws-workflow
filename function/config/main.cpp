#include <iostream>
#include <string>
#include <typeinfo>

#include "configfile.h"

int main()
{
	ConfigFile cfg("config.cfg");

	bool exists = cfg.keyExists("car");
	std::cout << "car key: " << std::boolalpha << exists << "\n";
	exists = cfg.keyExists("fruits");
	std::cout << "fruits key: " << exists << "\n";

	std::string someValue = cfg.getValueOfKey<std::string>("mykey", "Unknown");
	std::cout << "value of key mykey: " << someValue << "\n";
	std::string carValue = cfg.getValueOfKey<std::string>("car");
	std::cout << "value of key car: " << carValue << "\n";
	double doubleVal = cfg.getValueOfKey<double>("double");
	std::cout << "value of key double: " << doubleVal + 1<< "\n\n";
	
	return 0;
}