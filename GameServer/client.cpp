#include "client.h"

Client::Client(SOCKET _socket, SOCKADDR_IN _socketAddr)
{
	socket = _socket;
	socketAddr = _socketAddr;
	
}

void clientThread(Client client, std::vector<Client>* allClients)
{
	std::cout << inet_ntoa(client.socketAddr.sin_addr) << " connected" << std::endl;

	for (;;)
	{
		char buf[1024];
		if (recv(client.socket, buf, 1024, 0) <= 0)
			break;
		if (std::strcmp(buf, ":close") == 0)
			break;
		for (auto it = allClients->begin(); it != allClients->end(); ++it)
			if (client.socket != it->socket)
				send(it->socket, buf, sizeof(buf), 0);
		std::cout << buf << std::endl;
	}
	std::cout << inet_ntoa(client.socketAddr.sin_addr) << " disconnected" << std::endl;
	closesocket(client.socket);
}
