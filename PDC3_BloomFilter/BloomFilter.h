#pragma once
#include "IHasher.h"
class BloomFilter {
private:
	unsigned long long inMemorySize;
	unsigned int hashFunctionsNumber;
	IHasher * hashFunction;
public:
	BloomFilter(unsigned long long inMemorySize, unsigned int hashFunctionsNumber, IHasher * hashFunction);
	void addKey(string key);
	bool readKey(string key);	// false --> key doesn't exists in the set (certainly)
								// true  --> key exists in the set (normally), with a risk of error 
	~BloomFilter();
};