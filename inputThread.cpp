#include "inputThread.h"

void inputThreadRun(IOManager* io)
{
	for (;;)
	{
		if (io->is_end)
			break;
		io->inputKey();
	}
}
