#include "threads.h"

void inputThreadFunc(std::mutex* m)
{
	DWORD	cNumRead;
	INPUT_RECORD	inputBuffer[1];
	InputManager&	inputManager = InputManager::getInstance();

	for (;;)
	{
		if (SceneManager::getInstance().getCurSceneId() == SceneManager::SceneId::None)
			break;
		if (!ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), inputBuffer, 1, &cNumRead))
			throw std::runtime_error("Failed: ReadConsoleInput");
		if (inputBuffer[0].EventType == KEY_EVENT)
		{
			m->lock();
			inputManager.pushKey(inputBuffer[0].Event.KeyEvent);
			m->unlock();
		}
	}
}

void socketThreadFunc(std::mutex* m)
{
	SocketManager& socketManager = SocketManager::getInstance();
	for (;;)
	{
		if (SceneManager::getInstance().getCurSceneId() == SceneManager::SceneId::None)
			break;
		if (SceneManager::getInstance().getCurSceneId() == SceneManager::SceneId::Play)
		{

			std::thread recvThread(socketRecvThreadFunc);
			std::thread sendThread(socketSendThreadFunc);

			recvThread.join();
			sendThread.join();
			socketManager.closeSocket();
		}
	}
}

void socketRecvThreadFunc()
{
	SocketManager& socketManager = SocketManager::getInstance();
	for (;;)
	{
		if (SceneManager::getInstance().getCurSceneId() != SceneManager::SceneId::Play)
			break;
		if (socketManager.isConnected())
		{
			socketManager.recvMsg();
		}
	}
}

void socketSendThreadFunc()
{
	SocketManager& socketManager = SocketManager::getInstance();
	for (;;)
	{
		if (SceneManager::getInstance().getCurSceneId() != SceneManager::SceneId::Play)
			break;
		if (socketManager.isConnected())
		{

			socketManager.sendMsg();
		}
	}
}
