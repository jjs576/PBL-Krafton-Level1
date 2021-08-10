#pragma once
#include "header.h"

class IOManager
{
private:
	DWORD	terminalMode;
	DWORD	terminalModeOrigin;
	HANDLE	stdinHandle;

public:
	enum TermMode
	{
		game,
		origin,
	};
	IOManager();
	~IOManager();
	void	setTerm(TermMode);
	KEY_EVENT_RECORD	getKey();
	void	clear();
	void	gotoxy(int, int);
	void	keyEvent(KEY_EVENT_RECORD);
};