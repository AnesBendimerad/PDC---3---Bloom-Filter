#pragma once
#include <cassandra.h>
#include "RandomAdditionalOperations.h"
#include "DataBaseConfiguration.h"
#include<vector>


class DataBaseGenerator {
private:
	DataBaseConfiguration dataBaseConfiguration;
	unsigned int dataBaseSize;
	std::vector<std::string> * countryCode;
	bool createDB();
	std::vector<std::string> * loadCountryCode();
	string RandomCountryCode();

public:
	DataBaseGenerator(DataBaseConfiguration dataBaseConfiguration, unsigned int dataBaseSize);
	bool createAndGenerateDB();
	~DataBaseGenerator();
};