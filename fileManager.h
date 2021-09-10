#pragma once
#include "header.h"

class FileManager
{
private:
	static FileManager* instance;
	const std::string saveFileName = "save.dat";
	std::map<std::string, std::map<std::string, std::string> > fileContents;

	void readFile(std::string);
	void writeFile(std::string);

public:
	static FileManager& getInstance();
	void initStatus();
	void saveStatus(int);
	void loadStatus();
	std::map<std::string, std::string> getSaveData();
};