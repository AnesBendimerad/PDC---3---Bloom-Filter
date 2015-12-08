// PDC3_BloomFilter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <stdio.h>
#include "BloomFilterServer.h"

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
	return 0;
}