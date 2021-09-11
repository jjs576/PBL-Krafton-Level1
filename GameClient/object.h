#pragma once
#include "header.h"

class Object
{
protected:
	int x, y;
	int old_x, old_y;
	std::string character;
public:
	int getX();
	int getY();
	int getOldX();
	int getOldY();
	void setPosition(std::string);
	std::string getCharacter();
	void setCharacter(std::string);
	std::string getTransferData();
};