#pragma once
#include "Server.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include "BloomFilterBasedDBController.h"

#define CONFIG_SERVER_PORT			"port"
#define CONFIG_DB_CONTACTPOINTS		"db.contactPoints" 
#define CONFIG_DB_KEYSPACE			"db.keySpace" 
#define CONFIG_DB_TABLE				"db.table" 
#define CONFIG_BF_SIZE				"bf.sizeInBit" 
#define CONFIG_BF_HASHNUMBER		"bf.hashFunctionNumber"

#define DEFAULT_DB_CONTACTPOINTS	"127.0.0.1"
#define DEFAULT_DB_KEYSPACE			"documentDataBase"
#define DEFAULT_DB_TABLE			"documentTable"
#define DEFAULT_BF_SIZE				10009
#define DEFAULT_BF_HASHNUMBER		5

#define EXISTS_COMMAND				"exists" // exists <document_number> [<option_of_search>]
#define GET_COMMAND					"get"	 // get    <document_number>

class BloomFilterServer :
	public Server
{
public:
	BloomFilterServer(string configFilePath);
	~BloomFilterServer();
private : 
	virtual void init();
	virtual string executeRequest(string query);
	virtual void destroy();

	vector<string> getCommandArgument(string query); // return empty vector if the command is not correct
	BloomFilterBasedDBController* bloomFilterBasedDBController;
	
};

