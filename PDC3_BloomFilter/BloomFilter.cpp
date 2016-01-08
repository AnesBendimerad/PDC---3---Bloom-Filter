#include "stdafx.h"
#include "BloomFilter.h"
#include "BloomFilterStats.h"

//#include "prime.h"
BloomFilter::BloomFilter(uint32_t sizeInBit, unsigned int hashFunctionsNumber, IHasher * hashFunction)
{
	//sizeInBit = getUpperPrimeNumber(sizeInBit);
	if (sizeInBit == 0) sizeInBit = 1;
	if (hashFunctionsNumber == 0) hashFunctionsNumber = 1;

	BloomFilter::bitWiseArray = new BitWiseArray(sizeInBit);
	BloomFilter::hashFunctionsNumber = hashFunctionsNumber;
	BloomFilter::hashFunction = hashFunction;

	BloomFilterStats* bloomFilterStats = BloomFilterStats::getInstance();
	
	bloomFilterStats->set_bloom_filter_sizeInBit(sizeInBit);
	bloomFilterStats->set_bloom_filter_hashFunctionsNumber(hashFunctionsNumber);
	bloomFilterStats->set_bloom_filter_hashFunctionName(hashFunction->getName());
	bloomFilterStats->set_number_of_one_in_filter(0);
}

void BloomFilter::addKey(string key)
{
	unsigned int newInsertedOneNumber = 0;
	HashIterator* hashIterator = BloomFilter::hashFunction->getHashIterator(key);
	for (unsigned int k = 0;k < hashFunctionsNumber;k++)
	{
		uint32_t index = hashIterator->getNextHash();
		if (!BloomFilter::bitWiseArray->get(index)) {
			BloomFilter::bitWiseArray->set(index);
			newInsertedOneNumber += 1;
		}
	}
	BloomFilterStats* bloomFilterStats = BloomFilterStats::getInstance();
	bloomFilterStats->increment_number_of_one_in_filter(newInsertedOneNumber);
	delete hashIterator;
}

bool BloomFilter::readKey(string key)
{
	HashIterator* hashIterator = BloomFilter::hashFunction->getHashIterator(key);
	bool returnValue = true;
	for (unsigned int k = 0;k < hashFunctionsNumber;k++)
	{
		uint32_t index = hashIterator->getNextHash();
		if (!BloomFilter::bitWiseArray->get(index))
		{
			returnValue = false;
			break;
		}
	}
	delete hashIterator;
	return returnValue;
}

BloomFilter::~BloomFilter()
{
	delete BloomFilter::bitWiseArray;
	delete BloomFilter::hashFunction;
}
