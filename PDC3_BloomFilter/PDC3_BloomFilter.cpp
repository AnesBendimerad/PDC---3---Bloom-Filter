// PDC3_BloomFilter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cassandra.h>
#include <conio.h>
#include <stdio.h>
#include "BloomFilter.h"
#include "IHasher.h"
#include "MurmurHasher.h"
#include "DataBaseGenerator.h"
#include "BloomFilterBasedDBController.h"

using namespace std;

int main() {
	DataBaseConfiguration config;
	config.contactPoints = "127.0.0.1";
	config.keySpace = "documentDataBase";
	config.table = "documentTable";

	//DataBaseGenerator* generator = new DataBaseGenerator(config,1000);
	//generator->generate();
	//delete generator;

	uint32_t bloomSizeInBit = 10009;
	uint32_t bloomHashNumber = 5;
	IHasher* hasher = new MurmurHasher();

	BloomFilterBasedDBController* bloomFilterController = new BloomFilterBasedDBController(config, bloomSizeInBit, bloomHashNumber);
	bloomFilterController->construct();

	string testKey = "502";

	if (bloomFilterController->doesDocumentNumberExist(testKey,BLOOM_AND_DB_VERIFICATION))
	{
		cout << testKey << " exists in the set " << endl;
	}
	else
	{
		cout << testKey << " doesn't exists in the set " << endl;
	}

	system("Pause");
}