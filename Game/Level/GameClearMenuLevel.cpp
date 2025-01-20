#include "GameClearMenuLevel.h"
#include "Game/Game.h"
#include "Level/MenuLevel.h"
#include "Level/GameLevel.h"

GameClearMenuLvel::GameClearMenuLvel()
{
	// 커서 감추기.
	Engine::Get().SetCursorType(CursorType::NoCursor);

	// 클리어할 다음 스테이지가 존재할 경우.
	if (Game::Get().GetStageIndex() + 1 < Game::Get().stageAdress.size())
	{
		// 다음 스테이지로 이동.
		menuItems.emplace_back(new MenuItem("Next Stage!", []() {
			// 다음 스테이지 로드.
			Game::Get().LoadLevel(new GameLevel(Game::Get().GetStageIndex() + 1));
			// 다음 스테이지 인데스 정보를 Game 클래스에 전달.
			Game::Get().SetStageIndex(Game::Get().GetStageIndex() + 1);
			}));

		// 메뉴로 돌아가기.
		menuItems.emplace_back(new MenuItem("Menu", []() {
			// 돌아갈 때 남는 찌꺼기 제거.
			//Engine::Get().Clear;
			Game::Get().LoadLevel(new MenuLevel());
			}));

		menuItems.emplace_back(new MenuItem("QuitGame", []() {
			Game::Get().QuitGame();
			}));
	}

	// 모든 스테이지를 다 클리어한 경우.
	else if (Game::Get().GetStageIndex() + 1 >= Game::Get().stageAdress.size())
	{
		// 메뉴로 돌아가기.
		menuItems.emplace_back(new MenuItem("Menu (Clear all stages)", []() {
			Game::Get().LoadLevel(new MenuLevel());
			}));

		menuItems.emplace_back(new MenuItem("QuitGame", []() {
			Game::Get().QuitGame();
			}));

	}

	// 메뉴 선택지 개수 저장.
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

	// 출력 될 위치.
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
