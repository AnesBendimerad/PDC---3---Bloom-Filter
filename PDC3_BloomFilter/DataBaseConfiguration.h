#pragma once
#include <string>
using namespace std;

typedef struct DataBaseConfiguration {
	string keySpace;
	string table;
	string contactPoints;   // example : "127.0.0.1"
} DataBaseConfiguration;