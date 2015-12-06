#include "stdafx.h"
#include "DataBaseHandler.h"



const CassResult * DataBaseHandler::getResultOfQuery(string query)
{
	CassStatement* statement = cass_statement_new(query.c_str(), 0);
	CassFuture* result_future = cass_session_execute(session, statement);
	if (cass_future_error_code(result_future) == CASS_OK) {
		const CassResult* result = cass_future_get_result(result_future);
		cass_statement_free(statement);
		return result;
	}
	else {
		/* Handle error */
		const char* message;
		size_t message_length;
		cass_future_error_message(result_future, &message, &message_length);
		fprintf(stderr, "Unable to run query: '%.*s'\n",
			(int)message_length, message);
		cass_statement_free(statement);
		return nullptr;
	}
}

DataBaseHandler::DataBaseHandler(DataBaseConfiguration dataBaseConfiguration)
{
	DataBaseHandler::dataBaseConfiguration = dataBaseConfiguration;
	/* Setup and connect to cluster */
	cluster = cass_cluster_new();
	session = cass_session_new();
	/* Add contact points */
	cass_cluster_set_contact_points(cluster, dataBaseConfiguration.contactPoints.c_str());
	/* Provide the cluster object as configuration to connect the session */
	connect_future = cass_session_connect(session, cluster);
	/* This operation will block until the result is ready */
	CassError rc = cass_future_error_code(connect_future);
	printf("Connect result: %s\n", cass_error_desc(rc));
}

Document * DataBaseHandler::getDocumentByNumber(string documentNumber)
{
	string query = "SELECT * FROM " + dataBaseConfiguration.keySpace
		+ "." + dataBaseConfiguration.table + " WHERE "
		+ DOCUMENT_NUMBER + " = '" + documentNumber + "'";
	const CassResult* result = getResultOfQuery(query);
	if (result!=nullptr){
		DocumentIterator * documentIterator=new DocumentIterator(result);
		return documentIterator->getNextDocument();
	}
	else {
		return nullptr;
	}
}

bool DataBaseHandler::addDocument(Document * document)
{
	CassError rc = CASS_OK;
	CassStatement* statement = NULL;
	CassFuture* future = NULL;
	bool returnedValue = true;
	string query = "INSERT INTO " + dataBaseConfiguration.keySpace
		+ "." + dataBaseConfiguration.table+ "("+DOCUMENT_NUMBER+", "
		+DOCUMENT_TYPE+", "+COUNTRY_CODE+") VALUES (?, ?, ?);";
	statement = cass_statement_new(query.c_str(), 3);
	cass_statement_bind_string(statement, 0, document->documentNumber.c_str());
	cass_statement_bind_string(statement, 1, document->documentType.c_str());
	cass_statement_bind_string(statement, 2, document->countryCode.c_str());
	future = cass_session_execute(session, statement);
	cass_future_wait(future);
	rc = cass_future_error_code(future);
	if (rc != CASS_OK) {
		const char* message;
		size_t message_length;
		cass_future_error_message(future, &message, &message_length);
		fprintf(stderr, "Error: %.*s\n", (int)message_length, message);
		returnedValue=false;
	}
	cass_future_free(future);
	cass_statement_free(statement);
	return returnedValue;
}

DocumentIterator * DataBaseHandler::getDocumentIterator(string countryCode, string documentType)
{
	string query = "SELECT * FROM " + dataBaseConfiguration.keySpace
		+ "." + dataBaseConfiguration.table;
	string word = " WHERE ";
	if (countryCode.compare("") != 0) {
		query = query + word + COUNTRY_CODE + " = '" + countryCode + "'";
		word = " AND ";
	}
	if (documentType.compare("") != 0) {
		query = query + word + DOCUMENT_TYPE + " = '" + documentType + "'";
	}
	const CassResult* result = getResultOfQuery(query);
	if (result != nullptr) {
		return new DocumentIterator(result);
	}
	else {
		return nullptr;
	}
}

DataBaseHandler::~DataBaseHandler()
{
	cass_future_free(connect_future);
	cass_session_free(session);
	cass_cluster_free(cluster);
	delete session;
	delete connect_future;
	delete cluster;
}