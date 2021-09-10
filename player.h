#pragma once
#include "header.h"

class Player
{
public:
	struct State {
		enum class Horizontal {
			none = 0,
			left,
			right,
			
		};
		enum class Vertical {
			none = 0,
			up,
			down,
		};
		enum class Color {
			def = 0,
			red,
			yellow,
			green,
		};
		Horizontal moveHorizontal;
		Vertical moveVertical;
		Color color;
		State();
	};
	int		boardSizeX;
	int		boardSizeY;
private:

	class Combo
	{
	private:
		std::vector<Combo*> child;
		std::string skillName;
	public:
		Combo();
		~Combo();
		void insert(std::vector<std::string> combo, size_t index);

		std::string find(std::vector<std::string> combo, size_t index);
	};

	Combo combo;


	int x, y;
	int old_x, old_y;
	int speed;
	std::string character;
	std::string coloredCharacter;
	std::string skillName;
	State state;

public:
	Player();
	void setHorizontal(Player::State::Horizontal);
	void setVertical(Player::State::Vertical);
	void setColor(Player::State::Color);
	void setSkillName(std::string);
	void behavior();

	void move();
	void moveUp();
	void moveLeft();
	void moveRight();
	void moveDown();

	void skill();
	void skillUpDash();
	void skillLeftDash();
	void skillRightDash();
	void skillDownDash();

	void speedUp();
	void speedDown();
	int getX();
	int getY();
	int getOldX();
	int getOldY();
	std::string getCharacter();


	std::string checkCombo(std::vector<KEY_EVENT_RECORD> combo);
	std::string keyToString(WORD key, BOOL press);
	void insertCombo(std::vector<std::string> combo);
};