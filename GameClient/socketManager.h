#pragma once
#include "header.h"

constexpr auto SERVER_IP = "127.0.0.1";
constexpr auto PORT = 4242;
constexpr auto BUF_SIZE = 1024;

class SocketManager
{
private:
	static SocketManager* instance;
	WSADATA	wsaData;
	SOCKET sock;
	SOCKADDR_IN addr = {};
	bool connected;
	std::queue<std::string> recvQueue;
	std::queue<std::string> sendQueue;

public:
	SocketManager();
	~SocketManager();
	static SocketManager& getInstance();
	void setup();
	void connectServer();
	void closeSocket();
	void pushRecvQueue(std::string);
	std::string popRecvQueue();
	void pushSendQueue(std::string);
	std::string popSendQueue();
	void recvMsg();
	void sendMsg();

	bool isConnected();
};