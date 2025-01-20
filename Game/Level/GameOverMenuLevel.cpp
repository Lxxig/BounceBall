#include "GameOverMenuLevel.h"
#include "Game/Game.h"
#include "Level/MenuLevel.h"
#include "Level/GameLevel.h"

GameOverMenuLevel::GameOverMenuLevel()
{
	// Ŀ�� ���߱�.
	Engine::Get().SetCursorType(CursorType::NoCursor);

	menuItems.emplace_back(new MenuItem("ReGame", []() {
		// ���� ���������� ���Ҵ�.
		Game::Get().LoadLevel(new GameLevel(Game::Get().GetStageIndex()));
		// �������� �ε��� ���� ����.
		Game::Get().SetStageIndex(Game::Get().GetStageIndex());
		}));

	// �޴��� ���ư���.
	menuItems.emplace_back(new MenuItem("Menu", []() {
		// ���ư� �� ���� ��� ����.
		Engine::Get().Clear();
		Game::Get().LoadLevel(new MenuLevel());
		}));

	// ���� ����.
	menuItems.emplace_back(new MenuItem("QuitGame", []() {
		Game::Get().QuitGame();
		}));

	// �޴� ������ ���� ����.
	length = (int)menuItems.size();
}

GameOverMenuLevel::~GameOverMenuLevel()
{
	for (auto* item : menuItems)
	{
		delete item;
	}
}

void GameOverMenuLevel::Update(float deltaTime)
{
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

void GameOverMenuLevel::Draw()
{
	Super::Draw();

	Engine::Get().SetCursorPosition(0, 0);

	SetColor(unselectedColor);
	Log("GameOverMenu\n\n");

	for (int ix = 0; ix < length; ++ix)
	{
		SetColor(ix == currentIndex ? selectedColor : unselectedColor);
		Log("%s\n", menuItems[ix]->menuText);
	}
}
