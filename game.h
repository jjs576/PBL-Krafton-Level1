#pragma once

#include "header.h"
#include "ioManager.h"
#include "player.h"

class Game
{
private:
	IOManager	io;
	Player		player;
public:
	static const int boardSizeX = 10;
	static const int boardSizeY = 10;
public:
	Game();
	~Game();
	void run();
	void render();
	void renderObject(int, int, char);
};