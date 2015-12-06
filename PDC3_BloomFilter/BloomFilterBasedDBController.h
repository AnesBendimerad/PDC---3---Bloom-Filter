#pragma once
#include "DataBaseHandler.h"
#include "DataBaseConfiguration.h"
#include "BloomFilter.h"
#define BLOOM_AND_DB_VERIFICATION 0
#define BLOOM_VERIFICATION 1
#define DB_VERIFICATION 2

class BloomFilterBasedDBController {
private:
	DataBaseHandler* dbHandler;
	BloomFilter * bloomFilter;
public:
	BloomFilterBasedDBController(DataBaseConfiguration dataBaseConfiguration, uint32_t bloomFilterSizeInBit, unsigned int bloomFilterHashFunctionsNumber, IHasher * bloomFilterHashFunction=nullptr);
	bool addDocument(Document * document);
	bool doesDocumentNumberExist(string documentNumber, unsigned int verificationType = BLOOM_AND_DB_VERIFICATION);
	~BloomFilterBasedDBController();
};