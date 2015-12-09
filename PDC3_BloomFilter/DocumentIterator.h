#pragma once
#include <cassandra.h>
#include "CassandraAdditionalFunctions.h"
#include "Document.h"
class DocumentIterator {
private:
	const CassResult* result;
	CassIterator* rows;
public:
	DocumentIterator(const CassResult* result);
	Document * getNextDocument();
	size_t getSize();
	~DocumentIterator();
};