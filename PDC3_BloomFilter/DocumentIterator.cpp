#include "stdafx.h"
#include "DocumentIterator.h"

DocumentIterator::DocumentIterator(const CassResult * result)
{
	DocumentIterator::result = result;
	if (result != nullptr) {
		rows = cass_iterator_from_result(result);
	}
}

string DocumentIterator::getColumnValue(const CassRow * row, string columnName)
{
	const CassValue* value = cass_row_get_column_by_name(row, columnName.c_str());
	const char* keyspace;
	size_t keyspace_length;
	cass_value_get_string(value, &keyspace, &keyspace_length);
	char *resultAsChar = (char*)malloc(sizeof(char)*(keyspace_length + 1));
	for (unsigned int i = 0; i < keyspace_length; i++) {
		resultAsChar[i] = keyspace[i];
	}
	resultAsChar[keyspace_length] = '\0';
	string resultAsString;
	resultAsString.assign(resultAsChar, resultAsChar + keyspace_length);
	return resultAsString;
}

Document * DocumentIterator::getNextDocument()
{
	if (cass_iterator_next(rows)) {
		const CassRow* row = cass_iterator_get_row(rows);
		Document * document = new Document;
		document->documentNumber = getColumnValue(row, DOCUMENT_NUMBER);
		document->documentType = getColumnValue(row, DOCUMENT_TYPE);
		document->countryCode = getColumnValue(row, COUNTRY_CODE);
		return document;
	}
	else {
		return nullptr;
	}
}

DocumentIterator::~DocumentIterator()
{
	cass_result_free(result);
	cass_iterator_free(rows);
}
