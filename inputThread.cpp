#include "inputThread.h"

void inputThreadRun(IOManager* io, std::mutex* m)
{
	DWORD	cNumRead;
	INPUT_RECORD	input_buffer[1];

	for (;;)
	{
		if (io->is_end)
			break;
		
		if (!ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), input_buffer, 1, &cNumRead))
			throw std::runtime_error("Failed: ReadConsoleInput");
		if (input_buffer[0].EventType == KEY_EVENT)
		{
			m->lock();
			io->pushKey(input_buffer[0].Event.KeyEvent);
			m->unlock();
		}
	}
}
