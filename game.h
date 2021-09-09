#pragma once

#include "header.h"
#include "consoleManager.h"
#include "player.h"
#include "inputManager.h"
#include "sceneManager.h"
#include "fileManager.h"
#include "socketManager.h"
#include "threads.h"
#include "scene.h"

class Game
{
private:
	ConsoleManager	consoleManager;
	std::vector<KEY_EVENT_RECORD> inputVector;
	clock_t		startTick;
	clock_t		curTick;
	InputManager*	inputManager;
	SceneManager*	sceneManager;
	FileManager*	fileManager;
	SocketManager*	socketManager;

	std::mutex	inputMutex;
	std::mutex	socketMutex;


private:
	void update();
	void render();
	void renderObject(int, int, std::string);
	void timer(int);

public:
	const static int boardSizeX = 20;
	const static int boardSizeY = 20;
	Game();
	~Game();
	void run();
	
};