#include "ioManager.h"

IOManager::IOManager()
{
	stdinHandle = GetStdHandle(STD_INPUT_HANDLE);
	if (stdinHandle == INVALID_HANDLE_VALUE)
		throw std::runtime_error("Failed: GetStdHandle: stdin");
	
	if (!GetConsoleMode(stdinHandle, &terminalModeOrigin))
		throw std::runtime_error("Failed: GetConsoleMode");
	
	terminalMode = ENABLE_WINDOW_INPUT;
	
}

IOManager::~IOManager()
{
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

KEY_EVENT_RECORD IOManager::getKey()
{
	DWORD	cNumRead;
	INPUT_RECORD	input_buffer[1];

	if (!ReadConsoleInput(stdinHandle, input_buffer, 1, &cNumRead))
		throw std::runtime_error("Failed: ReadConsoleInput");
	if (input_buffer[0].EventType == KEY_EVENT)
		return input_buffer[0].Event.KeyEvent;
	else
		return KEY_EVENT_RECORD();
	
}

void IOManager::clear()
{
	system("cls");
}

void IOManager::gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void IOManager::keyEvent(KEY_EVENT_RECORD key)
{
	if (key.bKeyDown)
	{
		IOManager::clear();
		IOManager::gotoxy(0, 0);
		std::cout << YELLOW("keyEvent") << std::endl;
		std::cout << key.dwControlKeyState << std::endl;
		std::cout << key.wRepeatCount << std::endl;
		std::cout << key.wVirtualKeyCode << std::endl;
		std::cout << key.wVirtualScanCode << std::endl;
	}
}
