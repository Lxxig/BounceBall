#include "Game.h"

#include "Level/GameLevel.h"
#include "Level/MenuLevel.h"
#include "Level/GameClearMenuLevel.h"
#include "Level/GameOverMenuLevel.h"

Game* Game::instance = nullptr;

Game::Game()
	: Engine()
{
	instance = this;
	
	stageAdress.emplace_back("../Assets/Maps/Stage1.txt");
	stageAdress.emplace_back("../Assets/Maps/Stage2.txt");
	stageAdress.emplace_back("../Assets/Maps/Stage3.txt");
}

Game::~Game()
{
	if (mainLevel->As<GameLevel>())
	{
		// backLevel = menuLevel.
		delete backLevel;
		backLevel = nullptr;
		delete mainLevel;
		mainLevel = nullptr;
	}
	// mainLevel과 menuLevel인 상태
	else
	{
		delete mainLevel;
		mainLevel = nullptr;

		// backLevel이 menuLevel이 아닌 다른 스테이지 레벨(GameLevel)이면 delete.
		if(backLevel != nullptr)
		{
			if (backLevel->As<GameLevel>())
			{
				delete backLevel;
				backLevel = nullptr;
			}
		}
		menuLevel = nullptr;
	}
	
	if (menuLevel != nullptr)
	{
		delete menuLevel;
		menuLevel = nullptr;
	}
}

void Game::LoadLevel(Level* newLevel)
{
	// 기존 레벨이 존재하면 제거.
	if (mainLevel != nullptr)
	{
		// 기존 레벨이 MenuLevel이면 nullptr 초기화.
		if(mainLevel->As<MenuLevel>())
		{
			menuLevel = nullptr;
		}
		delete mainLevel;
	}

	mainLevel = newLevel;
}

// mainLevel = menuLevel
void Game::ToggleMenu()
{
	if (menuLevel == nullptr)
	{
		menuLevel = new MenuLevel();
	}

	system("cls");
	//Clear();
	
	// 기존 stage와 메뉴에서 선택한 stage가 다를 때
	// backLevel에 남아 있는 기존stage(GameLevel)을
	// 먼저 delete한 후 backLevel에 mainLevel 저장.
	// 그렇지 않을 경우 memory leak이 발생한다.
	if(mainLevel->As<GameLevel>())
	{
		if(backLevel != nullptr)
		{
			if (backLevel->As<GameLevel>())
			{
				delete backLevel;
				backLevel = nullptr;
			}
		}
		backLevel = mainLevel;
		mainLevel = menuLevel;
	}
	else
	{
		mainLevel = backLevel;
		backLevel = menuLevel;
	}
}

void Game::ToggleGameClearOrOverMenu()
{
	system("cls");
	//Clear();

	// 게임을 클리어한 경우.
	if(mainLevel->As<GameLevel>()->IsGameClear())
	{
		LoadLevel(new GameClearMenuLvel());
	}

	// 게임 오버인 경우.
	else if (mainLevel->As<GameLevel>()->IsGameOver())
	{
		LoadLevel(new GameOverMenuLevel());
	}
}
