#pragma once
#include "header.h"

class Player
{
private:
	int x, y;
	int old_x, old_y;
	int speed;
	int color;
	std::string character;

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
	int getOldX();
	int getOldY();
	std::string getCharacter();

};