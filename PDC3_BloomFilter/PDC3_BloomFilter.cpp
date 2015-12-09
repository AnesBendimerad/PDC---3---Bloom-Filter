// PDC3_BloomFilter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <stdio.h>
#include "BloomFilterServer.h"
#include "DataBaseGenerator.h"
#include "RandomAdditionalOperations.h"
#include "TestFileGenerator.h"
using namespace std;

#define CONFIG_SERVER_PORT			"port"
#define CONFIG_DB_CONTACTPOINTS		"db.contactPoints" 
#define CONFIG_DB_KEYSPACE			"db.keySpace" 
#define CONFIG_DB_TABLE				"db.table" 
#define CONFIG_BF_SIZE				"bf.sizeInBit" 
#define CONFIG_BF_HASHNUMBER		"bf.hashFunctionNumber"

int main(int argc, char** argv) {
	//commande progName port=2014 db.contactPoints=127.0.0.1 db.keySpace=documentDataBase db.table=documentTable bf.sizeInBit=10009 bf.hashFunctionNumber=5
	//command : prog configFileName
	
	unsigned int port = 0;
	DataBaseConfiguration config;
	config.contactPoints = "";
	config.keySpace = "";
	config.table = "";
	uint32_t bloomSizeInBit = 0;
	uint32_t bloomHashNumber = 0;

	bool error = (argc != 7);
	if (! error)
	{
		string argument;
		string argumentName;
		string argumentValue;

		for (unsigned int i = 1;i < 7;i++)
		{
			argument = string(argv[i]);
			unsigned int equalPosition = argument.find("=");
			if (equalPosition < string::npos) {
				argumentName = argument.substr(0, equalPosition);
				argumentValue = argument.substr(equalPosition+1);

				if (strcmp(argumentName.c_str(), CONFIG_SERVER_PORT) == 0) {
					if (port == 0) port = atoi(argumentValue.c_str());
					else error = true;
					if (port == 0) error = true;
				}
				else if (strcmp(argumentName.c_str(), CONFIG_DB_CONTACTPOINTS) == 0)
				{
					if (config.contactPoints.empty()) {
						config.contactPoints = argumentValue;
					}
					else error = true;
				}
				else if (strcmp(argumentName.c_str(), CONFIG_DB_KEYSPACE) == 0)
				{
					if (config.keySpace.empty()) {
						config.keySpace = argumentValue;
					}
					else error = true;
				}
				else if (strcmp(argumentName.c_str(), CONFIG_DB_TABLE) == 0) 
				{
					if (config.table.empty()) {
						config.table = argumentValue;
					}
					else error = true;
				}
				else if (strcmp(argumentName.c_str(), CONFIG_BF_SIZE) == 0) {
					if (bloomSizeInBit == 0) bloomSizeInBit = atoi(argumentValue.c_str());
					else error = true;
					if (bloomSizeInBit == 0) error = true;
				}
				else if (strcmp(argumentName.c_str(), CONFIG_BF_HASHNUMBER) == 0) {
					if (bloomHashNumber == 0) bloomHashNumber = atoi(argumentValue.c_str());
					else error = true;
					if (bloomHashNumber == 0) error = true;
				}
				else error = true;
			}
			else error = true;
			if (error) break;
		}
	}

	if (!error) {
		cout << "Configuration of the bloom filter : " << endl;
		cout << "\t" << CONFIG_SERVER_PORT << " : " << to_string(port) << endl;
		cout << "\t" << CONFIG_DB_CONTACTPOINTS << " : " << config.contactPoints << endl;
		cout << "\t" << CONFIG_DB_KEYSPACE << " : " << config.keySpace << endl;
		cout << "\t" << CONFIG_DB_TABLE << " : " << config.table << endl;
		cout << "\t" << CONFIG_BF_SIZE << " : " << bloomSizeInBit << endl;
		cout << "\t" << CONFIG_BF_HASHNUMBER << " : " << bloomHashNumber << endl;
		
		BloomFilterBasedDBController* bloomFilterBasedDBController = new BloomFilterBasedDBController(config, bloomSizeInBit, bloomHashNumber, nullptr);
		BloomFilterServer bloomFilterServer(port, bloomFilterBasedDBController);
		
		cout << "--------------------------------------------" << endl;
		cout << "Bloom server launched" << endl;
		
		bloomFilterServer.start();
	}
	else {
		cout << "Error" << ":" << "Please specify all the parameters" << endl;
	}
	return 0; 
}
