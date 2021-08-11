#pragma once
#include "header.h"

class IOManager
{
private:
	DWORD	terminalMode;
	DWORD	terminalModeOrigin;
	HANDLE	stdinHandle;
public:

	std::list<KEY_EVENT_RECORD>	input_list;
	bool	is_end;

public:
	enum class TermMode
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