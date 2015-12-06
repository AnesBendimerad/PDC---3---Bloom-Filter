#pragma once
#include <cassandra.h>
#include "Document.h"
class DocumentIterator {
private:
	CassResult* result;
	CassIterator* rows;
public:
	DocumentIterator(const CassResult* result);
	Document * getNextDocument();
	~DocumentIterator();
};