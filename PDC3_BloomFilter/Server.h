#pragma once
#include <winsock2.h>
#include <iostream>
#include <string>

using namespace std;

#define STOP_COMMAND "stop"
#define DEFAULT_PORT MAXUINT16
#define BUF_SIZE 1024

class Server
{
public:
	Server();
	~Server();
	void start();
	void stop();
private:
	SOCKET sock;
	int Server::init_connection();
	int read_client(SOCKET sock, char *buffer);
	void write_client(SOCKET sock, const char *buffer);
protected:
	unsigned int port = DEFAULT_PORT;
	virtual void init() = 0;
	virtual string executeRequest(string query) = 0;
	virtual void destroy() = 0;
};