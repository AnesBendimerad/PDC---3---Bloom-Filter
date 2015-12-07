#pragma once
#include "Server.h"
class BloomFilterServer :
	public Server
{
public:
	BloomFilterServer(unsigned int port);
	~BloomFilterServer();
	virtual void init();
	virtual void executeRequest(string query);
	virtual void destroy();
};

