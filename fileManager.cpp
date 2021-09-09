#include "fileManager.h"

FileManager* FileManager::instance = 0;

FileManager& FileManager::getInstance()
{
	if (instance == NULL)
		instance = new FileManager();
	return *instance;
}