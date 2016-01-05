#include "stdafx.h"
#include "MurmurHasher.h"
#include "HashIterator.h"

#define ROT32(x, y) ((x << y) | (x >> (32 - y)))

MurmurHasher::MurmurHasher()
{
}

HashIterator* MurmurHasher::getHashIterator(string key)
{
	uint32_t hashValue_1 = murmur3_32(key, 0);
	uint32_t hashValue_2 = murmur3_32(key, hashValue_1);
	return new HashIterator(hashValue_1, hashValue_2);
}

int MurmurHasher::getId()
{
	return MURMUR_HASHER;
}

string MurmurHasher::getName()
{
	return VALUE_MURMUR_HASH;
}

MurmurHasher::~MurmurHasher()
{
}

uint32_t MurmurHasher::murmur3_32(string key, uint32_t seed)
{
	const char* keyAsChars= key.c_str();
	uint32_t len = key.length();

	static const uint32_t c1 = 0xcc9e2d51;
	static const uint32_t c2 = 0x1b873593;
	static const uint32_t r1 = 15;
	static const uint32_t r2 = 13;
	static const uint32_t m = 5;
	static const uint32_t n = 0xe6546b64;

	uint32_t hash = seed;

	const int nblocks = len / 4;
	const uint32_t *blocks = (const uint32_t *)keyAsChars;
	int i;
	uint32_t k;
	for (i = 0; i < nblocks; i++) {
		k = blocks[i];
		k *= c1;
		k = ROT32(k, r1);
		k *= c2;

		hash ^= k;
		hash = ROT32(hash, r2) * m + n;
	}

	const uint8_t *tail = (const uint8_t *)(keyAsChars + nblocks * 4);
	uint32_t k1 = 0;

	switch (len & 3) {
	case 3:
		k1 ^= tail[2] << 16;
	case 2:
		k1 ^= tail[1] << 8;
	case 1:
		k1 ^= tail[0];

		k1 *= c1;
		k1 = ROT32(k1, r1);
		k1 *= c2;
		hash ^= k1;
	}

	hash ^= len;
	hash ^= (hash >> 16);
	hash *= 0x85ebca6b;
	hash ^= (hash >> 13);
	hash *= 0xc2b2ae35;
	hash ^= (hash >> 16);

	return hash;
}