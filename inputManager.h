#pragma once
#include "header.h"


class InputManager
{
private:
	static InputManager* instance;
	
	std::queue<KEY_EVENT_RECORD>	inputQueue;
	std::set<std::tuple<BOOL, WORD> > inputSet;

public:
	InputManager();

	static InputManager& getInstance();

	KEY_EVENT_RECORD	getKey();
	void	pushKey(KEY_EVENT_RECORD key);

	void	insertInputSet(KEY_EVENT_RECORD);
	void	clearInputSet();
	bool	findKey(WORD, BOOL);

};