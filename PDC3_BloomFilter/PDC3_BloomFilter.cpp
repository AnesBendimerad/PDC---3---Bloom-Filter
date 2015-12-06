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

using namespace std;

int main() {
	DataBaseConfiguration config;
	config.contactPoints = "127.0.0.1";
	config.keySpace = "documentDataBase";
	config.table = "documentTable";

	DataBaseGenerator* generator = new DataBaseGenerator(config,1000);
	generator->generate();
	delete generator;
	system("Pause");
}