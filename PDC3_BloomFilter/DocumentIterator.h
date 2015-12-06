#pragma once
#include <cassandra.h>
#include "Document.h"
class DocumentIterator {
private:
	const CassResult* result;
	CassIterator* rows;
	string getColumnValue(const CassRow* row, string columnName);
public:
	DocumentIterator(const CassResult* result);
	Document * getNextDocument();
	~DocumentIterator();
};