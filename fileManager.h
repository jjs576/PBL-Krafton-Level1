#pragma once
#include "header.h"

class FileManager
{
private:
	static FileManager* instance;

public:
	static FileManager& getInstance();
};