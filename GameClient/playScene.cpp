#include "scene.h"
#include "sceneManager.h"
#include "inputManager.h"
#include "fileManager.h"
#include "socketManager.h"

void PlayScene::start()
{
	boardSize = 20;
	player.boardSizeX = boardSize;
	player.boardSizeY = boardSize;
	score = 0;
	renderFrame();
	SocketManager::getInstance().setup();
	SocketManager::getInstance().connectServer();

}

void PlayScene::update()
{
	++score;
	changePlayerStatus();
	player.move();
	other.setPosition(SocketManager::getInstance().popRecvQueue());
	render();
	sceneControl();
}

void PlayScene::render()
{
	SceneManager::getInstance().pushRenderQueue(player.getOldX() + 1, player.getOldY() + 1, "  ");
	SceneManager::getInstance().pushRenderQueue(player.getX() + 1, player.getY() + 1, player.getCharacter());
	SceneManager::getInstance().pushRenderQueue(4, 22, std::to_string(score));
	SceneManager::getInstance().pushRenderQueue(other.getOldX() + 1, other.getOldY() + 1, "  ");
	SceneManager::getInstance().pushRenderQueue(other.getX() + 1, other.getY() + 1, other.getCharacter());
}

void PlayScene::changePlayerStatus()
{
	// direction press
	if (InputManager::getInstance().findKey(VK_UP, true))
		player.setVertical(Player::State::Vertical::up);
	else if (InputManager::getInstance().findKey(VK_DOWN, true))
		player.setVertical(Player::State::Vertical::down);

	if (InputManager::getInstance().findKey(VK_LEFT, true))
		player.setHorizontal(Player::State::Horizontal::left);
	else if (InputManager::getInstance().findKey(VK_RIGHT, true))
		player.setHorizontal(Player::State::Horizontal::right);

	// direction release
	if (InputManager::getInstance().findKey(VK_UP, false))
		player.setVertical(Player::State::Vertical::none);
	else if (InputManager::getInstance().findKey(VK_DOWN, false))
		player.setVertical(Player::State::Vertical::none);

	if (InputManager::getInstance().findKey(VK_LEFT, false))
		player.setHorizontal(Player::State::Horizontal::none);
	else if (InputManager::getInstance().findKey(VK_RIGHT, false))
		player.setHorizontal(Player::State::Horizontal::none);

	/*
	//change color
	if (InputManager::getInstance().findKey('G', true))
		player.setColor(Player::State::Color::green);
	else if (InputManager::getInstance().findKey('R', true))
		player.setColor(Player::State::Color::red);
	else if (InputManager::getInstance().findKey('Y', true))
		player.setColor(Player::State::Color::yellow);
	else if (InputManager::getInstance().findKey(VK_SPACE, true))
		player.setColor(Player::State::Color::def);
	*/
}

void PlayScene::sceneControl()
{
	if (InputManager::getInstance().findKey(VK_ESCAPE, true))
	{
		FileManager::getInstance().saveStatus(score);
		SocketManager::getInstance().pushSendQueue(":close");
		SceneManager::getInstance().changeScene(SceneManager::SceneId::Menu);
	}
}

void PlayScene::renderFrame()
{
	SceneManager::getInstance().pushRenderQueue(0, 0, "??");
	SceneManager::getInstance().pushRenderQueue(boardSize + 1, 0, "??");
	SceneManager::getInstance().pushRenderQueue(0, boardSize + 1, "??");
	SceneManager::getInstance().pushRenderQueue(boardSize + 1, boardSize + 1, "??");
	for (int i = 1; i <= boardSize; ++i)
	{
		SceneManager::getInstance().pushRenderQueue(i, 0, "??");
		SceneManager::getInstance().pushRenderQueue(i, boardSize + 1, "??");
		SceneManager::getInstance().pushRenderQueue(0, i, "??");
		SceneManager::getInstance().pushRenderQueue(boardSize + 1, i, "??");
	}
	SceneManager::getInstance().pushRenderQueue(0, 22, "score : ");
}