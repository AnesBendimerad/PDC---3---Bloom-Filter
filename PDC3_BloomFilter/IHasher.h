#pragma once
#include "HashIterator.h"
#include <string>
#define MURMUR_HASHER 0
#define FNV1A_HASHER 1
using namespace std;

class IHasher {
public:
	virtual HashIterator* getHashIterator(string key) = 0;
	virtual int getId()=0;
};