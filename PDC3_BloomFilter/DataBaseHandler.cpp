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
		throw new exception(message);
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
	//printf("Database connection result: %s\n", cass_error_desc(rc));
	dbSize = -1;
}

Document * DataBaseHandler::getDocumentByNumber(string documentNumber)
{
	string query = "SELECT * FROM " + dataBaseConfiguration.keySpace
		+ "." + dataBaseConfiguration.table + " WHERE "
		+ DOCUMENT_NUMBER + " = '" + documentNumber + "'";
	const CassResult* result = getResultOfQuery(query);
	if (result!=nullptr){
		DocumentIterator * documentIterator=new DocumentIterator(nullptr, nullptr,result);
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
		throw new exception(message);
		returnedValue=false;
	}
	cass_future_free(future);
	cass_statement_free(statement);
	return returnedValue;
}

DocumentIterator * DataBaseHandler::getDocumentIterator(string countryCode)
{
	string query = "SELECT * FROM " + dataBaseConfiguration.keySpace
		+ "." + dataBaseConfiguration.table;
	if (countryCode.compare("") != 0) {
		query = query + " WHERE " + COUNTRY_CODE + " = '" + countryCode + "'";
	}
	const CassResult* result= nullptr;
	CassStatement* statement = cass_statement_new(query.c_str(), 0);
	cass_statement_set_paging_size(statement, 200000);
	CassFuture* result_future = cass_session_execute(session, statement);
	if (cass_future_error_code(result_future) == CASS_OK) {
		result = cass_future_get_result(result_future);
	}
	else {
		/* Handle error */
		const char* message;
		size_t message_length;
		cass_future_error_message(result_future, &message, &message_length);
		throw new exception(message);
		cass_statement_free(statement);
		return nullptr;
	}

	if (result != nullptr) {
		return new DocumentIterator(session, statement,result);
	}
	else {
		return nullptr;
	}
}

unsigned int DataBaseHandler::getDataBaseSize()
{
	if (dbSize != -1) {
		return dbSize;
	}
	string query = "SELECT * FROM " + dataBaseConfiguration.keySpace
		+ "." + dataBaseConfiguration.table;
	
	const CassResult* result = nullptr;
	CassStatement* statement = cass_statement_new(query.c_str(), 0);
	cass_statement_set_paging_size(statement, 200000);
	CassFuture* result_future = cass_session_execute(session, statement);
	if (cass_future_error_code(result_future) == CASS_OK) {
		result = cass_future_get_result(result_future);
		dbSize = cass_result_row_count(result);
		while (cass_result_has_more_pages(result)) {
			cass_statement_set_paging_state(statement, result);
			cass_result_free(result);
			result_future = cass_session_execute(session, statement);
			result = cass_future_get_result(result_future);
			dbSize+= cass_result_row_count(result);
		}
		cass_result_free(result);
		return dbSize;
	}
	else {
		/* Handle error */
		const char* message;
		size_t message_length;
		cass_future_error_message(result_future, &message, &message_length);
		throw new exception(message);
		cass_statement_free(statement);
		return 0;
	}
}

DataBaseHandler::~DataBaseHandler()
{
	cass_future_free(connect_future);
	cass_session_free(session);
	cass_cluster_free(cluster);
}