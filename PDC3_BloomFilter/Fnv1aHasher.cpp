#include "stdafx.h"
#include "Fnv1aHasher.h"
#include "HashIterator.h"

uint32_t Fnv1aHasher::fnv1aString(const std::string text, uint32_t hash)
{
	size_t numBytes = text.length();
	const char *textAsChars = text.c_str();
	while (numBytes--)
	{
		hash = (((unsigned char)*textAsChars++) ^ hash) * Prime;
	}
	return hash;
}

int Fnv1aHasher::getId()
{
	return FNV1A_HASHER;
}

Fnv1aHasher::Fnv1aHasher()
{
}

HashIterator * Fnv1aHasher::getHashIterator(string key)
{
	uint32_t hashValue_1 = fnv1aString(key);
	uint32_t hashValue_2 = fnv1aString(key, hashValue_1);
	return new HashIterator(hashValue_1, hashValue_2);
}

Fnv1aHasher::~Fnv1aHasher()
{
}
