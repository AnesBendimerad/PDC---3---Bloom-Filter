#include "stdafx.h"
#include "BloomFilterServer.h"
#include <iostream>
#include <fstream>
using namespace std;

BloomFilterServer::BloomFilterServer(string configFilePath) : Server()
{
	this->prepareFromConfigFile(configFilePath);
}


void BloomFilterServer::prepareFromConfigFile(string configFilePath)
{
	string element;
	ifstream configFile(configFilePath.c_str());
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

void BloomFilterServer::init()
{
	bloomFilterBasedDBController->initBloomFilter();
	cout << "Initilized the Bloom Filter" << endl << "-----------------------" << endl;
}

void BloomFilterServer::reinit(string configFilePath)
{
	this->prepareFromConfigFile(configFilePath);
	this->bloomFilterBasedDBController->initBloomFilter();
	cout << "Reinitilized the Bloom Filter" << endl << "-----------------------" << endl;
}

string BloomFilterServer::executeRequest(string query)
{
	string response = "";
	cout << "exectuting "<< query << " ... " << endl;
	
	vector<string> tokens = this->getCommandArgument(query);
	
	if (tokens.size() == 0)
	{
		response = "Incorrect query !";
	}
	else
	{
		if (strcmp(tokens[0].c_str(),GET_COMMAND)==0)
		{
			Document *document = bloomFilterBasedDBController->getDocument(tokens[1]);
			if (document == nullptr)
			{
				response = "document doesn't exists in the set ";
			}
			else
			{
				response = "document details : " + document->documentNumber + " | " + document->documentType + " | " + document->countryCode;
			}
		}
		else if (strcmp(tokens[0].c_str(), EXISTS_COMMAND)==0)
		{
			unsigned int option = BLOOM_AND_DB_VERIFICATION;
			if (tokens.size() == 3)
			{
				option = atoi(tokens[2].c_str());
			}

			if (bloomFilterBasedDBController->doesDocumentNumberExist(tokens[1], option))
			{
				response = "document exists in the set ";
				if (option == BLOOM_VERIFICATION)
				{
					response += "( with a risk of FALSE POSITIVE )";
				}
			}
			else
			{
				response = "document doesn't exists in the set ";
			}
		} 
		else if (strcmp(tokens[0].c_str(), REINIT_COMMAND) == 0)
		{
			this->reinit(tokens[1]);
			response = "Bloom filter reinitilized";
		}
	}
	
	cout << "Answer sent : " << response << endl;
	cout << "--------------------------------" << endl;
	return response+RESPONSE_END_TAG;
}

vector<string> BloomFilterServer::getCommandArgument(string query)
{
	istringstream iss(query);
	vector<string> tokens{ istream_iterator<string>{iss},istream_iterator<string>{} };

	

	if (tokens.size() > 0)
	{
		if (strcmp(tokens[0].c_str(), STOP_COMMAND)==0 && tokens.size() == 1)
		{
			return tokens;
		}
		else if (strcmp(tokens[0].c_str(), GET_COMMAND)==0 && tokens.size() == 2)
		{
			return tokens;
		}
		else if (strcmp(tokens[0].c_str(), EXISTS_COMMAND)==0 && tokens.size() >= 2 && tokens.size() <= 3)
		{
			return tokens;
		}
		else if (strcmp(tokens[0].c_str(), REINIT_COMMAND) == 0 && tokens.size() == 2)
		{
			return tokens;
		}
	}
	return vector<string>();
}

void BloomFilterServer::destroy()
{
	delete bloomFilterBasedDBController;
}

BloomFilterServer::~BloomFilterServer()
{

}
