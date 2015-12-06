#include "stdafx.h"
#include "BloomFilterBasedDBController.h"

bool BloomFilterBasedDBController::addDocument(Document * document)
{
	if (dbHandler->addDocument(document))
	{
		bloomFilter->addKey(document->documentNumber);
	}
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
}
