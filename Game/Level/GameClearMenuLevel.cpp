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
			// ���ư� �� ���� ��� ����.
			//Engine::Get().Clear;
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
	const char* printText = "GameClearMenu";
	Vector2 cursorPositon(Engine::Get().ScreenSize().x / 2 - (int)strlen(printText) / 2, 0);
	Engine::Get().Draw(cursorPositon, printText);

	for (int ix = 0; ix < menuItems.size(); ++ix)
	{
		//SetColor(ix == currentIndex ? selectedColor : unselectedColor);
		Color setColor = (ix == currentIndex) ? selectedColor : unselectedColor;
		Engine::Get().Draw(Vector2(2, ix + 3), menuItems[ix]->menuText, setColor);
	}
}
