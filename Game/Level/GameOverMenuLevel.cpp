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
		// stageIndex = -1;�� ������ ������ ���ӿ������� -> �޴� ����
		// ������ ������ �ٽ��÷��� ���� ���Ѵ�.
		Game::Get().SetStageIndex(-1);
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

	// ��� �� ��ġ.
	const char* printText = "_____  _   _  _____ ______   _ ";
	int cursorPositonX = Engine::Get().ScreenSize().x / 2 - (int)strlen(printText) / 2;

	Engine::Get().Draw(Vector2(cursorPositonX, 0), " _____  _   _  _____ ______   _ ");
	Engine::Get().Draw(Vector2(cursorPositonX, 1), "|  _  || | | ||  ___|| ___ \\ | |");
	Engine::Get().Draw(Vector2(cursorPositonX, 2), "| | | || | | || |__  | |_/ / | |");
	Engine::Get().Draw(Vector2(cursorPositonX, 3), "| | | || | | ||  __| |    /  | |");
	Engine::Get().Draw(Vector2(cursorPositonX, 4), "\\ \\_/ /\\ \\_/ /| |___ | |\\ \\  |_|");
	Engine::Get().Draw(Vector2(cursorPositonX, 5), " \\___/  \\___/ \\____/ \\_| \\_| (_)");

	int i = 0;
	for (int ix = 0; ix < menuItems.size(); ++ix)
	{
		Color setColor = (ix == currentIndex) ? selectedColor : unselectedColor;
		Engine::Get().Draw(Vector2(1, ix + 10 + i), "|");
		Engine::Get().Draw(Vector2(2, ix + 10 + i), menuItems[ix]->menuText, setColor);
		++i;
	}
}
