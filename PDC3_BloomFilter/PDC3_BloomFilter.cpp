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
	/*DataBaseConfiguration dbConf;
	dbConf.contactPoints = "127.0.0.1";
	dbConf.keySpace = "documentDBV1";
	dbConf.table = "documentTable";
	BloomFilterBasedDBController *controller = new BloomFilterBasedDBController(dbConf, 10000,5, nullptr);
	controller->initBloomFilter();
	string result = controller->processDocumentsTestFile("myTestFile.txt",BLOOM_VERIFICATION);
	cout << result << endl;
	system("Pause");*/
	return 0; 
}