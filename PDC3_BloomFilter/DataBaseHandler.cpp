#include "DataBaseHandler.h"

DataBaseHandler::DataBaseHandler(DataBaseConfiguration dataBaseConfiguration)
{
}

Document * DataBaseHandler::getDocumentByNumber(string documentNumber)
{
	return nullptr;
}

bool DataBaseHandler::addDocument(Document document)
{
	return false;
}

DocumentIterator * DataBaseHandler::getDocumentIterator(string countryCode, string documentType)
{
	return nullptr;
}

DataBaseHandler::~DataBaseHandler()
{
}
