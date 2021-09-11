#include "server.h"
#include "client.h"

void Server::setup()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		throw std::runtime_error("fail: WSAStartup");
	serverSocket = socket(PF_INET, SOCK_STREAM, 0);
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(4242);

	if (bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
		throw std::runtime_error("fail: bind");

	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::runtime_error("fail: listen");
	std::cout << "Server Start!" << std::endl;
}

void Server::run()
{
	for (;;)
	{
		int len = sizeof(SOCKADDR_IN);
		SOCKADDR_IN client;
		SOCKET clientSock = accept(serverSocket, (SOCKADDR*)&client, &len);
		Client c(clientSock, client);
		clients.push_back(c);
		clientThreads.push_back(std::thread(clientThread, c, &clients));
	}
}

void Server::waitThreads()
{
	for (auto it = clientThreads.begin(); it != clientThreads.end(); ++it)
		it->join();
	closesocket(serverSocket);
}
