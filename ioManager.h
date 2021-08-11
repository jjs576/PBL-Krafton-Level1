#pragma once
#include "header.h"

class IOManager
{
private:
	DWORD	terminalMode;
	DWORD	terminalModeOrigin;
	HANDLE	stdinHandle;
	std::queue<KEY_EVENT_RECORD>	input_queue;
public:
	bool	is_end;

public:
	enum TermMode
	{
		game,
		origin,
	};
	IOManager();
	~IOManager();

	void	setTerm(TermMode);
	void	pushKey(KEY_EVENT_RECORD key);
	KEY_EVENT_RECORD	getKey();
	void	clear();
	void	gotoxy(int, int);
};