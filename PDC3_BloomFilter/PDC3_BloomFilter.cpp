// PDC3_BloomFilter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string>
#include <cassandra.h>
#include <conio.h>
#include <stdio.h>
#include "BloomFilter.h"
#include "IHasher.h"
#include "MurmurHasher.h"
#include "DataBaseGenerator.h"
#include "BloomFilterBasedDBController.h"
#include "BloomFilterServer.h"
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

int main() {
	BloomFilterServer bloomFilterServer("configFile.txt");
	bloomFilterServer.start();
	system("pause");
	return 0;
}