#pragma once
#include <string>
using namespace std;

class BloomFilterStats {
private:
	static bool instanceFlag;
	static BloomFilterStats* bloomFilterStat;
	BloomFilterStats();

	unsigned int bloom_filter_sizeInBit;
	unsigned int bloom_filter_hashFunctionsNumber;
	string bloom_filter_hashFunctionName;

	unsigned int number_of_one_in_filter;


public:
	static BloomFilterStats* getInstance();
	void set_bloom_filter_sizeInBit(unsigned int bloom_filter_sizeInBit);
	void set_bloom_filter_hashFunctionsNumber(unsigned int bloom_filter_hashFunctionsNumber);
	void set_bloom_filter_hashFunctionName(string bloom_filter_hashFunctionName);
	void increment_filing_rate(unsigned int newInsertedOneNumber);

	string getStringOfAllStats();
	~BloomFilterStats();
	
};