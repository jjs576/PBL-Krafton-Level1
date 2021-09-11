#pragma once
#include "header.h"
#include "scene.h"
#include "inputManager.h"

class SceneManager
{
public:
	enum class SceneId
	{
		None = 0,
		Menu,
		Play,
		Status,
	};

private:
	static SceneManager* instance;
	Scene* curScene;
	SceneId curSceneId;
	std::queue<std::tuple<int, int, std::string> > renderQueue;
	
	SceneManager();

public:
	static SceneManager& getInstance();
	void start();
	void update();
	void pushRenderQueue(int, int, std::string);
	std::tuple<int, int, std::string> popRenderQueue();
	void changeScene(SceneId);
	SceneId getCurSceneId();
};