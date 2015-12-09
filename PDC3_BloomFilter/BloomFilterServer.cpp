#include "stdafx.h"
#include "BloomFilterServer.h"
#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;

BloomFilterServer::BloomFilterServer(unsigned int port, BloomFilterBasedDBController* bloomFilterBasedDBController) : Server()
{
	this->port=port;
	this->bloomFilterBasedDBController = bloomFilterBasedDBController;
	lastTestFilePath = "";
}

void BloomFilterServer::init()
{
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	bloomFilterBasedDBController->initBloomFilter();
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	unsigned long long duration = (t2 - t1).count() / 1000000;
	string informations = to_string(duration) + " ms";

	cout << "Initilized the Bloom Filter in " << informations << endl << "------------------------------------------" << endl;
}

void BloomFilterServer::reinit(uint32_t bloomFilterSizeInBit, unsigned int bloomFilterHashFunctionsNumber, IHasher * bloomFilterHashFunction)
{
	if (bloomFilterSizeInBit == 0) bloomFilterHashFunctionsNumber = 2;
	if (bloomFilterHashFunctionsNumber == 0) bloomFilterHashFunctionsNumber = 1;

	this->bloomFilterBasedDBController->reinitBloomFilter(bloomFilterSizeInBit, bloomFilterHashFunctionsNumber, bloomFilterHashFunction);
	cout << "Reinitilized the Bloom Filter" << endl;
	cout << "\t" << "bloom filter size" << " : " << bloomFilterSizeInBit << endl;
	cout << "\t" << "bloom filter hash function number" << " : " << bloomFilterHashFunctionsNumber << endl;
	cout << "------------------------------------------" << endl;
}

string BloomFilterServer::executeRequest(string query)
{
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

	string ok_or_ko = "OK";
	string response;
	string informations;
	string answer; //answer = <ok_or_ko> (<response>) (<informations>) <END/>
	
	cout << "exectuting "<< query << " ... " << endl;
	
	vector<string> tokens = this->getCommandArgument(query);
	
	if (tokens.size() == 0)
	{
		ok_or_ko = "KO";
		response = "Incorrect syntax !";
	}
	else
	{
		if (strcmp(tokens[0].c_str(),GET_COMMAND)==0)
		{
			Document *document = bloomFilterBasedDBController->getDocument(tokens[1]);
			response = documentToString(document);
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
				response = "1";
				if (option == BLOOM_VERIFICATION)
				{
					response += "-"; // if "-" is added => Possibility of false positive
				}
			}
			else
			{
				response = "0";
			}
		} 
		else if (strcmp(tokens[0].c_str(), REINIT_COMMAND) == 0)
		{
			this->reinit(atoi(tokens[1].c_str()), atoi(tokens[2].c_str()));
		}
		else if (strcmp(tokens[0].c_str(), TEST_COMMAND) == 0)
		{
			// run test command
			int testFileSize = atoi(tokens[1].c_str());
			float validDocumentPourcentage= float(atof(tokens[2].c_str()));
			int verificationType = BLOOM_AND_DB_VERIFICATION;
			if ((tokens.size() == 5) || (tokens.size() == 4 && (strcmp(tokens[3].c_str(), USE_LAST_IF_EXISTS) != 0))) {
				verificationType = atoi(tokens[3].c_str());
			}
			if (tokens.size() == 5 && (tokens[4].compare(USE_LAST_IF_EXISTS) != 0)) {
				ok_or_ko = "KO";
				response = "Incorrect syntax !";
			}
			if (lastTestFilePath.compare("") == 0 || tokens.size() == 3 || (tokens.size() == 4 && tokens[3].compare(USE_LAST_IF_EXISTS) != 0))
			{
				lastTestFilePath = DEFAULT_FILE_PATH;
				TestFileGenerator * generator = new TestFileGenerator(bloomFilterBasedDBController->getDataBaseHandler(), testFileSize, validDocumentPourcentage, lastTestFilePath);
				generator->generate();
			}
			response = bloomFilterBasedDBController->processDocumentsTestFile(lastTestFilePath, verificationType);
		}
	}

	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	unsigned long long duration = (t2 - t1).count()/1000000;
	informations = "time : "+to_string(duration)+" ms";

	answer = ok_or_ko + " (" + response + ")" + " (" + informations + ") "+ RESPONSE_END_TAG;
	cout << "Answer sent : " << answer << endl;
	cout << "--------------------------------" << endl;
	return answer;
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
		else if (strcmp(tokens[0].c_str(), REINIT_COMMAND) == 0 && tokens.size() == 3)
		{
			return tokens;
		}
		else if (strcmp(tokens[0].c_str(), TEST_COMMAND) == 0 && tokens.size() >= 3 && tokens.size() <= 5) {
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
