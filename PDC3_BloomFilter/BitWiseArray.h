#pragma once
#include <stdint.h>

class BitWiseArray
{
public:
	BitWiseArray(uint32_t sizeInBit);
	bool get(uint32_t i);
	void set(uint32_t i);
	void unset(uint32_t i);
private:
	uint32_t sizeInBit;
	uint32_t* bitArray;
};