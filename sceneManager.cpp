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
	getInput();
	if (curScene)
		curScene->update();
}

void SceneManager::pushRenderQueue(std::tuple<int, int, std::string> object)
{
	renderQueue.push(object);
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
}

SceneManager::SceneId SceneManager::getCurSceneId()
{
	return curSceneId;
}

void SceneManager::getInput()
{
	for (;;)
	{
		KEY_EVENT_RECORD rawInput = InputManager::getInstance().getKey();
		if (rawInput.wVirtualKeyCode == 0)
			break;
		input.insert(std::make_tuple(rawInput.wVirtualKeyCode, rawInput.bKeyDown));
	}
}

bool SceneManager::findKey(std::tuple<BOOL, WORD> key)
{
	return input.find(key) != input.end();
}
