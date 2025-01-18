#include "MenuLevel.h"
#include "Game/Game.h"
#include "Level/GameLevel.h"

MenuLevel::MenuLevel()
{
	menuItems.PushBack(new MenuItem("Stage1", []()
		{
			// 삭제될 Game클래스의 메뉴 레벨을 nullptr로 설정.
			Game::Get().SetMenuLvelToNullptr();

			if(Game::Get().GetStageIndex() != (int)StageType::Stage1)
			{
				// 해당 스테이지가 로드되어 있지않으면 로드.
				Game::Get().LoadLevel(new GameLevel((int)StageType::Stage1));
			}
			else
			{
				// 같은 스테이지가 이미 로드되어 있다면 ToggleMenu()로직을 
				// 이용해 mainLevel과 backLevel을 바꿔주기.
				Game::Get().ToggleMenu();
			}
			// 스테이지 인덱스 정보를 Game 클래스에 저장.
			Game::Get().SetStageIndex((int)StageType::Stage1);
		}));
	menuItems.PushBack(new MenuItem("Stage2", []()
		{
			// 삭제될 Game클래스의 메뉴 레벨을 nullptr로 설정.
			Game::Get().SetMenuLvelToNullptr();

			if (Game::Get().GetStageIndex() != (int)StageType::Stage2)
			{
				// 해당 스테이지가 로드되어 있지않으면 로드.
				Game::Get().LoadLevel(new GameLevel((int)StageType::Stage2));
			}
			else
			{
				// 같은 스테이지가 이미 로드되어 있다면 ToggleMenu()로직을 
				// 이용해 mainLevel과 backLevel을 바꿔주기.
				Game::Get().ToggleMenu();
			}
			// 스테이지 인덱스 정보를 Game 클래스에 저장.
			Game::Get().SetStageIndex((int)StageType::Stage2);
		}));
	menuItems.PushBack(new MenuItem("Stage3", []()
		{
			// 삭제될 Game클래스의 메뉴 레벨을 nullptr로 설정.
			Game::Get().SetMenuLvelToNullptr();

			if (Game::Get().GetStageIndex() != (int)StageType::Stage3)
			{
				// 해당 스테이지가 로드되어 있지않으면 로드.
				Game::Get().LoadLevel(new GameLevel((int)StageType::Stage3));
			}
			else
			{
				// 같은 스테이지가 이미 로드되어 있다면 ToggleMenu()로직을 
				// 이용해 mainLevel과 backLevel을 바꿔주기.
				Game::Get().ToggleMenu();
			}
			// 스테이지 인덱스 정보를 Game 클래스에 저장.
			Game::Get().SetStageIndex((int)StageType::Stage3);
		}));
	menuItems.PushBack(new MenuItem("Quit Game", []() { Game::Get().QuitGame(); }));
	length = menuItems.Size();
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

	Engine::Get().SetCursorPosition(0, 0);
	
	SetColor(unselectedColor);
	Log("BounceBall Game\n\n");

	for (int ix = 0; ix < length; ++ix)
	{
		SetColor(ix == currentIndex ? selectedColor : unselectedColor);
		Log("%s\n", menuItems[ix]->menuText);
	}
}