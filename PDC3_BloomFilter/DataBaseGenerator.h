#pragma once
#include <cassandra.h>
#include "RandomAdditionalOperations.h"
#include "DataBaseConfiguration.h"
#include<vector>

#define COUNTRY_CODES_BAG { "ABW", "AFG", "AGO", "AIA","ALA" , "ALB", "AND", "ARE", "ARG", "ARM","ASM","ATA","ATF","ATG","AUS","AUT","AZE","BDI","BEL","BEN","BES","BFA","BGD","BGR","BHR","BHS","BIH","BLM","BLR","BLZ","BMU","BOL","BRA","BRB","BRN","BTN","CMR","COD","COG","COK","COL","COM","CPV","CRI","CUB","CUW","CXR","CYM","CYP","CZE","DEU","DJI","MAR","MCO","MDA"}

class DataBaseGenerator {
private:
	DataBaseConfiguration dataBaseConfiguration;
	unsigned int dataBaseSize;
	std::vector<std::string> * countryCode;
	bool createDB();
	string RandomCountryCode();

public:
	DataBaseGenerator(DataBaseConfiguration dataBaseConfiguration, unsigned int dataBaseSize);
	bool createAndGenerateDB();
	~DataBaseGenerator();
};