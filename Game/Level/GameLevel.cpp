#include "GameLevel.h"
#include "Engine/Engine.h"
#include "Game/Game.h"

#include "Actor/Empty.h"
#include "Actor/Block.h"
#include "Actor/ThornBlock.h"
#include "Actor/ExtinctionBlock.h"
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

		// 블럭
		// .: Empty
		// 0: ThornBlock
		// 1: Block
		// e: ExtinctionBlock
		// 
		// 아이템.
		// 2: DoubleJump
		// 5: Star

		// 제거 처리를 해야하는 actor의 경우 메모리 관리를 추가로 해줘야 하기때문에
		// map에는 포함시키지 않는다.
		// map에는 메모리 관리를 해 줄 필요가 없는 액터들만 추가한다.

		// 맵 문자가 1이면 block 액터 생성.
		if (mapChar == '1')
		{
			Block* block = new Block(Vector2(xPosition, yPosition));
			actors.emplace_back(block);
			map.emplace_back(block);
		}

		// 맵 문자가 0이면 ThornBlock 액터 생성.
		if (mapChar == '0')
		{
			ThornBlock* thornBlock = new ThornBlock(Vector2(xPosition, yPosition));
			actors.emplace_back(thornBlock);
			map.emplace_back(thornBlock);
		}

		// 맵 문자가 .이면 empty 액터 생성.
		//else if (mapChar == '.')
		//{
		//	/*Empty* empty = new Empty(Vector2(xPosition, yPosition));
		//	actors.emplace_back(empty);
		//	map.emplace_back(empty);*/
		//}

		// 맵 문자가 e이면 ExtinctionBlock 액터 생성.
		if (mapChar == 'e')
		{
			ExtinctionBlock* extinctionBlock = new ExtinctionBlock(Vector2(xPosition, yPosition));
			extinctionBlocks.emplace_back(extinctionBlock);
			actors.emplace_back(extinctionBlock);
		}

		// 맵 문자가 5이면 star 액터 생성.
		else if (mapChar == '5')
		{
			// 스테이지에 존재하는 스타 개수 저장.
			++stageStarCount;

			Star* star = new Star(Vector2(xPosition, yPosition));
			stars.push_back(star);
			actors.emplace_back(star);
		}

		// 맵 문자가 p이면 player 액터 생성.
		else if (mapChar == 'p')
		{
			player = new Player(Vector2(xPosition, yPosition), this);
			actors.emplace_back(player);
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
	// 게임 오버 됐는지 확인.
	CheckGameOver();

	// 게임이 클리어 되었는지 확인.
	CheckGameClear();

	Super::Update(deltaTime);


	// 게임이 클리어 됐으면, 게임 클리어 메뉴에서 선택.
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
		Vector2 cursorPosition(Engine::Get().ScreenSize().x / 2 - (int)gameClearTextLength / 2, Engine::Get().ScreenSize().y / 2 - 4);

		// 메시지 출력.
		Engine::Get().Draw(cursorPosition, gameClearText);

		// 쓰레드 정지.
		Sleep(2000);

		// Level 전환.
		Game::Get().ToggleGameClearOrOverMenu();
		isGameOver = false;
	}

	if (isGameOver)
	{
		// 대략 한 프레임 정도의 시간 대기.
		static Timer timer(0.1f);
		timer.Update(deltaTime);
		if (!timer.IsTimeOut())
		{
			return;
		}

		const char* GameOverText = "GameClear!";
		size_t GameOverTextLength = strlen(GameOverText);

		// 커서 이동.
		Vector2 cursorPosition(Engine::Get().ScreenSize().x / 2 - (int)GameOverTextLength / 2, Engine::Get().ScreenSize().y / 2 - 4);

		// 메시지 출력.
		Engine::Get().Draw(cursorPosition, GameOverText);

		// 쓰레드 정지.
		Sleep(2000);

		// Level 전환.
		Game::Get().ToggleGameClearOrOverMenu();
	}
}

void GameLevel::Draw()
{
	// 해당 스테이지 출력.
	char StageName[10];
	snprintf(StageName, 10, "Stage%d", stageIndex + 1);
	Vector2 cursorPositon(Engine::Get().ScreenSize().x / 2 - (int)strlen(StageName) / 2, 0);
	Engine::Get().Draw(cursorPositon, StageName);

	for (auto* actor : actors)
	{
		actor->Draw();
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

	// 스타 획득 로직.
	for (auto it = stars.begin(); it!=stars.end(); ++it)
	{
		// 플레이어의 다음 위치가 star면 스타를 제거.
		if ((*it)->Position() == position)
		{
			// 메모리 해제.
			(*it)->Destroy();
			// stars벡터 내부에서 해제된 노드(요소)를 제거.
			it = stars.erase(it);

			++starCount;

			return true;
		}
	}

	// ExtinctionBlock 부서지는 로직.
	for (auto it = extinctionBlocks.begin(); it != extinctionBlocks.end(); ++ it)
	{
		if ((*it)->Position() == position)
		{
			if (prePosition.y < position.y && prePosition.x == position.x)
			{
				// 메모리 해제.
				(*it)->Destroy();

				// stars벡터 내부에서 해제된 노드(요소)를 제거.
				it = extinctionBlocks.erase(it);

			}

			return false;
		}
	}

	prePosition = Vector2(position);

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
		// 검색한 액터가 ThornBlock인지 확인.
		if (searchedActor->As<ThornBlock>())
		{
			isGameOver = true;
			return false;
		}

		// 검색한 액터가 Block지 확인.
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
		return true;
	}
	return isGameClear;
}

bool GameLevel::CheckGameOver()
{
	if (player->Position().y >= Game::Get().ScreenSize().y - 1 && isGameClear != true)
	{
		isGameOver = true;
		return true;
	}
	return isGameOver;
}
