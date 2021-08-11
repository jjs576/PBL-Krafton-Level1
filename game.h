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
	static const int boardSizeX = 20;
	static const int boardSizeY = 20;
public:
	Game();
	~Game();
	void run();
	void render();
	void renderObject(int, int, std::string);
	void timer(int);
};