#pragma once
#include "header.h"
#include "inputManager.h"
#include "socketManager.h"
#include "game.h"

void inputThreadFunc(std::mutex* m);
void socketThreadFunc(std::mutex* m);
void socketRecvThreadFunc();
void socketSendThreadFunc();
