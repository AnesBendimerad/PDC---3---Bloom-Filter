#pragma once
#include <cassandra.h>
#include "DataBaseConfiguration.h"
#include "DocumentIterator.h"
class DataBaseHandler {
private:
	DataBaseConfiguration dataBaseConfiguration;
	CassSession* session;
	
public:
	DataBaseHandler(DataBaseConfiguration dataBaseConfiguration);
	Document * getDocumentByNumber(string documentNumber);
	bool addDocument(Document document);
	DocumentIterator * getDocumentIterator(string countryCode = "", string documentType = "");
	~DataBaseHandler();
};