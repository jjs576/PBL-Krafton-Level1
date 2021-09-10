#include "fileManager.h"

FileManager* FileManager::instance = 0;

FileManager& FileManager::getInstance()
{
	if (instance == NULL)
		instance = new FileManager();
	return *instance;
}

void FileManager::readFile(std::string fileName)
{
	std::ifstream in(fileName);
	if (in.fail())
	{
		return;
	}
	std::map<std::string, std::string> fileMap;
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(in, line))
		lines.push_back(line);
	in.close();
	for (auto it = lines.begin(); it != lines.end(); ++it)
	{
		size_t delim = it->find('=');
		std::string key = it->substr(0, delim);
		std::string value = it->substr(delim + 1, it->length() - delim);
		fileMap[key] = value;
	}
	fileContents[fileName] = fileMap;
}

void FileManager::writeFile(std::string fileName)
{
	std::ofstream out(fileName);
	if (out.fail())
	{
		return;
	}
	for (auto it = fileContents[fileName].begin(); it != fileContents[fileName].end(); ++it)
	{
		std::string line = it->first + '=' + it->second + '\n';
		out.write(line.c_str(), line.length());
	}
	out.close();
}

void FileManager::initStatus()
{
	fileContents[saveFileName].clear();
	fileContents[saveFileName]["PlayCount"] = "0";
	fileContents[saveFileName]["HighScore"] = "0";
}

void FileManager::saveStatus(int highScore)
{
	fileContents[saveFileName]["PlayCount"] = std::to_string(std::atoi(fileContents[saveFileName]["PlayCount"].c_str()) + 1);
	fileContents[saveFileName]["HighScore"] = std::to_string(max(std::atoi(fileContents[saveFileName]["HighScore"].c_str()), highScore));
	writeFile(saveFileName);
}

void FileManager::loadStatus()
{
	readFile(saveFileName);
}

std::map<std::string, std::string> FileManager::getSaveData()
{
	return fileContents[saveFileName];
}
