#include "consoleManager.h"

ConsoleManager::ConsoleManager()
{
	stdinHandle = GetStdHandle(STD_INPUT_HANDLE);
	if (stdinHandle == INVALID_HANDLE_VALUE)
		throw std::runtime_error("Failed: GetStdHandle");
	
	if (!GetConsoleMode(stdinHandle, &terminalModeOrigin))
		throw std::runtime_error("Failed: GetConsoleMode");
	
	terminalMode = ENABLE_WINDOW_INPUT;
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}

ConsoleManager::~ConsoleManager()
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = true;
	SetConsoleCursorInfo(out, &cursorInfo);
}

void ConsoleManager::setTerm(TermMode mode)
{
	switch (mode)
	{
	case TermMode::game:
		if (!SetConsoleMode(stdinHandle, terminalMode))
			throw std::runtime_error("Failed: SetConsoleMode");
	case TermMode::origin:
		if (!SetConsoleMode(stdinHandle, terminalModeOrigin))
			throw std::runtime_error("Failed: SetConsoleMode");
	}
}

void ConsoleManager::clear()
{
	system("cls");
}

void ConsoleManager::gotoxy(int x, int y)
{
	COORD pos = { (short)x, (short)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

