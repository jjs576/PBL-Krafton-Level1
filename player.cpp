#include "player.h"
#include "game.h"


Player::Player()
{
	x = 0;
	y = 0;
	old_x = 0;
	old_y = 0;
	color = 0;
	speed = 1;
	character = "бс";
}

void Player::moveUp()
{
	old_x = x;
	old_y = y;
	y -= speed;
	if (y < 0)
		y = 0;
}

void Player::moveRight()
{
	old_x = x;
	old_y = y;
	x += speed;
	if (x >= Game::boardSizeX)
		x = Game::boardSizeX - 1;
}

void Player::moveDown()
{
	old_x = x;
	old_y = y;
	y += speed;
	if (y >= Game::boardSizeY)
		y = Game::boardSizeY - 1;
}

void Player::moveLeft()
{
	old_x = x;
	old_y = y;
	x -= speed;
	if (x < 0)
		x = 0;
}

void Player::changeColor()
{
	color = (color + 1) % 4;
	switch (color)
	{
	case 0:
		character = "бс";
		break;
	case 1:
		character = RED("бс");
		break;
	case 2:
		character = YELLOW("бс");
		break;
	case 3:
		character = GREEN("бс");
		break;
	}
}

void Player::speedUp()
{
	++speed;
}

void Player::speedDown()
{
	--speed;
	if (speed <= 0)
		speed = 1;
}

int Player::getX()
{
	return x;
}

int Player::getY()
{
	return y;
}

int Player::getOldX()
{
	return old_x;
}

int Player::getOldY()
{
	return old_y;
}

std::string Player::getCharacter()
{
	return character;
}
