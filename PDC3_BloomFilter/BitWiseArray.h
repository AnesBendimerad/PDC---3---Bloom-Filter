#pragma once
#include <stdint.h>

class BitWiseArray
{
// this class is a circular bit wise array 
public:
	BitWiseArray(uint32_t sizeInBit);
	uint32_t getSize();
	bool get(uint32_t i);
	void set(uint32_t i);
	void unset(uint32_t i);
	~BitWiseArray();
private:
	uint32_t sizeInBit;
	uint32_t* bitArray;
};