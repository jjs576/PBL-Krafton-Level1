#pragma once
#pragma comment(lib, "ws2_32")
#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <queue>
#include <list>
#include <tuple>
#include <set>
#include <map>
#include <fstream>
#include <WinSock2.h>

#define __RED		std::string("\033[31m")
#define __GREEN		std::string("\033[32m")
#define __YELLOW	std::string("\033[33m")
#define __DEFAULT	std::string("\033[0m")

#define RED(x)		__RED + std::string(x) + __DEFAULT
#define GREEN(x)	__GREEN + std::string(x) + __DEFAULT
#define YELLOW(x)	__YELLOW + std::string(x) + __DEFAULT

