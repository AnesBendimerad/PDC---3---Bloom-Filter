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
		perror("WSAStartup failed !");
		exit(errno);
	}
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sin = { 0 };

	if (sock == INVALID_SOCKET)
	{
		perror("socket()");
		exit(errno);
	}

	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_port = htons(this->port);
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
	
	this->sock = this->init_connection(); //initilize the connection using the port
	char buffer[BUF_SIZE];
	SOCKET csock;
	SOCKADDR_IN csin = { 0 };
	int sinsize = sizeof csin;

	init(); // to implement

	//cout << "waiting client ... " << endl;
	
	cout << "listening to port " << port << " ... " << endl;
	bool end = false;
	string response = "";
	while (!end)
	{
		csock = accept(sock, (SOCKADDR *)&csin, &sinsize);
		if (csock == SOCKET_ERROR)
		{
			perror("Acceptation phase failed");
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
	send(sock, buffer, strlen(buffer), 0);
}