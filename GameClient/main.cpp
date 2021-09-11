#include "game.h"

int main()
{
	try
	{
		Game game;
		game.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << RED(e.what()) << std::endl;
	}
	return 0;
}