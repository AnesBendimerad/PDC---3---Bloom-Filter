#pragma once
#include "Server.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include "BloomFilterBasedDBController.h"
#include "TestFileGenerator.h"

#define EXISTS_COMMAND				"exists" // exists <document_number> [<verification_type>]
#define GET_COMMAND					"get"	 // get    <document_number>
#define REINIT_COMMAND				"reinit" // reinit <bloom_filter_size> <hash_function_number> <hash_function_id>
#define TEST_COMMAND				"test"   // test <test_file_size> <valid_document_pourcentage> [<verification_type>] [USE_LAST_IF_EXISTS]
#define USE_LAST_IF_EXISTS			"USE_LAST_IF_EXISTS"
#define STATS_COMMAND				"stats"  // stats // return statistic concerning the Bloom Filter
#define RESPONSE_END_TAG			"<END/>"

class BloomFilterServer : public Server
{
public:
	BloomFilterServer(unsigned int port, BloomFilterBasedDBController* bloomFilterBasedDBController);
	~BloomFilterServer();
private : 
	virtual void init();
	string reinit(uint32_t bloomFilterSizeInBit, unsigned int bloomFilterHashFunctionsNumber, IHasher * bloomFilterHashFunction = nullptr);
	virtual string executeRequest(string query);
	virtual void destroy();

	vector<string> getCommandArgument(string query); // return empty vector if the command is not correct
	BloomFilterBasedDBController* bloomFilterBasedDBController;
	string lastTestFilePath;
};

