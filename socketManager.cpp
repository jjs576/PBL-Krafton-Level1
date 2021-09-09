#include "socketManager.h"

SocketManager* SocketManager::instance = 0;


SocketManager& SocketManager::getInstance()
{
	if (instance == NULL)
		instance = new SocketManager();
	return *instance;
}

