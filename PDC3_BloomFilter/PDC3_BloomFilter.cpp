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
#include "DataBaseConfiguration.h"
#include "DataBaseHandler.h"
using namespace std;

int main() {
	DataBaseConfiguration dataBaseConfiguration;
	dataBaseConfiguration.contactPoints = "127.0.0.1";
	dataBaseConfiguration.keySpace = "documentDataBase";
	dataBaseConfiguration.table = "documentTable";
	DataBaseHandler *dataBaseHandler = new DataBaseHandler(dataBaseConfiguration);
	/*Document d1, d2, d3;
	d1.documentNumber = "1";
	d1.documentType = "11";
	d1.countryCode = "111";
	d2.documentNumber = "2";
	d2.documentType = "22";
	d2.countryCode = "222";
	d3.documentNumber = "3";
	d3.documentType = "33";
	d3.countryCode = "333";
	dataBaseHandler->addDocument(&d1);
	dataBaseHandler->addDocument(&d2);
	dataBaseHandler->addDocument(&d3);
	delete dataBaseHandler;*/
	/*Document *d1 = dataBaseHandler->getDocumentByNumber("4");
	if (d1 != nullptr) {
		cout << "document number :";
		cout << d1->documentNumber<<endl;
		cout << "document type :";
		cout << d1->documentType << endl;
		cout << "country code :";
		cout << d1->countryCode<<endl;
	}
	else {
		cout << "pb" << endl;
	}*/
	DocumentIterator * documentIterator = dataBaseHandler->getDocumentIterator();
	Document * document;
	while ((document = documentIterator->getNextDocument()) != nullptr) {
		cout << "document number :";
		cout << document->documentNumber << endl;
		cout << "document type :";
		cout << document->documentType << endl;
		cout << "country code :";
		cout << document->countryCode << endl;
	}
	system("pause");
}