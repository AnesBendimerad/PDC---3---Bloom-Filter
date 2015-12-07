#include "stdafx.h"
#include "BloomFilterServer.h"


BloomFilterServer::BloomFilterServer(unsigned int port) : Server(port)
{
	// do some tasks to initialize the bloom filter parameters
}


BloomFilterServer::~BloomFilterServer()
{

}

void BloomFilterServer::init()
{
	// do some tasks to construct the bloom filter
}

void BloomFilterServer::executeRequest(string query)
{
	cout << query << endl;
}

void BloomFilterServer::destroy()
{
	// do some tasks to destroy the bloom filter parameters
}