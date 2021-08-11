#include "keyManager.h"


KeyManager::Combo::Combo()
{
	child.resize(2560);
	for (auto it = child.begin(); it != child.end(); ++it)
		*it = NULL;
	skillName = "";
}
KeyManager::Combo::~Combo()
{
	for (auto it = child.begin(); it != child.end(); ++it)
		if (*it != NULL)
			delete* it;
}
void KeyManager::Combo::insert(std::vector<std::string> combo, size_t index)
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

std::string KeyManager::Combo::find(std::vector<std::string> combo, size_t index)
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


KeyManager::KeyManager()
{
	std::vector < std::string > up_dash = { keyToString(VK_UP, 1), keyToString(VK_UP, 0), keyToString(VK_UP, 1), keyToString(VK_UP, 0), ":UpDash" };
	std::vector < std::string > left_dash = { keyToString(VK_LEFT, 1), keyToString(VK_LEFT, 0), keyToString(VK_LEFT, 1), keyToString(VK_LEFT, 0), ":LeftDash" };
	std::vector < std::string > right_dash = { keyToString(VK_RIGHT, 1), keyToString(VK_RIGHT, 0), keyToString(VK_RIGHT, 1), keyToString(VK_RIGHT, 0), ":RightDash" };
	std::vector < std::string > down_dash = { keyToString(VK_DOWN, 1), keyToString(VK_DOWN, 0), keyToString(VK_DOWN, 1), keyToString(VK_DOWN, 0), ":DownDash" };
	combo.insert(up_dash, 0);
	combo.insert(left_dash, 0);
	combo.insert(right_dash, 0);
	combo.insert(down_dash, 0);

}
std::string KeyManager::checkCombo(std::vector<KEY_EVENT_RECORD> combo)
{
	std::vector<std::string> comboString;
	for (auto it = combo.begin(); it != combo.end(); ++it)
		comboString.push_back(keyToString(it->wVirtualKeyCode, it->bKeyDown));
	comboString.push_back("");
	return this->combo.find(comboString, 0);
}

std::string KeyManager::keyToString(WORD key, BOOL press)
{
	return std::to_string(key) + std::to_string(press);
}
