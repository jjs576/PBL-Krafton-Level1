#include "socketManager.h"

SocketManager* SocketManager::instance = 0;


SocketManager::SocketManager()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		throw std::runtime_error("fail: WSAStartup");
	connected = false;
}

SocketManager::~SocketManager()
{
	WSACleanup();
}

SocketManager& SocketManager::getInstance()
{
	if (instance == NULL)
		instance = new SocketManager();
	return *instance;
}

void SocketManager::setup()
{
	sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	addr.sin_port = htons(PORT);
}

void SocketManager::connectServer()
{
	if (connect(sock, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		throw std::runtime_error("fail: connect Server");
	}
	else
		connected = true;
}

void SocketManager::closeSocket()
{
	closesocket(sock);
	connected = false;
}

void SocketManager::pushRecvQueue(std::string data)
{
	recvQueue.push(data);
}

std::string SocketManager::popRecvQueue()
{
	if (recvQueue.empty())
		return "";
	std::string data = recvQueue.front();
	recvQueue.pop();
	return data;
}

void SocketManager::pushSendQueue(std::string data)
{
	sendQueue.push(data);
}

std::string SocketManager::popSendQueue()
{
	if (sendQueue.empty())
		return "";
	std::string data = sendQueue.front();
	sendQueue.pop();
	return data;
}

bool SocketManager::isConnected()
{
	return connected;
}

void SocketManager::recvMsg()
{
	char c[BUF_SIZE] = {};
	if (recv(sock, c, BUF_SIZE, 0) <= 0)
	{
		pushRecvQueue(":SOCKET_ERROR");
		connected = false;
	}
	else
		pushRecvQueue(std::string(c));
}

void SocketManager::sendMsg()
{
	char c[BUF_SIZE] = {};
	std::string buf = popSendQueue();
	if (buf == "")
		return;
	std::strcpy(c, buf.c_str());
	if (send(sock, c, BUF_SIZE, 0) <= 0)
		connected = false;
}