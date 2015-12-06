#pragma once
#include <cassandra.h>
#include "DataBaseConfiguration.h"
#include "DocumentIterator.h"
#define DOCUMENT_NUMBER "documentNumber"
#define DOCUMENT_TYPE "documentType"
#define COUNTRY_CODE "countryCode"
class DataBaseHandler {
private:
	/// nota : verify if cass_statement_free is in its place
	DataBaseConfiguration dataBaseConfiguration;
	CassSession* session;
	CassCluster* cluster;
	CassFuture* connect_future;
	string getColumnValue(const CassRow* row,string columnName);
	const CassResult* getResultOfQuery(string query);
public:
	DataBaseHandler(DataBaseConfiguration dataBaseConfiguration);
	Document * getDocumentByNumber(string documentNumber);
	bool addDocument(Document * document);
	DocumentIterator * getDocumentIterator(string countryCode = "", string documentType = "");
	~DataBaseHandler();
};