#pragma once
#include <string>
using namespace std;
class BloomFilterStats {
private:
	static bool instanceFlag;
	static BloomFilterStats* bloomFilterStat;
	BloomFilterStats() {};

	unsigned int bloom_filter_sizeInBit;
	unsigned int bloom_filter_hashFunctionsNumber;
	unsigned int bloom_filter_hashFunctionId;


public:
	static BloomFilterStats* getInstance();
	void set_bloom_filter_sizeInBit(unsigned int bloom_filter_sizeInBit);
	void set_bloom_filter_hashFunctionsNumber(unsigned int bloom_filter_sizeInBit);
	void set_bloom_filter_hashFunctionId(unsigned int bloom_filter_sizeInBit);

	string getStringOfAllStats();
	~BloomFilterStats();
	
};