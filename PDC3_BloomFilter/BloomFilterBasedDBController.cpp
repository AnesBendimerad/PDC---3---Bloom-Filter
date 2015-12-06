#include "stdafx.h"
#include "BloomFilterBasedDBController.h"
#include "DataBaseHandler.h"
#include "MurmurHasher.h"

BloomFilterBasedDBController::BloomFilterBasedDBController(DataBaseConfiguration dataBaseConfiguration, uint32_t bloomFilterSizeInBit, unsigned int bloomFilterHashFunctionsNumber, IHasher * bloomFilterHashFunction)
{
	BloomFilterBasedDBController::dbHandler = new DataBaseHandler(dataBaseConfiguration);
	if (bloomFilterHashFunction == nullptr) bloomFilterHashFunction = new MurmurHasher();
	BloomFilterBasedDBController::bloomFilter = new BloomFilter(bloomFilterSizeInBit, bloomFilterHashFunctionsNumber, bloomFilterHashFunction);
}

bool BloomFilterBasedDBController::addDocument(Document * document)
{
	if (dbHandler->addDocument(document))
	{
		bloomFilter->addKey(document->documentNumber);
		return true;
	}
	return false;
}

bool BloomFilterBasedDBController::doesDocumentNumberExist(string documentNumber, unsigned int verificationType)
{
	unsigned int i = 0;
	switch (verificationType)
	{
		case BLOOM_VERIFICATION :
			return bloomFilter->readKey(documentNumber);
			break;
		case DB_VERIFICATION :
			return dbHandler->getDocumentByNumber(documentNumber)!= nullptr;
			break;
		default :
			if (!bloomFilter->readKey(documentNumber))
			{
				return false;
			}
			else
			{
				return dbHandler->getDocumentByNumber(documentNumber) != nullptr;
			}
			break;
	}	
}

BloomFilterBasedDBController::~BloomFilterBasedDBController()
{
	delete BloomFilterBasedDBController::dbHandler;
	delete BloomFilterBasedDBController::bloomFilter;
}
