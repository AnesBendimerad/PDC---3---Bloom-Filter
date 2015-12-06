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

using namespace std;

int main() {
	unsigned int m = 10010;
	unsigned int k = 5;
	IHasher* hasher = new MurmurHasher();
	BloomFilter* bf = new BloomFilter(m, k, hasher);

	string key1 = "aymen";
	string key2 = "abi";
	bf->addKey(key1);

	if (bf->readKey(key2))
	{
		cout << key2 << " exists in the set (normally), with a risk of ERROR !" << endl;
	}
	else
	{
		cout << key2 << " key doesn't exists in the set (certainly)" << endl;
	}
	system("Pause");
}