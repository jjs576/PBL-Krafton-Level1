#include "player.h"
#include "game.h"

Player::State::State()
{
	moveVertical = Vertical::none;
	moveHorizontal = Horizontal::none;
	color = Color::def;
}

Player::Player()
{
	x = 0;
	y = 0;
	old_x = 0;
	old_y = 0;
	speed = 1;
	character = "��";
	colored_character = character;
}


void Player::setHorizontal(Player::State::Horizontal h)
{
	state.moveHorizontal = h;
}

void Player::setVertical(Player::State::Vertical v)
{
	state.moveVertical = v;
}

void Player::setColor(Player::State::Color c)
{
	state.color = c;
	switch (state.color) {
	case State::Color::def:
		colored_character = character;
		break;
	case State::Color::green:
		colored_character = GREEN(character);
		break;
	case State::Color::red:
		colored_character = RED(character);
		break;
	case State::Color::yellow:
		colored_character = YELLOW(character);
		break;
	}
}

void Player::move()
{
	old_x = x;
	old_y = y;
	switch (state.moveVertical)
	{
	case Player::State::Vertical::up:
		moveUp();
		break;
	case Player::State::Vertical::down:
		moveDown();
		break;
	default:
		break;
	}
	switch (state.moveHorizontal)
	{
	case Player::State::Horizontal::left:
		moveLeft();
		break;
	case Player::State::Horizontal::right:
		moveRight();
		break;
	default:
		break;
	}
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

void Player::moveLeft()
{
	x -= speed;
	if (x < 0)
		x = 0;
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
	return colored_character;
}
