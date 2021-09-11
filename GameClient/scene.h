#pragma once
#include "header.h"
#include "player.h"

class Scene
{
protected:
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
	Player player;
	Object other;
	int boardSize;
	int score;
public:
	
	void start();
	void render();
	void update();
	void changePlayerStatus();
	void sceneControl();
	void renderFrame();
	//void comboCheck();
};


class StatusScene : public Scene
{
private:
	
public:
	void start();
	void render();
	void update();
	void renderScore();
};