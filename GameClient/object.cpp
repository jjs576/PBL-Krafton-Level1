#include "object.h"


int Object::getX()
{
	return x;
}

int Object::getY()
{
	return y;
}

int Object::getOldX()
{
	return old_x;
}

int Object::getOldY()
{
	return old_y;
}

void Object::setPosition(std::string msg)
{
	//msg = ":xx,yy,cc"
	if (msg.size() != 9)
		return;
	old_x = x;
	old_y = y;
	x = std::atoi(msg.substr(1, 2).c_str());
	y = std::atoi(msg.substr(4, 2).c_str());
	character = msg.substr(7,2);
}

std::string Object::getCharacter()
{
	return character;
}

void Object::setCharacter(std::string c)
{
	character = c;
}

std::string Object::getTransferData()
{
	std::string _x = std::to_string(getX());
	if (_x.size() == 1)
		_x = "0" + _x;
	std::string _y = std::to_string(getY());
	if (_y.size() == 1)
		_y = "0" + _y;
	return ":" + _x + "," +_y + "," + getCharacter();
}