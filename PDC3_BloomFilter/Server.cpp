#include "stdafx.h"
#include "Server.h"


Server::Server(unsigned int port)
{
	this->port = port;
	this->sock = init_connection();
	if (sock == INVALID_SOCKET)
	{
		perror("socket()");
		exit(errno);
	}
}


Server::~Server()
{
}

int Server::init_connection(void)
{
	WSADATA wsa;
	int err = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (err < 0)
	{
		cout << "WSAStartup failed !" << endl;
		return INVALID_SOCKET;
	}


	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sin = { 0 };

	if (sock == INVALID_SOCKET)
	{
		perror("socket()");
		exit(errno);
	}

	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_port = htons(port);
	sin.sin_family = AF_INET;

	if (bind(sock, (SOCKADDR *)&sin, sizeof sin) == SOCKET_ERROR)
	{
		perror("bind()");
		exit(errno);
	}

	if (listen(sock, 5) == SOCKET_ERROR)
	{
		perror("listen()");
		exit(errno);
	}
	cout << "listening to port" << port << endl;
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
	char buffer[BUF_SIZE];
	SOCKET csock;
	SOCKADDR_IN csin = { 0 };
	int sinsize = sizeof csin;

	csock = accept(sock, (SOCKADDR *)&csin, &sinsize);
	init(); // to implement

	if (csock == SOCKET_ERROR)
	{
		perror("accept()");
	}

	bool end = false;
	while (!end)
	{
		if (read_client(csock, buffer) == -1)
		{
			continue;
		}
		else
		{
			if (strcmp(buffer, STOP_QUERY) == 0)
			{
				end = true;
			}
			else
			{
				executeRequest(buffer); // to implement
				write_client(csock, "received");
			}
		}
	}



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
	if (send(sock, buffer, strlen(buffer), 0) < 0)
	{
		exit(errno);
	}
}