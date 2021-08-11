#pragma once
#include "header.h"


class KeyManager
{
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

public:
	KeyManager();
	std::string checkCombo(std::vector<KEY_EVENT_RECORD> combo);

	std::string keyToString(WORD key, BOOL press);
};