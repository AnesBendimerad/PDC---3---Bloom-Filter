#pragma once
#include "IHasher.h"
#include <stdint.h>

class MurmurHasher : public IHasher
{
public :
	MurmurHasher();
	HashIterator* getHashIterator(string key);
	~MurmurHasher();

private :
	uint32_t murmur3_32(string key, uint32_t seed);

};