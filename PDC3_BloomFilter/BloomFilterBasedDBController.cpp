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
string BloomFilterBasedDBController::processDocumentsTestFile(string filePath, unsigned int verificationType)
{
	ifstream inputStream(filePath, ios::in);

	unsigned int testFileSize = 0;
	unsigned int nonValidDocumentsCount = 0;
	unsigned int falsePositiveCount = 0;
	float falsePositiveRate = 0;

	string token;
	string annotation;
	bool queryResult;
	if (inputStream.fail()) {
		throw runtime_error("Failed when openning file");
	}
	
	while (inputStream >> token) {
		inputStream >> annotation;
		testFileSize++;
		if (annotation.compare("1") == 0) {
			nonValidDocumentsCount++;
		}
		queryResult = doesDocumentNumberExist(token, verificationType);
		if ((queryResult) && (annotation.compare("0")==0)) {
			falsePositiveCount++;
		}
	}
	falsePositiveRate = (1.* falsePositiveCount) / testFileSize;
	if (verificationType == BLOOM_VERIFICATION) {
		return "N:" + to_string(testFileSize) + " NV:" + to_string(nonValidDocumentsCount) + " FP:" + to_string(falsePositiveCount) + " FPR:" + to_string(falsePositiveRate);
	}
	else {
		return "N:" + to_string(testFileSize) + " NV:" + to_string(nonValidDocumentsCount);
	}
}