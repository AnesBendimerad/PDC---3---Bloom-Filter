#include "stdafx.h"
#include "BitWiseArray.h"
#include <stdlib.h>
#include <stdio.h> 

using namespace std;

BitWiseArray::BitWiseArray(uint32_t sizeInBit)
{
	BitWiseArray::sizeInBit = sizeInBit;
	uint32_t sizeInWord = sizeInBit / (8*sizeof(uint32_t));
	if (sizeInBit % (8 * sizeof(uint32_t))) 
	{
		sizeInWord++;
	}
	BitWiseArray::bitArray = (uint32_t*)calloc(1,sizeInWord*sizeof(uint32_t));
}

uint32_t BitWiseArray::getSize()
{
	return sizeInBit;
}

bool BitWiseArray::get(uint32_t i)
{
	uint32_t mod = i%sizeInBit;
	uint32_t indexInBitArray = mod / ((8 * sizeof(uint32_t)));
	uint32_t mask = 1 << (mod % ((8 * sizeof(uint32_t))));
	uint32_t result = BitWiseArray::bitArray[indexInBitArray] & mask;
	return result > 0;
}

void BitWiseArray::set(uint32_t i)
{
	uint32_t mod = i%sizeInBit;
	uint32_t indexInBitArray = mod / ((8 * sizeof(uint32_t)));
	uint32_t mask = 1 << (mod % ((8 * sizeof(uint32_t))));
	BitWiseArray::bitArray[indexInBitArray] |= mask;
}

void BitWiseArray::unset(uint32_t i)
{
	uint32_t mod = i%sizeInBit;
	uint32_t indexInBitArray = mod / ((8 * sizeof(uint32_t)));
	uint32_t mask = (1 << (mod % ((8 * sizeof(uint32_t)))))^(UINT32_MAX);
	BitWiseArray::bitArray[indexInBitArray] &= mask;
}

BitWiseArray::~BitWiseArray()
{
	free(BitWiseArray::bitArray);
}
