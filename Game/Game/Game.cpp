#include "Game.h"

#include "Level/GameLevel.h"
#include "Level/GameClearMenuLevel.h"
#include "Level/MenuLevel.h"

Game* Game::instance = nullptr;

Game::Game()
	: Engine()
{
	instance = this;
	
	stageAdress.PushBack("../Assets/Maps/Stage1.txt");
	stageAdress.PushBack("../Assets/Maps/Stage2.txt");
	stageAdress.PushBack("../Assets/Maps/Stage3.txt");
}

Game::~Game()
{
	if (mainLevel->As<GameLevel>())
	{
		// backLevel = menuLevel or GameLevel�� ����.
		delete backLevel;
		backLevel = nullptr;
		//menuLevel = nullptr;
		mainLevel = nullptr;
	}
	else
	{
		// backLevel = GameLevel�� ����.
		delete mainLevel;
		mainLevel = nullptr;
		menuLevel = nullptr;
	}
	
	if (menuLevel != nullptr)
	{
		delete menuLevel;
		menuLevel = nullptr;
	}
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
	
	// mainLevel�� backLevel �Ѵ� GameLevel�̸� delete backLevel;
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

void Game::ToggleGameClearMenu()
{
	system("cls");
	//Clear();

	// mainLevel�� GameLevel�� ���.
	if (mainLevel->As<GameLevel>())
	{
		LoadLevel(new GameClearMenuLvel());
	}
	// mainLevel�� GameClearMenuLvel�� ���.
	else if (mainLevel->As<GameClearMenuLvel>())
	{
		LoadLevel(new GameLevel(stageIndex));
	}
}
