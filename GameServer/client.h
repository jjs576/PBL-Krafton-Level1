#pragma once
#include "header.h"

class Client
{
public:
	SOCKET socket;
	SOCKADDR_IN socketAddr;
	Client(SOCKET, SOCKADDR_IN);
};

void clientThread(Client, std::vector<Client>*);