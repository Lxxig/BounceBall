#include "GameOverMenuLevel.h"
#include "Game/Game.h"
#include "Level/MenuLevel.h"
#include "Level/GameLevel.h"

GameOverMenuLevel::GameOverMenuLevel()
{
	// 커서 감추기.
	Engine::Get().SetCursorType(CursorType::NoCursor);

	menuItems.emplace_back(new MenuItem("ReGame", []() {
		// 기존 스테이지를 재할당.
		Game::Get().LoadLevel(new GameLevel(Game::Get().GetStageIndex()));
		// 스테이지 인덱스 정보 저장.
		Game::Get().SetStageIndex(Game::Get().GetStageIndex());
		}));

	// 메뉴로 돌아가기.
	menuItems.emplace_back(new MenuItem("Menu", []() {
		Game::Get().LoadLevel(new MenuLevel());
		}));

	// 게임 종료.
	menuItems.emplace_back(new MenuItem("QuitGame", []() {
		Game::Get().QuitGame();
		}));

	// 메뉴 선택지 개수 저장.
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

	// 출력 될 위치.
	const char* printText = "GameOverMenu";
	Vector2 cursorPositon(Engine::Get().ScreenSize().x / 2 - (int)strlen(printText) / 2, 0);
	Engine::Get().Draw(cursorPositon, printText);

	int i = 0;
	for (int ix = 0; ix < menuItems.size(); ++ix)
	{
		//SetColor(ix == currentIndex ? selectedColor : unselectedColor);
		Color setColor = (ix == currentIndex) ? selectedColor : unselectedColor;
		Engine::Get().Draw(Vector2(2, ix + 3 + i), menuItems[ix]->menuText, setColor);
		++i;
	}
}
