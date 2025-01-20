#include "MenuLevel.h"
#include "Game/Game.h"
#include "Level/GameLevel.h"

MenuLevel::MenuLevel()
{
	// Ŀ�� ���߱�.
	Engine::Get().SetCursorType(CursorType::NoCursor);

	menuItems.emplace_back(new MenuItem("Stage1", []()
		{
			if(Game::Get().GetStageIndex() != (int)StageType::Stage1)
			{
				// �ش� ���������� �ε�Ǿ� ���������� �ε�.
				Game::Get().LoadLevel(new GameLevel((int)StageType::Stage1));
			}
			else
			{
				// ���� ���������� �̹� �ε�Ǿ� �ִٸ� ToggleMenu()������ 
				// �̿��� mainLevel�� backLevel�� �ٲ��ֱ�.
				Game::Get().ToggleMenu();
			}
			// �������� �ε��� ������ Game Ŭ������ ����.
			Game::Get().SetStageIndex((int)StageType::Stage1);
		}));
	menuItems.emplace_back(new MenuItem("Stage2", []()
		{
			if (Game::Get().GetStageIndex() != (int)StageType::Stage2)
			{
				// �ش� ���������� �ε�Ǿ� ���������� �ε�.
				Game::Get().LoadLevel(new GameLevel((int)StageType::Stage2));
			}
			else
			{
				// ���� ���������� �̹� �ε�Ǿ� �ִٸ� ToggleMenu()������ 
				// �̿��� mainLevel�� backLevel�� �ٲ��ֱ�.
				Game::Get().ToggleMenu();
			}
			// �������� �ε��� ������ Game Ŭ������ ����.
			Game::Get().SetStageIndex((int)StageType::Stage2);
		}));
	menuItems.emplace_back(new MenuItem("Stage3", []()
		{
			if (Game::Get().GetStageIndex() != (int)StageType::Stage3)
			{
				// �ش� ���������� �ε�Ǿ� ���������� �ε�.
				Game::Get().LoadLevel(new GameLevel((int)StageType::Stage3));
			}
			else
			{
				// ���� ���������� �̹� �ε�Ǿ� �ִٸ� ToggleMenu()������ 
				// �̿��� mainLevel�� backLevel�� �ٲ��ֱ�.
				Game::Get().ToggleMenu();
			}
			// �������� �ε��� ������ Game Ŭ������ ����.
			Game::Get().SetStageIndex((int)StageType::Stage3);
		}));
	menuItems.emplace_back(new MenuItem("Quit Game", []() { Game::Get().QuitGame(); }));
	length = (int)menuItems.size();
}

MenuLevel::~MenuLevel()
{
	for (auto* item : menuItems)
	{
		delete item;
	}
}

void MenuLevel::Update(float deltaTime)
{
	if (Game::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleMenu();
	}

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

void MenuLevel::Draw()
{
	Super::Draw();

	// ��� �� ��ġ.
	const char* printText = "BounceBall";
	Vector2 cursorPositon(Engine::Get().ScreenSize().x / 2 - (int)strlen(printText) / 2, 0);
	Engine::Get().Draw(cursorPositon, printText);

	for (int ix = 0; ix < menuItems.size(); ++ix)
	{
		Color setColor = (ix == currentIndex) ? selectedColor : unselectedColor;
		Engine::Get().Draw(Vector2(2, ix+3), menuItems[ix]->menuText, setColor);
	}
}