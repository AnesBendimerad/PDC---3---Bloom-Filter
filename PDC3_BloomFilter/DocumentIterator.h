#pragma once
#include <cassandra.h>
#include "CassandraAdditionalFunctions.h"
#include "Document.h"
class DocumentIterator {
private:
	const CassResult* result;
	CassStatement* statement;
	CassSession* session;
	CassIterator* rows;
public:
	DocumentIterator(CassSession* session, CassStatement* statement, const CassResult* result);
	Document * getNextDocument();
	//	size_t getSize();
	~DocumentIterator();
};