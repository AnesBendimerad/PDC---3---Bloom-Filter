#pragma once
#include <winsock2.h>
#include <iostream>
#include <string>

#define BUF_SIZE 1024
#define STOP_QUERY "stop"

using namespace std;

class Server
{
public:
	Server(unsigned int port);
	~Server();
	void start();
	void stop();
private:
	unsigned int port;
	SOCKET sock;
	int init_connection(void);
	int read_client(SOCKET sock, char *buffer);
	void write_client(SOCKET sock, const char *buffer);
protected:
	virtual void init() = 0;
	virtual void executeRequest(string query) = 0;
	virtual void destroy() = 0;
};