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
	KEY_EVENT_RECORD	input;
	std::mutex	m;
	std::thread	ioThread(inputThreadRun, &io, &m);
	ioThread.detach();
	render();
	int tick = 0;
	while (!io.is_end)
	{
		timer(33);
		m.lock();
		input = io.getKey();
		m.unlock();
		if (input.bKeyDown)
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
		io.gotoxy(0, 21);
		std::cout << "                                                                               ";
		io.gotoxy(0, 21);
		m.lock();
		std::cout << "key :";
		for (auto it = io.input_list.begin(); it != io.input_list.end(); ++it)
			std::cout << "(" << it->wVirtualKeyCode << ","<< it->bKeyDown << ") ";
		m.unlock();
		io.gotoxy(0, 22);
		std::cout << "Tick :" << ++tick;
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

void Game::timer(int time)
{
	clock_t start = clock();
	for (;;)
	{
		clock_t end = clock();
		if (end - start >= time)
			break;
	}

		
}
