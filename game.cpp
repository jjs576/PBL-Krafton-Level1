#include "game.h"

Game::Game()
{
	consoleManager.setTerm(ConsoleManager::TermMode::game);
	startTick = clock();
	curTick = 0;
	inputManager = &InputManager::getInstance();
	sceneManager = &SceneManager::getInstance();
	fileManager = &FileManager::getInstance();
	socketManager = &SocketManager::getInstance();
}

Game::~Game()
{
	consoleManager.setTerm(ConsoleManager::TermMode::origin);
	delete inputManager;
	delete fileManager;
	delete socketManager;
}

void Game::run()
{
	std::thread	inputThread(inputThreadFunc, &inputMutex);
	std::thread socketThread(socketThreadFunc, &socketMutex);
	
	inputThread.detach();
	socketThread.detach();

	sceneManager->start();
	for (;;)
	{
		if (sceneManager->getCurSceneId() == SceneManager::SceneId::None)
			break;
		timer(33); // 30fps
		curTick = clock() - startTick;
		update();
		render();
	}
	renderObject(0, 0, ":clear");
}

void Game::update()
{
	sceneManager->update();
}

void Game::render()
{
	for (;;)
	{
		std::tuple<int, int, std::string> object = sceneManager->popRenderQueue();
		if (std::get<2>(object) == ":empty")
			break;
		renderObject(std::get<0>(object), std::get<1>(object), std::get<2>(object));
	}
}

void Game::renderObject(int x, int y, std::string c)
{
	if (c == ":clear")
		ConsoleManager::clear();
	else
	{
		ConsoleManager::gotoxy(x * 2, y);
		std::cout << c;
	}
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

