#include "sceneManager.h"

SceneManager* SceneManager::instance = 0;


SceneManager::SceneManager()
{
	curScene = new MenuScene();
	curSceneId = SceneId::Menu;
}

SceneManager& SceneManager::getInstance()
{
	if (instance == NULL)
		instance = new SceneManager();
	return *instance;
}

void SceneManager::start()
{
	curScene->start();
}

void SceneManager::update()
{
	if (curScene)
		curScene->update();
}

void SceneManager::pushRenderQueue(int x, int y, std::string c)
{
	renderQueue.push(std::make_tuple(x, y, c));
}

std::tuple<int, int, std::string> SceneManager::popRenderQueue()
{
	if (renderQueue.empty())
		return std::make_tuple(-1, -1, ":empty");
	std::tuple<int, int, std::string> object = renderQueue.front();
	renderQueue.pop();
	return object;
}

void SceneManager::changeScene(SceneId id)
{
	delete curScene;
	curSceneId = id;
	switch (id)
	{
	case SceneId::Menu:
		curScene = new MenuScene();
		break;
	case SceneId::Play:
		curScene = new PlayScene();
		break;
	case SceneId::Status:
		curScene = new StatusScene();
		break;
	default:
		curScene = 0;
	}
	pushRenderQueue(0, 0, ":clear");
	if (curScene)
		curScene->start();
}

SceneManager::SceneId SceneManager::getCurSceneId()
{
	return curSceneId;
}
