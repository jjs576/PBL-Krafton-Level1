#pragma once
#include "header.h"
#include "client.h"

class Server
{
private:
	WSADATA wsaData;
	SOCKET serverSocket;
	SOCKADDR_IN serverAddr;
	std::vector<std::thread> clientThreads;
	std::vector<Client>	clients;
public:
	void setup();
	void run();
	void waitThreads();
};