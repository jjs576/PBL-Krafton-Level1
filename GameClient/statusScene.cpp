#include "scene.h"
#include "fileManager.h"
#include "inputManager.h"
#include "sceneManager.h"

void StatusScene::start()
{
	FileManager::getInstance().loadStatus();
	renderScore();
}

void StatusScene::render()
{

}

void StatusScene::update()
{
	if (InputManager::getInstance().findKey(VK_ESCAPE, true))
	{
		SceneManager::getInstance().changeScene(SceneManager::SceneId::Menu);
	}
	else if (InputManager::getInstance().findKey(VK_SPACE, true))
	{
		SceneManager::getInstance().changeScene(SceneManager::SceneId::Menu);
	}
}

void StatusScene::renderScore()
{
	std::map<std::string, std::string> saveData = FileManager::getInstance().getSaveData();
	SceneManager::getInstance().pushRenderQueue(0, 0, "PlayCount : " + saveData["PlayCount"]);
	SceneManager::getInstance().pushRenderQueue(0, 1, "HighScore : " + saveData["HighScore"]);
}