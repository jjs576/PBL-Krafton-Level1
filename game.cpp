#include "game.h"

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
	KEY_EVENT_RECORD input;

	for (;;)
	{
		input = io.getKey();
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
		}
		render();
	}
}

void Game::render()
{
	io.clear();
	io.gotoxy(player.getX() * 2, player.getY());
	std::cout << "бс";
}
