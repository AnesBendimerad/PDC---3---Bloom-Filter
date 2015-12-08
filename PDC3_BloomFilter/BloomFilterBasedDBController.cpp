#include "stdafx.h"
#include "BloomFilterBasedDBController.h"
#include "DataBaseHandler.h"
#include "MurmurHasher.h"

BloomFilterBasedDBController::BloomFilterBasedDBController(DataBaseConfiguration dataBaseConfiguration, uint32_t bloomFilterSizeInBit, unsigned int bloomFilterHashFunctionsNumber, IHasher * bloomFilterHashFunction)
{
	this->dbHandler = new DataBaseHandler(dataBaseConfiguration);
	if (bloomFilterHashFunction == nullptr) bloomFilterHashFunction = new MurmurHasher();
	this->bloomFilter = new BloomFilter(bloomFilterSizeInBit, bloomFilterHashFunctionsNumber, bloomFilterHashFunction);
}

void BloomFilterBasedDBController::initBloomFilter()
{
	DocumentIterator* allDocumentIterator = this->dbHandler->getDocumentIterator();
	while (Document* d = allDocumentIterator->getNextDocument())
	{
		this->bloomFilter->addKey(d->documentNumber);
	}
}

bool BloomFilterBasedDBController::addDocument(Document * document)
{
	if (this->dbHandler->addDocument(document))
	{
		this->bloomFilter->addKey(document->documentNumber);
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
			return this->bloomFilter->readKey(documentNumber);
			break;
		case DB_VERIFICATION :
			return this->dbHandler->getDocumentByNumber(documentNumber)!= nullptr;
			break;
		default :
			if (!this->bloomFilter->readKey(documentNumber))
			{
				return false;
			}
			else
			{
				return this->dbHandler->getDocumentByNumber(documentNumber) != nullptr;
			}
			break;
	}	
}

Document * BloomFilterBasedDBController::getDocument(string documentNumber)
{
	if (!this->bloomFilter->readKey(documentNumber))
	{
		return false;
	}
	else
	{
		return this->dbHandler->getDocumentByNumber(documentNumber);
	}
}

BloomFilterBasedDBController::~BloomFilterBasedDBController()
{
	delete this->dbHandler;
	delete this->bloomFilter;
}
