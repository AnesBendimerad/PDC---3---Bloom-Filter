#pragma once
#include "IHasher.h"
#include "BitWiseArray.h"
#include <stdint.h>

class BloomFilter {
private:
	BitWiseArray* bitWiseArray;
	unsigned int hashFunctionsNumber;
	IHasher * hashFunction;
public:
	// if sizeInBit is not prime, the colsest lesser prime number is used
	BloomFilter(uint32_t sizeInBit, unsigned int hashFunctionsNumber, IHasher * hashFunction);
	void addKey(string key);
	bool readKey(string key);	// false --> key doesn't exists in the set (certainly)
								// true  --> key exists in the set (normally), with a risk of error 
	~BloomFilter();
};