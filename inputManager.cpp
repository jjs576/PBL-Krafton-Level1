#include "inputManager.h"

InputManager* InputManager::instance = 0;


void InputManager::pushKey(KEY_EVENT_RECORD key)
{
	inputQueue.push(key);
}


KEY_EVENT_RECORD InputManager::getKey()
{
	KEY_EVENT_RECORD input = { 0, };
	if (!inputQueue.empty())
	{
		input = inputQueue.front();
		inputQueue.pop();
	}
	return input;
}

void InputManager::insertInputSet(KEY_EVENT_RECORD input)
{
	inputSet.insert(std::make_tuple(input.wVirtualKeyCode, input.bKeyDown));
}

void InputManager::clearInputSet()
{
	inputSet.clear();
}


bool InputManager::findKey(WORD key, BOOL press)
{
	return inputSet.find(std::make_tuple(key, press)) != inputSet.end();
}

InputManager::InputManager()
{

}

InputManager& InputManager::getInstance()
{
	if (instance == NULL)
		instance = new InputManager();
	return *instance;
}
