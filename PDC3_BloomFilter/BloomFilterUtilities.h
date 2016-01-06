#pragma once

unsigned int getOptimalSizeForMaximalFPRate(double maximalFPRate, unsigned int databaseSize);
unsigned int getOptimalHashFunctionNumberForMaximalFPRateAndSize(double maximalFPRate, unsigned int databaseSize, unsigned int bloomFilterSize);
double estimateTheoricalFPRate(unsigned int databaseSize, unsigned int bloomFilterSize, unsigned int hashFunctionNumber);
double estimateFPRateWithFillingRate(double fillingRate, unsigned int hashFunctionNumber);