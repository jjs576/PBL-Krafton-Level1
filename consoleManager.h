#pragma once
#include "header.h"

class ConsoleManager
{
private:
	DWORD	terminalMode;
	DWORD	terminalModeOrigin;
	HANDLE	stdinHandle;
public:
	enum class TermMode
	{
		game,
		origin,
	};
	ConsoleManager();
	~ConsoleManager();

	void		setTerm(TermMode);
	static void	clear();
	static void	gotoxy(int, int);
};