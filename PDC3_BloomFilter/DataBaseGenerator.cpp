#include "stdafx.h"
#include <time.h>
#include <algorithm>
#include "DataBaseGenerator.h"
#include "Document.h"
#include "DataBaseHandler.h"


using namespace std;

DataBaseGenerator::DataBaseGenerator(DataBaseConfiguration dataBaseConfiguration, unsigned int dataBaseSize)
{
	countryCode = loadCountryCode();
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
		 
		doc.documentNumber = RandomString(documentNumberSize);
		doc.countryCode = RandomCountryCode();
		doc.documentType = RandomString(documentTypeSize);
		dataBaseHandler->addDocument(&doc);
		i++;
	}
	delete dataBaseHandler;
	return true;
}

string DataBaseGenerator::RandomString(unsigned int len)
{
	
	string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	unsigned int pos;
	while (str.size() != len) {
		pos = ((rand() % (str.size() - 1)));
		str.erase(pos, 1);
	}
	return str;
}

std::vector<std::string> * DataBaseGenerator::loadCountryCode(){

	std::vector<std::string> * countryCode = new std::vector<std::string>();

	countryCode->push_back("ABW");
	countryCode->push_back("AFG");
	countryCode->push_back("AGO");
	countryCode->push_back("AIA");
	countryCode->push_back("ALA");
	countryCode->push_back("ALB");
	countryCode->push_back("AND");
	countryCode->push_back("ARE");
	countryCode->push_back("ARG");
	countryCode->push_back("ARM");
	countryCode->push_back("ASM");
	countryCode->push_back("ATA");
	countryCode->push_back("ATF");
	countryCode->push_back("ATG");
	countryCode->push_back("AUS");
	countryCode->push_back("AUT");
	countryCode->push_back("AZE");
	countryCode->push_back("BDI");
	countryCode->push_back("BEL");
	countryCode->push_back("BEN");
	countryCode->push_back("BES");
	countryCode->push_back("BFA");
	countryCode->push_back("BGD");
	countryCode->push_back("BGR");
	countryCode->push_back("BHR");
	countryCode->push_back("BHS");
	countryCode->push_back("BIH");
	countryCode->push_back("BLM");
	countryCode->push_back("BLR");
	countryCode->push_back("BLZ");
	countryCode->push_back("BMU");
	countryCode->push_back("BOL");
	countryCode->push_back("BRA");
	countryCode->push_back("BRB");
	countryCode->push_back("BRN");
	countryCode->push_back("BTN");
	countryCode->push_back("CMR");
	countryCode->push_back("COD");
	countryCode->push_back("COG");
	countryCode->push_back("COK");
	countryCode->push_back("COL");
	countryCode->push_back("COM");
	countryCode->push_back("CPV");
	countryCode->push_back("CRI");
	countryCode->push_back("CUB");
	countryCode->push_back("CUW");
	countryCode->push_back("CXR");
	countryCode->push_back("CYM");
	countryCode->push_back("CYP");
	countryCode->push_back("CZE");
	countryCode->push_back("DEU");
	countryCode->push_back("DJI");
	countryCode->push_back("MAR");
	countryCode->push_back("MCO");
	countryCode->push_back("MDA");
	

	return countryCode;
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

	printf("Database connection result: %s\n", cass_error_desc(rc));

	/* Build statement and execute query ... */

	/* Create KeySpace*/
	string createKeyspace = "create keyspace if not exists " + DataBaseGenerator::dataBaseConfiguration.keySpace + " with replication={'class':'SimpleStrategy', 'replication_factor':1};";
	CassStatement* statement = cass_statement_new(createKeyspace.c_str(), 0);
	CassFuture* result_future = cass_session_execute(session, statement);
	if (cass_future_error_code(result_future) != CASS_OK)
	{
		/* Handle error */
		const char* message;
		size_t message_length;
		cass_future_error_message(result_future, &message, &message_length);
		fprintf(stderr, "Unable to run query: '%.*s'\n",(int)message_length, message);
		return false;
	}

	/* Create Table*/
	string createTable = "create table if not exists " + DataBaseGenerator::dataBaseConfiguration.keySpace + "." + DataBaseGenerator::dataBaseConfiguration.table + " ( " + string(DOCUMENT_NUMBER) + " varchar primary key, " + string(DOCUMENT_TYPE) + " varchar, " + string(COUNTRY_CODE) + " varchar); ";
	statement = cass_statement_new(createTable.c_str(), 0);
	result_future = cass_session_execute(session, statement);
	if (cass_future_error_code(result_future) != CASS_OK)
	{
		/* Handle error */
		const char* message;
		size_t message_length;
		cass_future_error_message(result_future, &message, &message_length);
		fprintf(stderr, "Unable to run query: '%.*s'\n", (int)message_length, message);
		return false;
	}

	/* Create Index*/
	string creatIndex = "create index if not exists " + string(COUNTRY_CODE) + "_index on " + DataBaseGenerator::dataBaseConfiguration.keySpace + "." + DataBaseGenerator::dataBaseConfiguration.table + "(" + string(COUNTRY_CODE) + "); ";
	statement = cass_statement_new(creatIndex.c_str(), 0);
	result_future = cass_session_execute(session, statement);
	if (cass_future_error_code(result_future) != CASS_OK)
	{
		/* Handle error */
		const char* message;
		size_t message_length;
		cass_future_error_message(result_future, &message, &message_length);
		fprintf(stderr, "Unable to run query: '%.*s'\n", (int)message_length, message);
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