#include "ioManager.h"

IOManager::IOManager()
{
	isEnd = false;
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

IOManager::~IOManager()
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = true;
	SetConsoleCursorInfo(out, &cursorInfo);
}

void IOManager::setTerm(TermMode mode)
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

void IOManager::pushKey(KEY_EVENT_RECORD key)
{
	inputQueue.push(key);
}

KEY_EVENT_RECORD IOManager::getKey()
{
	KEY_EVENT_RECORD input = { 0, };
	if (!inputQueue.empty())
	{
		input = inputQueue.front();
		inputQueue.pop();
	}
	return input;
}

void IOManager::clear()
{
	system("cls");
}

void IOManager::gotoxy(int x, int y)
{
	COORD pos = { (short)x, (short)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
