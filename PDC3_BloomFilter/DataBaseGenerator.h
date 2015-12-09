#pragma once
#include <cassandra.h>
#include "DataBaseConfiguration.h"
#include<vector>

unsigned const int documentNumberSize = 25;
unsigned const int documentTypeSize = 3;
unsigned const int countryCodeSize = 3;

class DataBaseGenerator {
private:
	DataBaseConfiguration dataBaseConfiguration;
	unsigned int dataBaseSize;
	std::vector<std::string> * countryCode;
	string RandomString(unsigned int len);
	bool createDB();
	std::vector<std::string> * loadCountryCode();
	string RandomCountryCode();

public:
	DataBaseGenerator(DataBaseConfiguration dataBaseConfiguration, unsigned int dataBaseSize);
	bool createAndGenerateDB();
	~DataBaseGenerator();
};