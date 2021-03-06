#include "stdafx.h"
#include "BloomFilterStats.h"
#include "BloomFilterUtilities.h"

bool BloomFilterStats::instanceFlag = false;
BloomFilterStats* BloomFilterStats::bloomFilterStat = nullptr;

BloomFilterStats::BloomFilterStats()
{
	dataBase_size = 0;

	bloom_filter_sizeInBit = 0;
	bloom_filter_hashFunctionsNumber = 0;
	bloom_filter_hashFunctionName = "";

	number_of_one_in_filter = 0;
}

BloomFilterStats * BloomFilterStats::getInstance()
{
	if (!instanceFlag)
	{
		BloomFilterStats::bloomFilterStat = new BloomFilterStats();
		BloomFilterStats::instanceFlag = true;
		return BloomFilterStats::bloomFilterStat;
	}
	else
	{
		return BloomFilterStats::bloomFilterStat;
	}
}

void BloomFilterStats::set_bloom_filter_sizeInBit(unsigned int bloom_filter_sizeInBit)
{
	BloomFilterStats::bloom_filter_sizeInBit = bloom_filter_sizeInBit;
}

void BloomFilterStats::set_bloom_filter_hashFunctionsNumber(unsigned int bloom_filter_hashFunctionsNumber)
{
	BloomFilterStats::bloom_filter_hashFunctionsNumber = bloom_filter_hashFunctionsNumber;
}

void BloomFilterStats::set_bloom_filter_hashFunctionName(string bloom_filter_hashFunctionName)
{
	BloomFilterStats::bloom_filter_hashFunctionName = bloom_filter_hashFunctionName;
}

void BloomFilterStats::set_number_of_one_in_filter(unsigned int numberOfOnes)
{
	number_of_one_in_filter = numberOfOnes;
}

void BloomFilterStats::increment_number_of_one_in_filter(unsigned int newInsertedOneNumber)
{
	number_of_one_in_filter += newInsertedOneNumber;
}

void BloomFilterStats::set_bloom_filter_fp_rates()
{
	bloom_filter_theorical_fp_rate = estimateTheoricalFPRate(dataBase_size, bloom_filter_sizeInBit, bloom_filter_hashFunctionsNumber);
	bloom_filter_fp_rate_with_filling_rate = estimateFPRateWithFillingRate((1.0*number_of_one_in_filter) / bloom_filter_sizeInBit, bloom_filter_hashFunctionsNumber);
}

void BloomFilterStats::set_dataBase_size(unsigned int dataBase_size)
{
	BloomFilterStats::dataBase_size = dataBase_size;
}

string BloomFilterStats::getStringOfAllStats()
{
	string returned="";
	returned += "Stats : \n";
	returned += "\t Database size : " + to_string(dataBase_size) + "\n";
	returned += "\t Size of bloom filter : " + to_string(bloom_filter_sizeInBit) + "\n";
	returned += "\t Number of hash function of bloom filter : " + to_string(bloom_filter_hashFunctionsNumber) + "\n";
	returned += "\t Type of hash function : " + bloom_filter_hashFunctionName + "\n";
	returned += "\t Bloom Filter Filing rate : " + to_string(100*((1.0*number_of_one_in_filter)/ bloom_filter_sizeInBit)) +"%"+"\n";
	returned += "\t Bloom Filter theorical false positive rate : " + to_string(100 * bloom_filter_theorical_fp_rate)+"%"+"\n";
	returned += "\t Bloom Filter false positive rate using filling rate : " + to_string(100 * bloom_filter_fp_rate_with_filling_rate) + "%";
	return returned;
}

BloomFilterStats::~BloomFilterStats()
{
	instanceFlag = false;
}
