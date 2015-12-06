#include "stdafx.h"
#include "DataBaseGenerator.h"
#include "Document.h"
#include <time.h>
#include "DataBaseHandler.h"

using namespace std;

DataBaseGenerator::DataBaseGenerator(DataBaseConfiguration dataBaseConfiguration, unsigned int dataBaseSize)
{
	DataBaseGenerator::dataBaseConfiguration = dataBaseConfiguration;
	DataBaseGenerator::dataBaseSize = dataBaseSize;
}

bool DataBaseGenerator::generate()
{
	string keyspace = "create keyspace " + DataBaseGenerator::dataBaseConfiguration.keySpace + " with replication={'class':'SimpleStrategy', 'replication_factor':1};";
	string index = " CREATE INDEX countryCode_index ON " + DataBaseGenerator::dataBaseConfiguration.keySpace + "." + DataBaseGenerator::dataBaseConfiguration.table + "(" + string(COUNTRY_CODE) + "); ";
	string table = "create table " + DataBaseGenerator::dataBaseConfiguration.keySpace + "." + DataBaseGenerator::dataBaseConfiguration.table + " ( " + string(DOCUMENT_NUMBER) + " varchar primary key, " + string(DOCUMENT_TYPE) + " varchar, " + string(COUNTRY_CODE) + " varchar); ";

	executeQuery(keyspace);
	executeQuery(table);
	executeQuery(index);

	DataBaseHandler * dbh = new DataBaseHandler(DataBaseGenerator::dataBaseConfiguration);
	Document doc;
	unsigned int i = 0;
	while (i < dataBaseSize){
		 
		doc.documentNumber = std::to_string(i);
		doc.countryCode = RandomString(countryCodeSize);
		doc.documentType = RandomString(documentTypeSize);

		dbh->addDocument(&doc);
		i++;
	}

	delete dbh;
	return true;
}


string DataBaseGenerator::RandomString(unsigned int len)
{
	srand(time(0));
	string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	unsigned int pos;
	while (str.size() != len) {
		pos = ((rand() % (str.size() - 1)));
		str.erase(pos, 1);
	}
	return str;
}

bool DataBaseGenerator::executeQuery(string query){

	/* Setup and connect to cluster */
	CassCluster* cluster = cass_cluster_new();
	CassSession* session = cass_session_new();

	/* Add contact points */
	cass_cluster_set_contact_points(cluster, dataBaseConfiguration.contactPoints.c_str());

	/* Provide the cluster object as configuration to connect the session */
	CassFuture* connect_future = cass_session_connect(session, cluster);

	/* This operation will block until the result is ready */
	CassError rc = cass_future_error_code(connect_future);

	printf("Connect result: %s\n", cass_error_desc(rc));

	/* Run queries... */

	/* Build statement and execute query */

	CassStatement* statement = cass_statement_new(query.c_str(), 0);

	CassFuture* result_future = cass_session_execute(session, statement);

	if (cass_future_error_code(result_future) == CASS_OK) {
		/* Retrieve result set and iterate over the rows */
		const CassResult* result = cass_future_get_result(result_future);
		CassIterator* rows = cass_iterator_from_result(result);

		cass_result_free(result);
		cass_iterator_free(rows);
	}
	else {
		/* Handle error */
		const char* message;
		size_t message_length;
		cass_future_error_message(result_future, &message, &message_length);
		fprintf(stderr, "Unable to run query: '%.*s'\n",
			(int)message_length, message);
		return false;
	}

	cass_statement_free(statement);
	cass_future_free(connect_future);
	cass_session_free(session);
	cass_cluster_free(cluster);

	return true;
}


DataBaseGenerator::~DataBaseGenerator()
{
}
