#pragma once
#include "HashIterator.h"
#include <string>
using namespace std;

class IHasher {
public:
	virtual HashIterator* getHashIterator(string key) = 0;

};