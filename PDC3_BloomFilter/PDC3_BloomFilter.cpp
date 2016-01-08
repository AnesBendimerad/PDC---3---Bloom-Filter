// PDC3_BloomFilter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <stdio.h>
#include "BloomFilterServer.h"
#include "DataBaseGenerator.h"
#include "RandomAdditionalOperations.h"
#include "TestFileGenerator.h"
#include "IHasher.h"
#include "MurmurHasher.h"
#include "Fnv1aHasher.h"
using namespace std;
#define MIN_LAUNCH_ARGUMENTS_NUMBER		8
#define CONFIG_SERVER_PORT			"port"
#define CONFIG_DB_CONTACTPOINTS		"db.contactPoints" 
#define CONFIG_DB_KEYSPACE			"db.keySpace" 
#define CONFIG_DB_TABLE				"db.table" 

#define CONFIG_BF_MAX_FP_RATE       "bf.maxFPRate"
#define CONFIG_BF_SIZE				"bf.sizeInBit" 
#define CONFIG_BF_HASHNUMBER		"bf.hashFunctionNumber"
#define CONFIG_BF_HASH_TYPE			"bf.hashType"
#define CONFIG_DBSIZE				"dbSize"

#define COMMAND_LAUNCH_SERVER		"launchServer"
#define COMMAND_GENERATE_DB			"generateDB"

bool launchServerCommand(int argc, char** argv)
{
	unsigned int port = 0;
	DataBaseConfiguration config;
	config.contactPoints = "";
	config.keySpace = "";
	config.table = "";
	uint32_t bloomSizeInBit = 0;
	uint32_t bloomHashNumber = 0;
	int hashFunctionId = -1;
	double maxFPRate = 0;

	bool error = ! (argc == 8 || argc == 9);
	if (!error)
	{
		string argument;
		string argumentName;
		string argumentValue;

		for (int i = 2;i < argc;i++)
		{
			argument = string(argv[i]);
			unsigned int equalPosition = argument.find("=");
			if (equalPosition < string::npos) {
				argumentName = argument.substr(0, equalPosition);
				argumentValue = argument.substr(equalPosition + 1);

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
				else if (strcmp(argumentName.c_str(), CONFIG_BF_SIZE) == 0 && argc==9) {
					if (bloomSizeInBit == 0) bloomSizeInBit = atoi(argumentValue.c_str());
					else error = true;
					if (bloomSizeInBit == 0) error = true;
				}
				else if (strcmp(argumentName.c_str(), CONFIG_BF_HASHNUMBER) == 0 && argc == 9) {
					if (bloomHashNumber == 0) bloomHashNumber = atoi(argumentValue.c_str());
					else error = true;
					if (bloomHashNumber == 0) error = true;
				}
				else if (strcmp(argumentName.c_str(), CONFIG_BF_MAX_FP_RATE) == 0 && argc == 8) {
					if (maxFPRate == 0) maxFPRate = atof(argumentValue.c_str());
					if (maxFPRate <= 0 || maxFPRate >= 1) error=true;
				}
				else if (strcmp(argumentName.c_str(), CONFIG_BF_HASH_TYPE) == 0) {
					if (hashFunctionId < 0) hashFunctionId = atoi(argumentValue.c_str());
					else error = true;
					if (hashFunctionId > 1 || hashFunctionId < 0) error = true;
				}
				else
				{
					error = true;
				}
			}
			else error = true;
			if (error) break;
		}
	}

	if (!error) {
		IHasher * hasher=nullptr;
		if (hashFunctionId == MURMUR_HASHER) {
			hasher = new MurmurHasher();
		}
		else if (hashFunctionId==FNV1A_HASHER){
			hasher = new Fnv1aHasher();
		} 
		else hasher = new MurmurHasher();

		BloomFilterBasedDBController* bloomFilterBasedDBController;
		if (argc==9) bloomFilterBasedDBController = new BloomFilterBasedDBController(config, bloomSizeInBit, bloomHashNumber, hasher);
		else bloomFilterBasedDBController = new BloomFilterBasedDBController(config, maxFPRate, hasher);
		BloomFilterServer bloomFilterServer(port, bloomFilterBasedDBController);

		std::cout << "Configuration of the bloom filter : " << endl;
		std::cout << "\t" << CONFIG_SERVER_PORT << " : " << to_string(port) << endl;
		std::cout << "\t" << CONFIG_DB_CONTACTPOINTS << " : " << config.contactPoints << endl;
		std::cout << "\t" << CONFIG_DB_KEYSPACE << " : " << config.keySpace << endl;
		std::cout << "\t" << CONFIG_DB_TABLE << " : " << config.table << endl;
		if (argc == 9) std::cout << "\t" << CONFIG_BF_SIZE << " : " << bloomSizeInBit << endl;
		if (argc == 8) std::cout << "\t" << CONFIG_BF_MAX_FP_RATE << " : " << maxFPRate << endl;
		std::cout << "\t" << CONFIG_BF_HASH_TYPE << " : " << hasher->getName() << endl;
		if (argc == 9) std::cout << "\t" << CONFIG_BF_HASHNUMBER << " : " << bloomHashNumber << endl;

		std::cout << "--------------------------------------------" << endl;
		std::cout << "Constructing the Bloom Filter ..." << endl;
		std::cout << "--------------------------------------------" << endl;

		bloomFilterServer.start();
	}
	return !error;
}

