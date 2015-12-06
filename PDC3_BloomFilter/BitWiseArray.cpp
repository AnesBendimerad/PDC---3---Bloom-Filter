#include "stdafx.h"
#include "BitWiseArray.h"
#include <stdlib.h>
#include <stdio.h> 
#include <stdexcept>

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

bool BitWiseArray::get(uint32_t i)
{
	if (i >= BitWiseArray::sizeInBit)
	{
		throw out_of_range("Index out of bound");
	}
	else
	{
		uint32_t indexInBitArray = i / ((8 * sizeof(uint32_t)));
		uint32_t mask = 1 << (i % ((8 * sizeof(uint32_t))));
		uint32_t result = BitWiseArray::bitArray[indexInBitArray] & mask;
		return result > 0;
	}
}

void BitWiseArray::set(uint32_t i)
{
	if (i >= BitWiseArray::sizeInBit)
	{
		throw out_of_range("Index out of bound");
	}
	uint32_t indexInBitArray = i / ((8 * sizeof(uint32_t)));
	uint32_t mask = 1 << (i % ((8 * sizeof(uint32_t))));
	BitWiseArray::bitArray[indexInBitArray] |= mask;
}

void BitWiseArray::unset(uint32_t i)
{
	if (i >= BitWiseArray::sizeInBit)
	{
		throw out_of_range("Index out of bound");
	}
	uint32_t indexInBitArray = i / ((8 * sizeof(uint32_t)));
	uint32_t mask = (1 << (i % ((8 * sizeof(uint32_t)))))^(UINT32_MAX);
	BitWiseArray::bitArray[indexInBitArray] &= mask;
}
