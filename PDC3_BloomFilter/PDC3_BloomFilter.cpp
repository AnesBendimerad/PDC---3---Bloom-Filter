// PDC3_BloomFilter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <stdio.h>
#include "BloomFilterServer.h"
#include "DataBaseGenerator.h"
using namespace std;

int main(int argc, char** argv) {
	//command : prog configFileName
	if (argc == 2)
	{
		string configFilePath = argv[1];
		BloomFilterServer bloomFilterServer(configFilePath);
		bloomFilterServer.start();
	}
	else {
		cout << "error : you must specify a configuration file" << endl;
	}
	/*
	DataBaseConfiguration dbConf;
	dbConf.contactPoints = "127.0.0.1";
	dbConf.keySpace = "documentDBV1";
	dbConf.table = "documentTable";
	DataBaseHandler * dbHandler = new DataBaseHandler(dbConf);
	DocumentIterator * docIterator = dbHandler->getDocumentIterator();
	cout << "documents count : " << docIterator->getSize()<< endl;*/
	/*Document * doc;
	cout << "begin iterating" << endl;
	int i = 1;
	while ((doc = docIterator->getNextDocument()) != nullptr) {
		cout << "document num " << i << endl;
		cout << "doc number : " << doc->documentNumber << endl;
		cout << "doc type : " << doc->documentType << endl;
		cout << "country code : " << doc->countryCode << endl;
		i++;
	}
	cout << "end iterating" << endl;*/
	
	//system("Pause");
	return 0; 
}