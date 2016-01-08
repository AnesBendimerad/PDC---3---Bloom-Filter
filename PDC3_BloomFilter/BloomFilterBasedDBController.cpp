#include "stdafx.h"
#include "BloomFilterBasedDBController.h"
#include "DataBaseHandler.h"
#include "MurmurHasher.h"
#include "BloomFilterStats.h"
#include "BloomFilterUtilities.h"

BloomFilterBasedDBController::BloomFilterBasedDBController(DataBaseConfiguration dataBaseConfiguration, uint32_t bloomFilterSizeInBit, unsigned int bloomFilterHashFunctionsNumber, IHasher * bloomFilterHashFunction)
{
	this->dbHandler = new DataBaseHandler(dataBaseConfiguration);
	if (bloomFilterHashFunction == nullptr) bloomFilterHashFunction = new MurmurHasher();
	this->bloomFilter = new BloomFilter(bloomFilterSizeInBit, bloomFilterHashFunctionsNumber, bloomFilterHashFunction);
}

BloomFilterBasedDBController::BloomFilterBasedDBController(DataBaseConfiguration dataBaseConfiguration, double bloomFilterMaximalFPRate, IHasher * bloomFilterHashFunction)
{
	this->dbHandler = new DataBaseHandler(dataBaseConfiguration);
	if (bloomFilterHashFunction == nullptr) bloomFilterHashFunction = new MurmurHasher();
	unsigned int dataBaseSize = this->dbHandler->getDataBaseSize();
	unsigned int bloomFilterSizeInBit = getOptimalSizeForMaximalFPRate(bloomFilterMaximalFPRate,dataBaseSize);
	unsigned int bloomFilterHashFunctionsNumber = getOptimalHashFunctionNumberForMaximalFPRateAndSize(bloomFilterMaximalFPRate, dataBaseSize, bloomFilterSizeInBit);
	this->bloomFilter = new BloomFilter(bloomFilterSizeInBit, bloomFilterHashFunctionsNumber, bloomFilterHashFunction);
}

void BloomFilterBasedDBController::initBloomFilter()
{
	DocumentIterator* allDocumentIterator = this->dbHandler->getDocumentIterator();
	while (Document* d = allDocumentIterator->getNextDocument())
	{
		this->bloomFilter->addKey(d->documentNumber);
	}

	BloomFilterStats* bloomFilterStats = BloomFilterStats::getInstance();
	bloomFilterStats->set_dataBase_size(allDocumentIterator->getSize());
	bloomFilterStats->set_bloom_filter_fp_rates();
	delete allDocumentIterator;
}

void BloomFilterBasedDBController::reinitBloomFilter(uint32_t bloomFilterSizeInBit, unsigned int bloomFilterHashFunctionsNumber, IHasher * bloomFilterHashFunction)
{
	delete this->bloomFilter;
	if (bloomFilterHashFunction == nullptr) bloomFilterHashFunction = new MurmurHasher();
	this->bloomFilter = new BloomFilter(bloomFilterSizeInBit, bloomFilterHashFunctionsNumber, bloomFilterHashFunction);
	this->initBloomFilter();
}

void BloomFilterBasedDBController::reinitBloomFilter(double bloomFilterMaximalFPRate, IHasher * bloomFilterHashFunction)
{
	delete this->bloomFilter;
	if (bloomFilterHashFunction == nullptr) bloomFilterHashFunction = new MurmurHasher();
	unsigned int dataBaseSize = this->dbHandler->getDataBaseSize();
	unsigned int bloomFilterSizeInBit = getOptimalSizeForMaximalFPRate(bloomFilterMaximalFPRate, dataBaseSize);
	unsigned int bloomFilterHashFunctionsNumber = getOptimalHashFunctionNumberForMaximalFPRateAndSize(bloomFilterMaximalFPRate, dataBaseSize, bloomFilterSizeInBit);
	this->bloomFilter = new BloomFilter(bloomFilterSizeInBit, bloomFilterHashFunctionsNumber, bloomFilterHashFunction);
	this->initBloomFilter();
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

DataBaseHandler * BloomFilterBasedDBController::getDataBaseHandler()
{
	return dbHandler;
}

BloomFilterBasedDBController::~BloomFilterBasedDBController()
{
	delete this->dbHandler;
	delete this->bloomFilter;
}

/*
	Result format :
	if (verificationType==BLOOM_VERIFICATION)
		"N:1000 NV:10 FP:7 FPR:0.01"
	else
		"N:1000 NV:10"
*/
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
	unsigned int quotient = testFileSize - nonValidDocumentsCount;
	if (quotient == 0) falsePositiveRate = 0;
	else falsePositiveRate = (float) ((1.* falsePositiveCount) / quotient);
	if (verificationType == BLOOM_VERIFICATION) {
		return "Number of documents : " + to_string(testFileSize) + ", Number of non valid documents : " + to_string(nonValidDocumentsCount) + ", Number of bloom filter errors - False Positive - : " + to_string(falsePositiveCount) + ", Error rate : " + to_string(falsePositiveRate);
	}
	else {
		return "Number of documents : " + to_string(testFileSize) + ", Number of non valid documents : " + to_string(nonValidDocumentsCount);
	}
}