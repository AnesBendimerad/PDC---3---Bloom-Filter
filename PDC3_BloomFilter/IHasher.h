#pragma once
#include "HashIterator.h"
#include <string>

#define MURMUR_HASHER				0
#define VALUE_MURMUR_HASH			"murmur"

#define FNV1A_HASHER				1
#define VALUE_FNV1A_HASH			"fnv1a"

using namespace std;

class IHasher {
public:
	virtual HashIterator* getHashIterator(string key) = 0;
	virtual int getId()=0;
	virtual string getName() = 0;
};