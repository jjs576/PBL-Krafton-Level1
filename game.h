#pragma once

#include "header.h"
#include "ioManager.h"
#include "player.h"
#include "keyManager.h"

class Game
{
private:
	IOManager	io;
	Player		player;
	std::vector<KEY_EVENT_RECORD> inputVector;
	int			lastInputTick;
	int			curTick;
	KeyManager	keyManager;
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
	void inputControl(KEY_EVENT_RECORD);
	void comboCheck();
};