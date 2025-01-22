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
		// stageIndex = -1;을 해주지 않으면 게임오버레벨 -> 메뉴 에서
		// 기존의 레벨을 다시플레이 하지 못한다.
		Game::Get().SetStageIndex(-1);
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
