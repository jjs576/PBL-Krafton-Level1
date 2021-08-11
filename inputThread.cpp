#include "inputThread.h"

void inputThreadRun(IOManager* io, std::mutex* m)
{
	DWORD	cNumRead;
	INPUT_RECORD	inputBuffer[1];

	for (;;)
	{
		if (io->isEnd)
			break;
		
		if (!ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), inputBuffer, 1, &cNumRead))
			throw std::runtime_error("Failed: ReadConsoleInput");
		if (inputBuffer[0].EventType == KEY_EVENT)
		{
			m->lock();
			io->pushKey(inputBuffer[0].Event.KeyEvent);
			m->unlock();
		}
	}
}
