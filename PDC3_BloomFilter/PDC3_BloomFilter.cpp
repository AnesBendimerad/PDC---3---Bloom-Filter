// PDC3_BloomFilter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cassandra.h>
#include <conio.h>
#include <stdio.h>
#include "BitWiseArray.h"

using namespace std;

int main() {
	/* Setup and connect to cluster */
	CassCluster* cluster = cass_cluster_new();
	CassSession* session = cass_session_new();

	/* Add contact points */
	cass_cluster_set_contact_points(cluster, "127.0.0.1");

	/* Provide the cluster object as configuration to connect the session */
	CassFuture* connect_future = cass_session_connect(session, cluster);

	/* This operation will block until the result is ready */
	CassError rc = cass_future_error_code(connect_future);

	printf("Connect result: %s\n", cass_error_desc(rc));

	/* Run queries... */

	/* Build statement and execute query */
	CassStatement* statement
		= cass_statement_new("SELECT *"
			"FROM hr2.emp2 WHERE  empid  = '1'", 0);

	CassFuture* result_future = cass_session_execute(session, statement);

	if (cass_future_error_code(result_future) == CASS_OK) {
		/* Retrieve result set and iterate over the rows */
		const CassResult* result = cass_future_get_result(result_future);
		CassIterator* rows = cass_iterator_from_result(result);

		while (cass_iterator_next(rows)) {
			const CassRow* row = cass_iterator_get_row(rows);
			const CassValue* value = cass_row_get_column_by_name(row, "emp_first");

			const char* keyspace;
			size_t keyspace_length;
			cass_value_get_string(value, &keyspace, &keyspace_length);
			cout << keyspace << endl;
			//printf("Name: '%.*s'\n", (int)keyspace_length, keyspace);
		}

		cass_result_free(result);
		cass_iterator_free(rows);
	}
	else {
		/* Handle error */
		const char* message;
		size_t message_length;
		cass_future_error_message(result_future, &message, &message_length);
		fprintf(stderr, "Unable to run query: '%.*s'\n",
			(int)message_length, message);
	}

	cass_statement_free(statement);
	cass_future_free(connect_future);
	cass_session_free(session);
	cass_cluster_free(cluster);
	system("pause");
	return 0;

}