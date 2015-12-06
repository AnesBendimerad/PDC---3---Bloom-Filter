#pragma once
#include <cassandra.h>
#include "DataBaseConfiguration.h"

unsigned const int documentNumberSize = 10;
unsigned const int documentTypeSize = 10;
unsigned const int countryCodeSize = 3;

class DataBaseGenerator {
private:
	DataBaseConfiguration dataBaseConfiguration;
	unsigned int dataBaseSize;
	string RandomString(unsigned int len);
	bool executeQuery(string query);

public:
	DataBaseGenerator(DataBaseConfiguration dataBaseConfiguration, unsigned int dataBaseSize);
	bool generate();
	~DataBaseGenerator();
};