bool generateDBCommand(int argc, char** argv)
{
	DataBaseConfiguration config;
	config.contactPoints = "";
	config.keySpace = "";
	config.table = "";
	uint32_t dbSize = 0;

	bool error = (argc != 6);
	if (!error)
	{
		string argument;
		string argumentName;
		string argumentValue;

		for (int i = 2;i < argc;i++)
		{
			argument = string(argv[i]);
			unsigned int equalPosition = argument.find("=");
			if (equalPosition < string::npos) {
				argumentName = argument.substr(0, equalPosition);
				argumentValue = argument.substr(equalPosition + 1);

				if (strcmp(argumentName.c_str(), CONFIG_DB_CONTACTPOINTS) == 0)
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
				else if (strcmp(argumentName.c_str(), CONFIG_DBSIZE) == 0) {
					if (dbSize == 0) dbSize = atoi(argumentValue.c_str());
					else error = true;
					if (dbSize == 0) error = true;
				}
				else error = true;
			}
			else error = true;
			if (error) break;
		}
	}

	if (!error) {
		std::cout << "Generation de la base de donnees ... " << endl;
		std::cout << "\t" << CONFIG_DB_CONTACTPOINTS << " : " << config.contactPoints << endl;
		std::cout << "\t" << CONFIG_DB_KEYSPACE << " : " << config.keySpace << endl;
		std::cout << "\t" << CONFIG_DB_TABLE << " : " << config.table << endl;
		std::cout << "\t" << CONFIG_DBSIZE << " : " << dbSize << endl;

		DataBaseGenerator* DBG = new DataBaseGenerator(config, dbSize);
		DBG->createAndGenerateDB();
		std::cout << "Generation completed of " << dbSize << " non valid documents" << endl;
		std::cout << "--------------------------------------------" << endl << endl;
	}
	return !error;
}

int main(int argc, char** argv) {
	std::cout << "--------------------------------------------" << endl;
	bool error = (argc < 2);
	try {
		if (!error)
		{
			if (strcmp(argv[1], COMMAND_LAUNCH_SERVER) == 0 && (argc == 8 || argc == 9)) {
				//commande 1 - <progName> launchServer port=2014 db.contactPoints=127.0.0.1 db.keySpace=documentDataBase db.table=documentTable bf.sizeInBit=10009 bf.hashFunctionNumber=5
				error = !launchServerCommand(argc, argv);
			}
			else if (strcmp(argv[1], COMMAND_GENERATE_DB) == 0 && argc == 6)
			{
				//commande 2 - <progName> generateDB db.contactPoints=127.0.0.1 db.keySpace=documentDataBase db.table=documentTable dbSize=100000
				error = !generateDBCommand(argc, argv);
			}
			else error = true;
		}
		if (error)
		{
			std::cout << "Error " << ":" << " Please specify all the parameters correctly" << endl;
		}
	}
	catch (const exception *e) {
		cerr << "An exception has occured: " << e->what() << endl;
	}
	return 0; 
}

