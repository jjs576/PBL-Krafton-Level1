#include "header.h"
#include "server.h"


int main()
{
	Server server;
	try {
		server.setup();
		server.run();
		server.waitThreads();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	WSACleanup();
	return 0;
}
