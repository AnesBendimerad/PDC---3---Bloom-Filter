#include "stdafx.h"
#include "BloomFilterStats.h"

bool BloomFilterStats::instanceFlag = false;
BloomFilterStats* BloomFilterStats::bloomFilterStat = nullptr;

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

void BloomFilterStats::set_bloom_filter_hashFunctionId(unsigned int bloom_filter_hashFunctionId)
{
	BloomFilterStats::bloom_filter_hashFunctionId = bloom_filter_hashFunctionId;
}

string BloomFilterStats::getStringOfAllStats()
{
	string returned="";
	returned += "size of bloom filter : " + to_string(bloom_filter_sizeInBit)+"\n";
	returned += "nomber of hash function of bloom filter : " + to_string(bloom_filter_hashFunctionsNumber) + "\n";
	returned += "type of hash function : " + to_string(bloom_filter_hashFunctionId) + "\n";
	return returned;
}

BloomFilterStats::~BloomFilterStats()
{
	instanceFlag = false;
}
