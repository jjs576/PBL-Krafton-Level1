#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <queue>
#include <list>
#include <tuple>
#include <set>
#include <Windows.h>

#define __RED		std::string("\033[31m")
#define __GREEN		std::string("\033[32m")
#define __YELLOW	std::string("\033[33m")
#define __DEFAULT	std::string("\033[0m")

#define RED(x)		__RED + std::string(x) + __DEFAULT
#define GREEN(x)	__GREEN + std::string(x) + __DEFAULT
#define YELLOW(x)	__YELLOW + std::string(x) + __DEFAULT

