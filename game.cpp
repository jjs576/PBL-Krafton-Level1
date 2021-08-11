#include "game.h"
#include "inputThread.h"

Game::Game()
{
	io.setTerm(IOManager::TermMode::game);
	lastInputTick = 0;
	curTick = 0;
}

Game::~Game()
{
	io.setTerm(IOManager::TermMode::origin);
}

void Game::run()
{
	std::mutex	m;
	std::thread	ioThread(inputThreadRun, &io, &m);
	ioThread.detach();
	render();
	curTick = 0;
	while (!io.isEnd)
	{
		timer(33);
		m.lock();
		KEY_EVENT_RECORD input= io.getKey();
		m.unlock();
		if (input.wVirtualKeyCode != 0)
		{
			lastInputTick = curTick;
			inputVector.push_back(input);
			inputControl(input);
		}
		comboCheck();
		//render
		io.gotoxy(0, 21);
		std::cout << "                                                                          ";
		io.gotoxy(0, 21);
		for (auto it = inputVector.begin(); it != inputVector.end(); ++it)
			std::cout << it->wVirtualKeyCode << " ";
		player.behavior();
		render();
		io.gotoxy(0, 22);
		std::cout << "Tick :" << ++curTick;
	}
	io.gotoxy(0, 0);
	io.clear();
}

void Game::render()
{
	renderObject(player.getOldX(), player.getOldY(), "  ");
	renderObject(player.getX(), player.getY(), player.getCharacter());
}

void Game::renderObject(int x, int y, std::string c)
{
	io.gotoxy(x * 2, y);
	std::cout << c;
}

void Game::timer(int time)
{
	clock_t start = clock();
	for (;;)
	{
		clock_t end = clock();
		if (end - start >= time)
			break;
	}
}

void Game::inputControl(KEY_EVENT_RECORD input)
{
	if (input.bKeyDown)
		switch (input.wVirtualKeyCode)
		{
		case VK_UP:
			player.setVertical(Player::State::Vertical::up);
			break;
		case VK_DOWN:
			player.setVertical(Player::State::Vertical::down);
			break;
		case VK_LEFT:
			player.setHorizontal(Player::State::Horizontal::left);
			break;
		case VK_RIGHT:
			player.setHorizontal(Player::State::Horizontal::right);
			break;
		case VK_SPACE:
			player.setColor(Player::State::Color::def);
			break;
		case 'R':
			player.setColor(Player::State::Color::red);
			break;
		case 'G':
			player.setColor(Player::State::Color::green);
			break;
		case 'Y':
			player.setColor(Player::State::Color::yellow);
			break;
		case VK_ESCAPE:
			io.isEnd = true;
		}
	else
	{
		switch (input.wVirtualKeyCode)
		{
		case VK_UP:
		case VK_DOWN:
			player.setVertical(Player::State::Vertical::none);
			break;
		case VK_LEFT:
		case VK_RIGHT:
			player.setHorizontal(Player::State::Horizontal::none);
			break;
		}
	}
}

void Game::comboCheck()
{
	std::string skill;
	if ((skill = keyManager.checkCombo(inputVector)) != "")
	{
		io.gotoxy(0, 24);
		player.setSkillName(skill);
		inputVector.clear();
	}
	if (curTick - lastInputTick > 5)
		inputVector.clear();
}
