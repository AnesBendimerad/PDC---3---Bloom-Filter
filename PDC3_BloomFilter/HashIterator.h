#pragma once
#include <stdint.h>

class HashIterator {
public:
	HashIterator(uint32_t hashValue_1, uint32_t hashValue_2);
	uint32_t getNextHash();
private:
	uint32_t hashValue_1;
	uint32_t hashValue_2;
	uint32_t i = 0;

};