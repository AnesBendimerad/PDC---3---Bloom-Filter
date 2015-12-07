#include "stdafx.h"
#include "BloomFilterServer.h"
#include <iostream>
#include <fstream>
using namespace std;

BloomFilterServer::BloomFilterServer(string configFilePath) : Server()
{
	
	string element;
	ifstream configFile(configFilePath.c_str());
	unsigned int port;

	DataBaseConfiguration config;
	config.contactPoints = DEFAULT_DB_CONTACTPOINTS;
	config.keySpace = DEFAULT_DB_KEYSPACE;
	config.table = DEFAULT_DB_TABLE;
	uint32_t bloomSizeInBit = DEFAULT_BF_SIZE;
	uint32_t bloomHashNumber = DEFAULT_BF_HASHNUMBER;

	if (configFile.is_open())
	{
		while (configFile >> element)
		{
			if (element.compare(CONFIG_SERVER_PORT) == 0)
			{
				configFile >> this->port;
			}
			else if (element.compare(CONFIG_DB_CONTACTPOINTS) == 0)
			{
				configFile >> config.contactPoints;
			}
			else if (element.compare(CONFIG_DB_KEYSPACE) == 0)
			{
				configFile >> config.keySpace;
			}
			else if (element.compare(CONFIG_DB_TABLE) == 0)
			{
				configFile >> config.table;
			}
			else if (element.compare(CONFIG_BF_SIZE) == 0)
			{
				configFile >> bloomSizeInBit;
			}
			else if (element.compare(CONFIG_BF_HASHNUMBER) == 0)
			{
				configFile >> bloomHashNumber;
			}
		}
	}

	this->bloomFilterBasedDBController = new BloomFilterBasedDBController(config, bloomSizeInBit, bloomHashNumber, nullptr);
}


BloomFilterServer::~BloomFilterServer()
{

}

void BloomFilterServer::init()
{
	bloomFilterBasedDBController->initBloomFilter();
	cout << "Initilized the Bloom Filter" << endl << "-----------------------" << endl;
}

string BloomFilterServer::executeRequest(string query)
{
	cout << "Searching "<< query << " ... " << endl;
	/*
	if (bloomFilterBasedDBController->doesDocumentNumberExist(query, BLOOM_AND_DB_VERIFICATION))
	{
		cout << "Answer sent !" << endl;
		return query+" exists in the set ";
	}
	else
	{
		cout << "Answer sent !" << endl;
		return query + " doesn't exists in the set ";
	}
	*/

	Document *document = bloomFilterBasedDBController->getDocument(query);
	if (document==nullptr)
	{
		cout << "Answer sent !" << endl;
		return query + " doesn't exists in the set ";
	}
	else
	{
		cout << "Answer sent !" << endl;
		return "document "+query + " details : "+document->documentNumber+" | "+ document->documentType+ " | " + document->countryCode;
	}
}

void BloomFilterServer::destroy()
{
	delete bloomFilterBasedDBController;
}
