#pragma once
#include "stdafx.h"
#include "BloomFilterUtilities.h"
#include <math.h>

unsigned int getOptimalSizeForMaximalFPRate(double maximalFPRate, unsigned int databaseSize)
{
	if (maximalFPRate > 1 || maximalFPRate < 0) maximalFPRate = 1;
	return ceill(((databaseSize+0.5)*log(1/maximalFPRate)) / (log(2)*log(2)))+1;
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