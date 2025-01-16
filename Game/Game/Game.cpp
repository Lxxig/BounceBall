#include "Game.h"

#include "Level/GameLevel.h"

Game* Game::instance = nullptr;

Game::Game()
	: Engine()
{
	instance = this;

	gameLevel.PushBack(new GameLevel("../Assets/Maps/Stage1.txt"));
	gameLevel.PushBack(new GameLevel("../Assets/Maps/Stage2.txt"));
	gameLevel.PushBack(new GameLevel("../Assets/Maps/Stage3.txt"));
}

// mainLevel -> gmaeLevel
// menuLevel -> menuLevel

// mainLevel -> menuLevel
// gameLevel -> gameLevel

Game::~Game()
{
	if (showGame)
	{
		delete backLevel;
		backLevel = nullptr;
		mainLevel = nullptr;
	}
	else
	{
		delete mainLevel;
		mainLevel = nullptr;
	}

	for (int i = 0; i < gameLevel.Size(); ++i)
	{
		delete gameLevel[i];
		gameLevel[i] = nullptr;
	}
}

// mainLevel = menuLevel
void Game::ToggleMenu()
{
	system("cls");
	//Clear();
	showGame = !showGame;
	if (showGame)
	{
		backLevel = mainLevel;
		mainLevel = gameLevel[stageIndex];
	}
	else
	{
		mainLevel = backLevel;
	}
}