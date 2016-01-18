#pragma once
#include "stdafx.h"
#include "BloomFilterUtilities.h"
#include <math.h>
#define UINT32_MAX  (0xffffffff)

long double getMinimalBitPerItem(double maximalFPRate, unsigned int hashFunctionNumber)
{
	return float(hashFunctionNumber) / (log(1 / (1 - pow(maximalFPRate, 1. / hashFunctionNumber))));
}

unsigned int getOptimalHashFunctionNumber(double maximalFPRate)
{
	unsigned int k = 1;
	if (maximalFPRate >= 1 || maximalFPRate <= 0) maximalFPRate = 0.5;
	long double x_min = log(1 / maximalFPRate) / log(2);
	if (x_min > 1) 
	{
		unsigned int k1= (unsigned int) floor(x_min);
		unsigned int k2 = (unsigned int) ceil(x_min);
		long double v1 = getMinimalBitPerItem(maximalFPRate, k1);
		long double v2 = getMinimalBitPerItem(maximalFPRate, k2);
		if (v1 < v2) k = k1;
		else k = k2;
	}
	return k;
}

unsigned int getOptimalFilterSize(double maximalFPRate, unsigned int databaseSize, unsigned int HashFunctionNumber)
{
	double long value = ceil((databaseSize + 0.5)*getMinimalBitPerItem(maximalFPRate, HashFunctionNumber)) + 1;
	unsigned int maximalSize = UINT32_MAX;
	if (value > maximalSize) value = maximalSize;
	return (unsigned int) value;
}

double estimateTheoricalFPRate(unsigned int databaseSize, unsigned int bloomFilterSize, unsigned int hashFunctionNumber)
{
	return pow(1 - pow(1 - 1.0 / bloomFilterSize, hashFunctionNumber*databaseSize), hashFunctionNumber);
}

double estimateFPRateWithFillingRate(double fillingRate, unsigned int hashFunctionNumber)
{
	return pow(fillingRate, hashFunctionNumber);
}