#include "player.h"
#include "game.h"


Player::Player()
{
	x = 0;
	y = 0;
	speed = 1;
}

void Player::moveUp()
{
	y -= speed;
	if (y < 0)
		y = 0;
}

void Player::moveRight()
{
	x += speed;
	if (x >= Game::boardSizeX)
		x = Game::boardSizeX - 1;
}

void Player::moveDown()
{
	y += speed;
	if (y >= Game::boardSizeY)
		y = Game::boardSizeY - 1;
}

void Player::changeColor()
{
	color = (color + 1) % 4;
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

void Player::moveLeft()
{
	x -= speed;
	if (x < 0)
		x = 0;
}
