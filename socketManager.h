#pragma once
#include "header.h"

class SocketManager
{
private:
	static SocketManager* instance;

public:
	static SocketManager& getInstance();
};