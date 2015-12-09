#pragma once
#include <cassandra.h>
#include <string>
using namespace std;
string getColumnValue(const CassRow * row, string columnName);