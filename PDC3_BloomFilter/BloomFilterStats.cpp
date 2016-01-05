#include "stdafx.h"
#include "BloomFilterStats.h"

bool BloomFilterStats::instanceFlag = false;
BloomFilterStats* BloomFilterStats::bloomFilterStat = nullptr;

BloomFilterStats::BloomFilterStats()
{
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

string BloomFilterStats::getStringOfAllStats()
{
	string returned="";
	returned += "Stats : \n";
	returned += "\t Size of bloom filter : " + to_string(bloom_filter_sizeInBit) + "\n";
	returned += "\t Number of hash function of bloom filter : " + to_string(bloom_filter_hashFunctionsNumber) + "\n";
	returned += "\t Type of hash function : " + bloom_filter_hashFunctionName + "\n";
	returned += "\t Bloom Filter Filing rate : " + to_string(100*((1.0*number_of_one_in_filter)/ bloom_filter_sizeInBit));
	return returned;
}

BloomFilterStats::~BloomFilterStats()
{
	instanceFlag = false;
}
