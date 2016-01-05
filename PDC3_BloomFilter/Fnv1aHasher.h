#pragma once
#include "IHasher.h"
#include <stdint.h>

const uint32_t Prime = 0x01000193; //   16777619
const uint32_t Seed = 0x811C9DC5; // 2166136261

class Fnv1aHasher : public IHasher {
private :
	uint32_t fnv1aString(const std::string text, uint32_t hash = Seed);
	int getId();
public :
	Fnv1aHasher();
	HashIterator* getHashIterator(string key);
	~Fnv1aHasher();
};