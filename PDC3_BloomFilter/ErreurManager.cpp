#include "stdafx.h"
#include "ErreurManager.h"

static vector<string> errorTable = { "Incorrect syntax","Initiation of the Winsock DLL failed",
									 "Invalid socket","Unable to associate the address with the socket", 
                                     "Cannot listen for an incoming connection","Permit the incoming connection failed"
                                     "Keyspace does not exist","Unconfigured table",
                                     "Creating index failed"};

string ErreurManager::getError(unsigned int i)
{
	if (i >= 0 && i < errorTable.size())
		return errorTable.at(i);
	return "Unknown Error";
}
