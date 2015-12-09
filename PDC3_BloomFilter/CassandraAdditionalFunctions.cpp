#include "stdafx.h"
#include "CassandraAdditionalFunctions.h"
string getColumnValue(const CassRow * row, string columnName)
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
