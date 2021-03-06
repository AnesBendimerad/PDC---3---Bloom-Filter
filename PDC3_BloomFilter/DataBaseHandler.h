#pragma once
#include <cassandra.h>
#include "CassandraAdditionalFunctions.h"
#include "DataBaseConfiguration.h"
#include "DocumentIterator.h"
class DataBaseHandler {
private:
	/// nota : verify if cass_statement_free is in its place
	DataBaseConfiguration dataBaseConfiguration;
	CassSession* session;
	CassCluster* cluster;
	CassFuture* connect_future;
	unsigned int dbSize;
	
	const CassResult* getResultOfQuery(string query);
public:
	DataBaseHandler(DataBaseConfiguration dataBaseConfiguration);
	Document * getDocumentByNumber(string documentNumber);
	bool addDocument(Document * document);
	DocumentIterator * getDocumentIterator(string countryCode = "");
	unsigned int getDataBaseSize();
	~DataBaseHandler();
};