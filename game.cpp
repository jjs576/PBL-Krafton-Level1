#include "game.h"
#include "inputThread.h"

Game::Game()
{
	io.setTerm(io.game);
}

Game::~Game()
{
	io.setTerm(io.origin);
}

void Game::run()
{
	std::thread	ioThread(inputThreadRun, &io);
	ioThread.detach();
	render();

	while (!io.is_end)
	{
		KEY_EVENT_RECORD	input = io.getKey();
		if (input.dwControlKeyState == 0)
			continue;
		if (!input.bKeyDown)
			continue;
		switch (input.wVirtualKeyCode)
		{
		case VK_UP:
			player.moveUp();
			break;
		case VK_DOWN:
			player.moveDown();
			break;
		case VK_LEFT:
			player.moveLeft();
			break;
		case VK_RIGHT:
			player.moveRight();
			break;
		case VK_SPACE:
			player.changeColor();
			break;
		case VK_ESCAPE:
			io.is_end = true;
			break;
		}
		render();
	}
}

void Game::render()
{
	renderObject(player.getOldX(), player.getOldY(), "  ");
	renderObject(player.getX(), player.getY(), player.getCharacter());
}

void Game::renderObject(int x, int y, std::string c)
{
	io.gotoxy(x * 2, y);
	std::cout << c;
}
