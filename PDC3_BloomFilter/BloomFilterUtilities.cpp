#pragma once
#include "stdafx.h"
#include "BloomFilterUtilities.h"
#include "prime.h"
#include <math.h>

unsigned int getPrimalOptimalSizeForMaximalFPRate(double maximalFPRate, unsigned int databaseSize)
{
	if (maximalFPRate > 1 || maximalFPRate < 0) maximalFPRate = 1;
	return getUpperPrimeNumber(ceill((databaseSize*log(1/maximalFPRate)) / (log(maximalFPRate)*log(maximalFPRate))));
}

unsigned int getOptimalHashFunctionNumberForMaximalFPRateAndSize(double maximalFPRate, unsigned int databaseSize, unsigned int bloomFilterSize)
{
	if (maximalFPRate > 1 || maximalFPRate < 0) maximalFPRate = 1;
	return ceill((log(2)*bloomFilterSize)/ databaseSize);
}

double estimateTheoricalFPRate(unsigned int databaseSize, unsigned int bloomFilterSize, unsigned int hashFunctionNumber)
{
	return pow(1 - pow(1 - 1.0 / bloomFilterSize, hashFunctionNumber*databaseSize), hashFunctionNumber);
}

double estimateFPRateWithFillingRate(double fillingRate, unsigned int hashFunctionNumber)
{
	return pow(fillingRate, hashFunctionNumber);
}