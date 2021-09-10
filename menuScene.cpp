#include "scene.h"
#include "sceneManager.h"

void MenuScene::start()
{
	render();
}

void MenuScene::render()
{
	SceneManager::getInstance().pushRenderQueue(0, 0, "1. Play Game");
	SceneManager::getInstance().pushRenderQueue(0, 1, "2. Status");
	SceneManager::getInstance().pushRenderQueue(0, 2, "3. Exit");
}

void MenuScene::update()
{
	if (InputManager::getInstance().findKey('1', true))
	{
		SceneManager::getInstance().changeScene(SceneManager::SceneId::Play);
	}
	else if (InputManager::getInstance().findKey('2', true))
	{
		SceneManager::getInstance().changeScene(SceneManager::SceneId::Status);
	}
	else if (InputManager::getInstance().findKey('3', true))
	{
		SceneManager::getInstance().changeScene(SceneManager::SceneId::None);
	}
}