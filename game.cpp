#include "game.h"
#include "inputThread.h"

Game::Game()
{
	io.setTerm(IOManager::TermMode::game);
}

Game::~Game()
{
	io.setTerm(IOManager::TermMode::origin);
}

void Game::run()
{
	std::mutex	m;
	std::thread	ioThread(inputThreadRun, &io, &m);
	ioThread.detach();
	render();
	KEY_EVENT_RECORD	input;
	while (!io.is_end)
	{
		m.lock();
		input = io.getKey();
		m.unlock();
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
	io.gotoxy(0, 0);
	io.clear();
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
