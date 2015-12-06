#include "stdafx.h"
#include "HashIterator.h"

HashIterator::HashIterator(uint32_t hashValue_1, uint32_t hashValue_2)
{
	HashIterator::hashValue_1 = hashValue_1;
	HashIterator::hashValue_2 = hashValue_2;
	HashIterator::i = 0;
}

uint32_t HashIterator::getNextHash()
{
	return hashValue_1 + (i++)*hashValue_2;
}
