#pragma once
#include <string>
using namespace std;

class BloomFilterStats {
private:
	static bool instanceFlag;
	static BloomFilterStats* bloomFilterStat;
	BloomFilterStats();

	unsigned int dataBase_size;
	unsigned int bloom_filter_sizeInBit;
	unsigned int bloom_filter_hashFunctionsNumber;
	string bloom_filter_hashFunctionName;

	unsigned int number_of_one_in_filter;
	
	double bloom_filter_theorical_fp_rate;
	double bloom_filter_fp_rate_with_filling_rate;

	


public:
	static BloomFilterStats* getInstance();
	void set_bloom_filter_sizeInBit(unsigned int bloom_filter_sizeInBit);
	void set_bloom_filter_hashFunctionsNumber(unsigned int bloom_filter_hashFunctionsNumber);
	void set_bloom_filter_hashFunctionName(string bloom_filter_hashFunctionName);

	void set_number_of_one_in_filter(unsigned int numberOfOnes);
	void increment_number_of_one_in_filter(unsigned int newInsertedOneNumber);

	void set_bloom_filter_fp_rates();
	
	void set_dataBase_size(unsigned int dataBase_size);
	string getStringOfAllStats();
	~BloomFilterStats();
	
};