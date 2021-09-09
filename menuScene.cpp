#include "scene.h"
#include "sceneManager.h"

void MenuScene::start()
{
	SceneManager::getInstance();
	render();
}

void MenuScene::render()
{
	SceneManager::getInstance().pushRenderQueue(std::make_tuple(0, 0, "1. Single Play"));
	SceneManager::getInstance().pushRenderQueue(std::make_tuple(0, 1, "2. Multiple Play"));
	SceneManager::getInstance().pushRenderQueue(std::make_tuple(0, 2, "3. Status"));
	SceneManager::getInstance().pushRenderQueue(std::make_tuple(0, 3, "4. Exit"));
}

void MenuScene::update()
{
	if (SceneManager::getInstance().findKey(std::make_tuple('1', true)))
	{
		SceneManager::getInstance().changeScene(SceneManager::SceneId::Play);
	}
	else if (SceneManager::getInstance().findKey(std::make_tuple('2', true)))
	{
		SceneManager::getInstance().changeScene(SceneManager::SceneId::Play);
	}
	else if (SceneManager::getInstance().findKey(std::make_tuple('3', true)))
	{
		SceneManager::getInstance().changeScene(SceneManager::SceneId::Status);
	}
	else if (SceneManager::getInstance().findKey(std::make_tuple('4', true)))
	{
		SceneManager::getInstance().changeScene(SceneManager::SceneId::None);
	}

}