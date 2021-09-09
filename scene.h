#pragma once
#include "header.h"

class Scene
{
protected:
	std::string sceneName;

public:
	virtual void start() = 0;
	virtual void render() = 0;
	virtual void update() = 0;
};

class MenuScene : public Scene
{
private:

public:
	void start();
	void render();
	void update();

};


class PlayScene : public Scene
{
private:
	bool isOnline;
	std::vector<std::vector<int> > map;
public:
	void start();
	void render();
	void update();
	void comboCheck();
};


class StatusScene : public Scene
{
private:

public:
	void start();
	void render();
	void update();

};