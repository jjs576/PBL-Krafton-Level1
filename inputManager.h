#pragma once
#include "header.h"


class InputManager
{
private:
	static InputManager* instance;
	
	std::queue<KEY_EVENT_RECORD>	inputQueue;

public:
	InputManager();

	static InputManager& getInstance();

	KEY_EVENT_RECORD	getKey();
	void	pushKey(KEY_EVENT_RECORD key);
};