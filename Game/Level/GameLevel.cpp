#include "GameLevel.h"
#include "Engine/Engine.h"
#include "Game/Game.h"

#include "Actor/Block.h"
#include "Actor/Empty.h"
#include "Actor/Star.h"
#include "Actor/Player.h"

#include "Engine/Timer.h"

GameLevel::GameLevel(int stageIndex)
{
	// 커서 감추기.
	Engine::Get().SetCursorType(CursorType::NoCursor);

	// 맵 파일 불러와 레벨 로드.
	// 파일 읽기.

	//char fileName[256];
	//snprintf(fileName, 256, "../Assets/Maps/Stage%d.txt", stageIndex + 1);

	FILE* file = nullptr;
	fopen_s(&file, Game::Get().stageAdress[stageIndex], "rb");
	//fopen_s(&file, fileName, "rb");

	// 파일 처리.
	if (file == nullptr)
	{
		std::cout << "맵 파일 열기 실패.\n";
		__debugbreak();
		return;
	}

	// 파일 읽기.
	// 끝위치로 이동.
	fseek(file, 0, SEEK_END);

	// 이동한 위치의 FP 가져오기(전체 파일 크기).
	size_t readSize = ftell(file);

	// FP(file Position) 원위치.
	// fseek(file, 0, SEEK_SET); // 아래 코드와 같음.
	rewind(file);

	// 파일 읽어서 버퍼에 담기.
	char* buffer = new char[readSize + 1];
	size_t bytesRead = fread(buffer, 1, readSize, file);

	if (readSize != bytesRead)
	{
		std::cout << "읽어온 크기가 다름\n";
		__debugbreak();
		return;
	}

	buffer[readSize] = '\0';

	// 파일 읽을 때 사용할 인덱스.
	int index = 0;

	// 좌표 계산을 위한 변수 선언.
	int xPosition = 0;
	int yPosition = 0;

	// 해석(파싱-Parcing).
	while (index < (int)bytesRead)
	{
		// 한 문자씩 읽기.
		char mapChar = buffer[index++];

		// 개행 문자인 경우 처리.
		if (mapChar == '\n')
		{
			++yPosition;
			xPosition = 0;
			continue;
		}

		// 맵 문자가 1이면 block 액터 생성.
		if (mapChar == '1')
		{
			Block* block = new Block(Vector2(xPosition, yPosition));
			actors.PushBack(block);
			map.PushBack(block);
		}

		// 맵 문자가 .이면 그라운드 액터 생성.
		else if (mapChar == '.')
		{
			Empty* empty = new Empty(Vector2(xPosition, yPosition));
			actors.PushBack(empty);
			map.PushBack(empty);
		}

		// 맵 문자가 5이면 그라운드 액터 생성.
		else if (mapChar == '5')
		{
			// 스테이지에 존재하는 스타 개수 저장.
			++stageStarCount;

			Empty* empty = new Empty(Vector2(xPosition, yPosition));
			actors.PushBack(empty);
			map.PushBack(empty);

			Star* star = new Star(Vector2(xPosition, yPosition));
			actors.PushBack(star);
			//stars.PushBack(star);
		}

		// 맵 문자가 p이면 그라운드 액터 생성.
		else if (mapChar == 'p')
		{
			Empty* empty = new Empty(Vector2(xPosition, yPosition));
			actors.PushBack(empty);
			map.PushBack(empty);

			player = new Player(Vector2(xPosition, yPosition), this);
			actors.PushBack(player);
		}

		++xPosition;
	}

	// 버퍼 삭제.
	delete[] buffer;

	// 파일 닫기.
	fclose(file);
}

void GameLevel::Update(float deltaTime)
{
	// 제거된 star을 제외하고 남은 star들을 stars에 푸쉬
	stars.Clear();
	for (Actor* actor : actors)
	{
		Star* star = actor->As<Star>();
		if (star)
		{
			stars.PushBack(star);
		}
	}

	// 게임이 클리어 되었는지 확인.
	CheckGameClear();

	Super::Update(deltaTime);


	// 게임이 클리어 됐으면, 게임 종료 처리.
	if (isGameClear)
	{
		// 대략 한 프레임 정도의 시간 대기.
		static Timer timer(0.1f);
		timer.Update(deltaTime);
		if (!timer.IsTimeOut())
		{
			return;
		}

		const char* gameClearText = "GameClear!";
		size_t gameClearTextLength = strlen(gameClearText);

		// 커서 이동.
		Engine::Get().SetCursorPosition(Engine::Get().ScreenSize().x / 2 - (int)gameClearTextLength / 2, Engine::Get().ScreenSize().y/2 - 4);

		// 메시지 출력.
		Log("GameClear!");

		// 쓰레드 정지.
		Sleep(2000);

		// Level 전환.
		Game::Get().ToggleGameClearMenu();
	}
}

void GameLevel::Draw()
{
	// 덮어 쓸거라 Super을 하면안됨.
	// 맵 그리기.

	for (auto* actor : map)
	{
		// 플레이어 위치 확인.
		if (actor->Position() == player->Position()) continue;

		// 스타가 있으면 Draw그리지 않게하는 변수.
		bool isStar = false;
		for (auto* star : stars)
		{
			if (actor->Position() == star->Position())
			{
				isStar = true;
				break;
			}
		}

		if (isStar) continue;
		
		// 맵 액터 그리기.
		actor->Draw();
	}

	// 스타 그리기.
	for (auto* star : stars)
	{
		// 플레이어 위치 확인.
		if (star->Position() == player->Position()) continue;

		star->Draw();
	}

	// 플레이어 그리기.
	player->Draw();
}

bool GameLevel::CanPlayerMove(const Vector2& position)
{
	// 게임이 클리어된 경우 바로 종료.
	if (isGameClear)
	{
		return false;
	}

	//for (Star* star : stars)
	for (int ix = 0; ix < stars.Size(); ++ix)
	{
		Star* star = stars[ix];

		// 검색한 액터가 star인지 확인.
		if (star->Position() == position)
		{
			// Star라면 스타를 스타를 획득 후 제거.
			star->Destroy();
			++starCount;
			
			return true;
		}
	}

	// 이동하려는 위치에 벽이 있는지 확인.
	DrawableActor* searchedActor = nullptr;

	// 먼저 이동하려는 위치의 액터 찾기.
	for (auto* actor : map)
	{
		if (actor->Position() == position)
		{
			searchedActor = actor;
			break;
		}
	}

	// 검색 가능한 액터가 존재하는지 확인.
	if (searchedActor)
	{
		// 검색한 액터가 벽인지 확인.
		if (searchedActor->As<Block>())
		{
			return false;
		}

		// 검색한 액터가 이동가능한 빈칸이면 이동,,.
		if (searchedActor->As<Empty>())
		{
			return true;
		}
	}
}

bool GameLevel::CheckGameClear()
{
	// 스타를 다 모았으면 게임 클리어.
	if (starCount == stageStarCount)
	{
		isGameClear = true;
	}
	return false;
}
