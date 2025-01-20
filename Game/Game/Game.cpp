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
	// mainLevel�� menuLevel�� ����
	else
	{
		delete mainLevel;
		mainLevel = nullptr;

		// backLevel�� menuLevel�� �ƴ� �ٸ� �������� ����(GameLevel)�̸� delete.
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
	// ���� ������ �����ϸ� ����.
	if (mainLevel != nullptr)
	{
		// ���� ������ MenuLevel�̸� nullptr �ʱ�ȭ.
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
	
	// ���� stage�� �޴����� ������ stage�� �ٸ� ��
	// backLevel�� ���� �ִ� ����stage(GameLevel)��
	// ���� delete�� �� backLevel�� mainLevel ����.
	// �׷��� ���� ��� memory leak�� �߻��Ѵ�.
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

	// ������ Ŭ������ ���.
	if(mainLevel->As<GameLevel>()->IsGameClear())
	{
		LoadLevel(new GameClearMenuLvel());
	}

	// ���� ������ ���.
	else if (mainLevel->As<GameLevel>()->IsGameOver())
	{
		LoadLevel(new GameOverMenuLevel());
	}
}
