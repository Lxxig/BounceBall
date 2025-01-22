#include "GameClearMenuLevel.h"
#include "Game/Game.h"
#include "Level/MenuLevel.h"
#include "Level/GameLevel.h"

GameClearMenuLvel::GameClearMenuLvel()
{
	// Ŀ�� ���߱�.
	Engine::Get().SetCursorType(CursorType::NoCursor);

	// Ŭ������ ���� ���������� ������ ���.
	if (Game::Get().GetStageIndex() + 1 < Game::Get().stageAdress.size())
	{
		// ���� ���������� �̵�.
		menuItems.emplace_back(new MenuItem("Next Stage!", []() {
			// ���� �������� �ε�.
			Game::Get().LoadLevel(new GameLevel(Game::Get().GetStageIndex() + 1));
			// ���� �������� �ε��� ������ Game Ŭ������ ����.
			Game::Get().SetStageIndex(Game::Get().GetStageIndex() + 1);
			}));

		// �޴��� ���ư���.
		menuItems.emplace_back(new MenuItem("Menu", []() {
			// stageIndex = -1;�� ������ ������ ���ӿ������� -> �޴� ����
			// ������ ������ �ٽ��÷��� ���� ���Ѵ�.
			Game::Get().SetStageIndex(-1);
			Game::Get().LoadLevel(new MenuLevel());
			}));

		menuItems.emplace_back(new MenuItem("QuitGame", []() {
			Game::Get().QuitGame();
			}));
	}

	// ��� ���������� �� Ŭ������ ���.
	else if (Game::Get().GetStageIndex() + 1 >= Game::Get().stageAdress.size())
	{
		// �޴��� ���ư���.
		menuItems.emplace_back(new MenuItem("Menu (Clear all stages)", []() {
			Game::Get().LoadLevel(new MenuLevel());
			}));

		menuItems.emplace_back(new MenuItem("QuitGame", []() {
			Game::Get().QuitGame();
			}));

	}

	// �޴� ������ ���� ����.
	length = (int)menuItems.size();
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

	// ��� �� ��ġ.
	const char* printText = " _____  _      _____   ___  ______  _ ";
	int cursorPositonX = Engine::Get().ScreenSize().x / 2 - (int)strlen(printText) / 2;

	Engine::Get().Draw(Vector2(cursorPositonX, 0), " _____  _      _____   ___  ______   _ ");
	Engine::Get().Draw(Vector2(cursorPositonX, 1), "/  __ \\| |    |  ___| / _ \\ | ___ \\ | |");
	Engine::Get().Draw(Vector2(cursorPositonX, 2), "| /  \\/| |    | |__  / /_\\ \\| |_/ / | |");
	Engine::Get().Draw(Vector2(cursorPositonX, 3), "| |    | |    |  __| |  _  ||    /  | |");
	Engine::Get().Draw(Vector2(cursorPositonX, 4), "| \\__/\\| |____| |___ | | | || |\\ \\  |_|");
	Engine::Get().Draw(Vector2(cursorPositonX, 5), " \\____/\\_____/\\____/ \\_| |_/\\_| \\_| (_)");

	int i = 0;
	for (int ix = 0; ix < menuItems.size(); ++ix)
	{
		Color setColor = (ix == currentIndex) ? selectedColor : unselectedColor;
		Engine::Get().Draw(Vector2(1, ix + 10 + i), "|");
		Engine::Get().Draw(Vector2(2, ix + 10 + i), menuItems[ix]->menuText, setColor);
		++i;
	}
}
