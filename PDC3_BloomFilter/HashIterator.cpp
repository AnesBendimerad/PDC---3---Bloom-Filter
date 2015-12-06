#include "stdafx.h"
#include "HashIterator.h"

HashIterator::HashIterator(unsigned int hashValue_1, unsigned int hashValue_2)
{
	HashIterator::hashValue_1 = hashValue_1;
	HashIterator::hashValue_2 = hashValue_2;
	HashIterator::i = 0;
}

unsigned int HashIterator::getNextHash()
{
	return hashValue_1 + (i++)*hashValue_2;
}
