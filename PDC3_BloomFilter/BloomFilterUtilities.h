#pragma once

long double getMinimalBitPerItem(double maximalFPRate, unsigned int hashFunctionNumber);
unsigned int getOptimalHashFunctionNumber(double maximalFPRate);
unsigned int getOptimalFilterSize(double maximalFPRate, unsigned int databaseSize, unsigned int HashFunctionNumber);
double estimateTheoricalFPRate(unsigned int databaseSize, unsigned int bloomFilterSize, unsigned int hashFunctionNumber);
double estimateFPRateWithFillingRate(double fillingRate, unsigned int hashFunctionNumber);