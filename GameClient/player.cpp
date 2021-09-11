#include "player.h"
#include "game.h"
#include "socketManager.h"


Player::Combo::Combo()
{
	child.resize(2560);
	for (auto it = child.begin(); it != child.end(); ++it)
		*it = NULL;
	skillName = "";
}

Player::Combo::~Combo()
{
	for (auto it = child.begin(); it != child.end(); ++it)
		if (*it != NULL)
			delete* it;
}

void Player::Combo::insert(std::vector<std::string> combo, size_t index)
{
	if (combo.size() <= index)
		return;
	if (combo[index][0] == ':')
	{
		this->skillName = combo[index];
		return;
	}
	int next = std::atoi(combo[index].c_str());
	if (child[next] == NULL)
		child[next] = new Combo();
	child[next]->insert(combo, index + 1);
}

std::string Player::Combo::find(std::vector<std::string> combo, size_t index)
{
	if (combo.size() <= 1)
		return "";
	if (combo.size() <= index)
		return "";
	std::string value = combo[index];
	int next = std::atoi(value.c_str());
	if (value == "" && this->skillName != "")
		return this->skillName;
	if (child[next] == NULL)
		return "";
	return child[next]->find(combo, index + 1);
}

std::string Player::checkCombo(std::vector<KEY_EVENT_RECORD> combo)
{
	std::vector<std::string> comboString;
	for (auto it = combo.begin(); it != combo.end(); ++it)
		comboString.push_back(keyToString(it->wVirtualKeyCode, it->bKeyDown));
	comboString.push_back("");
	return this->combo.find(comboString, 0);
}
  
std::string Player::keyToString(WORD key, BOOL press)
{
	return std::to_string(key) + std::to_string(press);
}

void Player::insertCombo(std::vector<std::string> combo)
{
	this->combo.insert(combo, 0);
}

Player::State::State()
{
	moveVertical = Vertical::none;
	moveHorizontal = Horizontal::none;
	color = Color::def;
}

Player::Player()
{
	std::vector < std::string > up_dash = { keyToString(VK_UP, 1), keyToString(VK_UP, 0), keyToString(VK_UP, 1), keyToString(VK_UP, 0), ":UpDash" };
	std::vector < std::string > left_dash = { keyToString(VK_LEFT, 1), keyToString(VK_LEFT, 0), keyToString(VK_LEFT, 1), keyToString(VK_LEFT, 0), ":LeftDash" };
	std::vector < std::string > right_dash = { keyToString(VK_RIGHT, 1), keyToString(VK_RIGHT, 0), keyToString(VK_RIGHT, 1), keyToString(VK_RIGHT, 0), ":RightDash" };
	std::vector < std::string > down_dash = { keyToString(VK_DOWN, 1), keyToString(VK_DOWN, 0), keyToString(VK_DOWN, 1), keyToString(VK_DOWN, 0), ":DownDash" };
	insertCombo(up_dash);
	insertCombo(left_dash);
	insertCombo(right_dash);
	insertCombo(down_dash);

	x = 0;
	y = 0;
	old_x = 0;
	old_y = 0;
	speed = 1;
	character = "¡Ú";
	//coloredCharacter = character;
	skillName = "";

}

void Player::setHorizontal(Player::State::Horizontal h)
{
	state.moveHorizontal = h;
}

void Player::setVertical(Player::State::Vertical v)
{
	state.moveVertical = v;
}
/*
void Player::setColor(Player::State::Color c)
{
	state.color = c;
	switch (state.color) {
	case State::Color::def:
		coloredCharacter = character;
		break;
	case State::Color::green:
		coloredCharacter = GREEN(character);
		break;
	case State::Color::red:
		coloredCharacter = RED(character);
		break;
	case State::Color::yellow:
		coloredCharacter = YELLOW(character);
		break;
	}
}
*/
void Player::setSkillName(std::string s)
{
	skillName = s;
}

void Player::behavior()
{
	old_x = x;
	old_y = y;
	if (skillName == "")
		move();
	else
		skill();
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
	if (SocketManager::getInstance().isConnected())
		if (state.moveHorizontal != Player::State::Horizontal::none || state.moveVertical != Player::State::Vertical::none)
			SocketManager::getInstance().pushSendQueue(getTransferData());

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
	if (x >= boardSizeX)
		x = boardSizeX - 1;
}

void Player::moveDown()
{
	y += speed;
	if (y >= boardSizeY)
		y = boardSizeY - 1;
}

void Player::moveLeft()
{
	x -= speed;
	if (x < 0)
		x = 0;
}


void Player::skill()
{
	if (skillName == ":UpDash")
		skillUpDash();
	else if (skillName == ":LeftDash")
		skillLeftDash();
	else if (skillName == ":RightDash")
		skillRightDash();
	else if (skillName == ":DownDash")
		skillDownDash();
	skillName = "";
}

void Player::skillUpDash()
{
	y = 0;
}
void Player::skillLeftDash()
{
	x = 0;
}
void Player::skillRightDash()
{
	x = boardSizeX - 1;
}
void Player::skillDownDash()
{
	y = boardSizeY - 1;
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


