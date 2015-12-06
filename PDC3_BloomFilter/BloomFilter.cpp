#include "stdafx.h"
#include "BloomFilter.h"

BloomFilter::BloomFilter(uint32_t sizeInBit, unsigned int hashFunctionsNumber, IHasher * hashFunction)
{
	BloomFilter::bitWiseArray = new BitWiseArray(sizeInBit);
	BloomFilter::hashFunctionsNumber = hashFunctionsNumber;
	BloomFilter::hashFunction = hashFunction;
}

void BloomFilter::addKey(string key)
{
	HashIterator* hashIterator = BloomFilter::hashFunction->getHashIterator(key);
	for (unsigned int k = 0;k < hashFunctionsNumber;k++)
	{
		uint32_t index = hashIterator->getNextHash();
		BloomFilter::bitWiseArray->set(index);
	}
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
}
