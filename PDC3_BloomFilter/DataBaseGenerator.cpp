#include "stdafx.h"
#include <time.h>
#include <algorithm>
#include "DataBaseGenerator.h"
#include "Document.h"
#include "DataBaseHandler.h"
#include "ErreurManager.h"

using namespace std;

DataBaseGenerator::DataBaseGenerator(DataBaseConfiguration dataBaseConfiguration, unsigned int dataBaseSize)
{
	DataBaseGenerator::countryCode = new vector<string>(COUNTRY_CODES_BAG);
	DataBaseGenerator::dataBaseConfiguration = dataBaseConfiguration;
	DataBaseGenerator::dataBaseSize = dataBaseSize;
}

bool DataBaseGenerator::createAndGenerateDB()
{
	this->createDB();
	DataBaseHandler * dataBaseHandler = new DataBaseHandler(this->dataBaseConfiguration);
	Document doc;
	unsigned int i = 0;
	srand(time(NULL));

	while (i < dataBaseSize){
		 
		doc.documentNumber = getRandomString(documentNumberSize);
		doc.countryCode = RandomCountryCode();
		doc.documentType = getRandomString(documentTypeSize);
		dataBaseHandler->addDocument(&doc);
		i++;
	}
	delete dataBaseHandler;
	return true;
}

string DataBaseGenerator::RandomCountryCode(){

	std::random_shuffle(countryCode->begin(), countryCode->end());
	return countryCode->at((rand() % (countryCode->size() - 1)));
}

bool DataBaseGenerator::createDB(){

	/* Setup and connect to cluster */
	CassCluster* cluster = cass_cluster_new();
	CassSession* session = cass_session_new();

	/* Add contact points */
	cass_cluster_set_contact_points(cluster, dataBaseConfiguration.contactPoints.c_str());

	/* Provide the cluster object as configuration to connect the session */
	CassFuture* connect_future = cass_session_connect(session, cluster);

	/* This operation will block until the result is ready */
	CassError rc = cass_future_error_code(connect_future);

	//printf("Database connection result: %s\n", cass_error_desc(rc));

	/* Build statement and execute query ... */

	/* Create KeySpace*/
	string createKeyspace = "create keyspace if not exists " + DataBaseGenerator::dataBaseConfiguration.keySpace + " with replication={'class':'SimpleStrategy', 'replication_factor':1};";
	CassStatement* statement = cass_statement_new(createKeyspace.c_str(), 0);
	CassFuture* result_future = cass_session_execute(session, statement);
		if (cass_future_error_code(result_future) != CASS_OK)
		{
			/* Handle error */
			throw new exception(ErreurManager::getError(DB_KEYSPACE_ERROR).c_str());
		    return false;
	    }

	/* Create Table*/
	string createTable = "create table if not exists " + DataBaseGenerator::dataBaseConfiguration.keySpace + "." + DataBaseGenerator::dataBaseConfiguration.table + " ( " + string(DOCUMENT_NUMBER) + " varchar primary key, " + string(DOCUMENT_TYPE) + " varchar, " + string(COUNTRY_CODE) + " varchar); ";
	statement = cass_statement_new(createTable.c_str(), 0);
	result_future = cass_session_execute(session, statement);

		if (cass_future_error_code(result_future) != CASS_OK)
		{
			/* Handle error */
			throw new exception(ErreurManager::getError(DB_TABLE_ERROR).c_str());
		return false;
	   }

	/* Create Index*/
	string creatIndex = "create index if not exists on " + DataBaseGenerator::dataBaseConfiguration.keySpace + "." + DataBaseGenerator::dataBaseConfiguration.table + "(" + string(COUNTRY_CODE) + "); ";
	statement = cass_statement_new(creatIndex.c_str(), 0);
	result_future = cass_session_execute(session, statement);

	if (cass_future_error_code(result_future) != CASS_OK)
		{
			/* Handle error */
			throw new exception(ErreurManager::getError(DB_INDEX_ERROR).c_str());
			return false;

		}
	

	/* Free database */
	cass_statement_free(statement);
	cass_future_free(connect_future);
	cass_session_free(session);
	cass_cluster_free(cluster);
	return true;
}

DataBaseGenerator::~DataBaseGenerator()
{
	delete countryCode;
}