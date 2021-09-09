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

InputManager::InputManager()
{

}

InputManager& InputManager::getInstance()
{
	if (instance == NULL)
		instance = new InputManager();
	return *instance;
}
