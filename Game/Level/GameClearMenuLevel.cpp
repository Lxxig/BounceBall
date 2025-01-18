#include "GameClearMenuLevel.h"
#include "Game/Game.h"
#include "Level/MenuLevel.h"
#include "Level/GameLevel.h"

GameClearMenuLvel::GameClearMenuLvel()
{
	// ���� ���������� �̵�.
	menuItems.PushBack(new MenuItem("Next Stage!", []() {
		// ���� �������� �ε�.
		Game::Get().LoadLevel(new GameLevel(Game::Get().GetStageIndex() + 1));
		// ���� �������� �ε��� ������ Game Ŭ������ ����.
		Game::Get().SetStageIndex(Game::Get().GetStageIndex() + 1);
	}));

	menuItems.PushBack(new MenuItem("QuitGame", []() {
		Game::Get().QuitGame();
		}));

	length = menuItems.Size();
}

GameClearMenuLvel::~GameClearMenuLvel()
{
	for (auto* item : menuItems)
	{
		delete item;
	}
}

void GameClearMenuLvel::Update(float deltaTime)
{
	//if (Game::Get().GetKeyDown(VK_ESCAPE))
	//{
	//	Game::Get().ToggleMenu();
	//}

	if (Game::Get().GetKeyDown(VK_UP))
	{
		currentIndex = (currentIndex - 1 + length) % length;
	}
	if (Game::Get().GetKeyDown(VK_DOWN))
	{
		currentIndex = (currentIndex + 1) % length;
	}

	if (Game::Get().GetKeyDown(VK_RETURN))
	{
		menuItems[currentIndex]->onSelected();
	}
}

void GameClearMenuLvel::Draw()
{
	Super::Draw();

	Engine::Get().SetCursorPosition(0, 0);

	SetColor(unselectedColor);
	Log("ClearGameMenu\n\n");

	for (int ix = 0; ix < length; ++ix)
	{
		SetColor(ix == currentIndex ? selectedColor : unselectedColor);
		Log("%s\n", menuItems[ix]->menuText);
	}
}
