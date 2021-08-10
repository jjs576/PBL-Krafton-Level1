#pragma once
#include "header.h"

class Player
{
private:
	int x, y;
	int speed;
	int color;
public:
	Player();
	void moveUp();
	void moveLeft();
	void moveRight();
	void moveDown();
	void changeColor();
	void speedUp();
	void speedDown();
	int getX();
	int getY();
};