#include "stdafx.h"
#include "Server.h"


Server::Server()
{
}


Server::~Server()
{

}

int Server::init_connection()
{
	WSADATA wsa;
	int err = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (err < 0)
	{
		throw new exception(ErreurManager::getError(WINSOCKDLL_INIT_ERROR).c_str());
		exit(errno);
	}
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sin = { 0 };

	if (sock == INVALID_SOCKET)
	{
		throw new exception(ErreurManager::getError(INVALID_SOCKET_ERROR).c_str());
		exit(errno);
	}

	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_port = htons(this->port);
	sin.sin_family = AF_INET;

	if (bind(sock, (SOCKADDR *)&sin, sizeof sin) == SOCKET_ERROR)
	{
		throw new exception(ErreurManager::getError(BIND_SOCKET_ERROR).c_str());
		exit(errno);
	}

	if (listen(sock, 5) == SOCKET_ERROR)
	{
		throw new exception(ErreurManager::getError(LISTEN_SOCKET_ERROR).c_str());
		exit(errno);
	}
	return sock;
}

void Server::stop()
{
	destroy(); // to implement
	closesocket(sock);
	WSACleanup();
}

void Server::start()
{
	try {
		this->sock = this->init_connection(); //initialize the connection using the port
	}
	catch (const exception *e) {
		cerr << "An exception has occured: " << e->what() << endl;
		return;
	}

	char buffer[BUF_SIZE];
	SOCKET csock;
	SOCKADDR_IN csin = { 0 };
	int sinsize = sizeof csin;

	init(); // to implement

	cout << "listening to port " << port << " ... " << endl;
	bool end = false;
	string response = "";
	while (!end)
	{
		csock = accept(sock, (SOCKADDR *)&csin, &sinsize);
		if (csock == SOCKET_ERROR)
		{
			throw new exception(ErreurManager::getError(ACCEPT_SOCKET_ERROR).c_str());
		}
		else {
			if (read_client(csock, buffer) == -1)
			{
				continue;
			}
			else
			{
				if (strcmp(buffer, STOP_COMMAND) == 0)
				{
					end = true;
				}
				else
				{
					response = executeRequest(buffer); // to implement
					write_client(csock, response.c_str());
				}
			}
		}
	}
	cout << "Stopping service ..." << endl;
	this->stop();
	cout << "Service stoped" << endl;
	cout << "--------------------------------" << endl;
}


int Server::read_client(SOCKET sock, char *buffer)
{
	int n = 0;
	if ((n = recv(sock, buffer, BUF_SIZE - 1, 0)) < 0)
	{
		n = 0;
	}
	buffer[n] = 0;
	return n;
}

void Server::write_client(SOCKET sock, const char *buffer)
{
	int nDataToSend = strlen(buffer);
	int nSentData = 0;
	while (nDataToSend > nSentData) {
		int nData = send(sock, buffer + nSentData, nDataToSend - nSentData, 0);
		if (nData > 0)
			nSentData += nData;
		else {
			//error
			break;
		}
	}
}