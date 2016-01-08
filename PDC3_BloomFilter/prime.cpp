#pragma once
#include "stdafx.h"
#include "prime.h"
#include <math.h>

bool isPrime(uint32_t number)
{
	double root = sqrt(number);
	for (unsigned int i = 2;i <= root;i++)
	{
		if (number%i == 0)
		{
			return false;
		}
	}
	return true;
}

uint32_t getLesserPrimeNumber(uint32_t number)
{
	uint32_t primeNumber=number+1;
	if (primeNumber <= 2) 
	{
		return 2;
	}
	if (primeNumber >= LARGEST_PRIME_NUMBER)
	{
		return LARGEST_PRIME_NUMBER;
	}
	while (!isPrime(--primeNumber));
	return primeNumber;
}

uint32_t getUpperPrimeNumber(uint32_t number)
{
	uint32_t primeNumber = number;
	if (primeNumber <= 2)
	{
		return 2;
	}
	if (primeNumber >= LARGEST_PRIME_NUMBER)
	{
		return LARGEST_PRIME_NUMBER;
	}
	while (primeNumber < LARGEST_PRIME_NUMBER && !isPrime(primeNumber))
	{
		primeNumber++;
	}
	return primeNumber;
}
