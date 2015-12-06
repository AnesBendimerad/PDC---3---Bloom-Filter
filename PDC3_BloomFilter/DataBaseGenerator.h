#pragma once
#include <cassandra.h>
#include "DataBaseConfiguration.h"
class DataBaseGenerator {
private:
	DataBaseConfiguration dataBaseConfiguration;
public:
	DataBaseGenerator(DataBaseConfiguration dataBaseConfiguration, unsigned int dataBaseSize);
	bool generate();
	~DataBaseGenerator();
};