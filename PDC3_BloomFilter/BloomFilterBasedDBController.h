#pragma once
#include "DataBaseHandler.h"
#include "BloomFilter.h"
#define BLOOM_AND_DB_VERIFICATION 0
#define BLOOM_VERIFICATION 1
#define DB_VERIFICATION 2

class BloomFilterBasedDBController {
private:
	DataBaseHandler* dbHandler;
	BloomFilter * bloomFilter;
public:
	
	bool addDocument(Document * document);
	bool doesDocumentNumberExist(string documentNumber, unsigned int verificationType = BLOOM_AND_DB_VERIFICATION);
	~BloomFilterBasedDBController();
};