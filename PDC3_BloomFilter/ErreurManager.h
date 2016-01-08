#pragma once
#include <string>
#include <vector>

#define INCORRECT_SYNTAX_ERROR 0
#define WINSOCKDLL_INIT_ERROR 1
#define INVALID_SOCKET_ERROR 2
#define BIND_SOCKET_ERROR 3
#define LISTEN_SOCKET_ERROR 4
#define ACCEPT_SOCKET_ERROR 5
#define DB_KEYSPACE_ERROR 6
#define DB_TABLE_ERROR 7
#define DB_INDEX_ERROR 8

using namespace std;

class ErreurManager
{
public:
	static string getError(unsigned int);
private:
};

