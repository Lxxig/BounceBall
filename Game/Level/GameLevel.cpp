#include "GameLevel.h"
#include "Engine/Engine.h"
#include "Game/Game.h"

#include "Actor/Block.h"
#include "Actor/MoveBlock.h"
#include "Actor/TargetBlock.h"
#include "Actor/JumpBlock.h"
#include "Actor/BlinkerBlock.h"
#include "Actor/ThornBlock.h"
#include "Actor/BlinkerThornBlock.h"
#include "Actor/ExtinctionBlock.h"
#include "Actor/Star.h"
#include "Actor/Player.h"

#include "Engine/Timer.h"

// ����
//#include <windows.h>
#pragma comment(lib, "winmm.lib")

GameLevel::GameLevel(int stageIndex)
{	
	// Ŀ�� ���߱�.
	Engine::Get().SetCursorType(CursorType::NoCursor);

	// bgm ���� �ݺ� ����ϱ�.
	auto error = mciSendString(TEXT("play bgm repeat"), NULL, 0, NULL);
	if (error)
	{
		char erorrMessage[256] = { };
		sprintf_s(erorrMessage, 256, "ErrorCode: %d\n", error);
		OutputDebugStringA(erorrMessage);
	}
	mciSendString(TEXT("setaudio bgm volume to 500"), NULL, 0, NULL);

	this->stageIndex = stageIndex;

	// �� ���� �ҷ��� ���� �ε�.
	// ���� �б�.

	//char fileName[256];
	//snprintf(fileName, 256, "../Assets/Maps/Stage%d.txt", stageIndex + 1);

	FILE* file = nullptr;
	fopen_s(&file, Game::Get().stageAdress[stageIndex], "rb");
	//fopen_s(&file, fileName, "rb");

	// ���� ó��.
	if (file == nullptr)
	{
		std::cout << "�� ���� ���� ����.\n";
		__debugbreak();
		return;
	}

	// ���� �б�.
	// ����ġ�� �̵�.
	fseek(file, 0, SEEK_END);

	// �̵��� ��ġ�� FP ��������(��ü ���� ũ��).
	size_t readSize = ftell(file);

	// FP(file Position) ����ġ.
	// fseek(file, 0, SEEK_SET); // �Ʒ� �ڵ�� ����.
	rewind(file);

	// ���� �о ���ۿ� ���.
	char* buffer = new char[readSize + 1];
	size_t bytesRead = fread(buffer, 1, readSize, file);

	if (readSize != bytesRead)
	{
		std::cout << "�о�� ũ�Ⱑ �ٸ�\n";
		__debugbreak();
		return;
	}

	buffer[readSize] = '\0';

	// ���� ���� �� ����� �ε���.
	int index = 0;

	// ��ǥ ����� ���� ���� ����.
	int xPosition = 0;
	int yPosition = 0;

	// �ؼ�(�Ľ�-Parcing).
	while (index < (int)bytesRead)
	{
		// �� ���ھ� �б�.
		char mapChar = buffer[index++];

		// ���� ������ ��� ó��.
		if (mapChar == '\n')
		{
			++yPosition;
			xPosition = 0;
			continue;
		}

		// ��.
		// .: 
		// 0: ThornBlock ���� ��.
		// 1: Block.
		// e: ExtinctionBlock ������ �μ����� ��(�Ҹ� ��).
		// j: JumpBlock ���� ��ȭ.
		// t: TargetBlock , t���̿� �ִ� ������ ���� ���� �ȴ�.
		// k: BlinkerBlock, �����̴� ��.
		// K: BlinkerThornBlock, �����̴� ���� ��.
		// 
		// ������.
		// 5: Star.

		// ���� ó���� �ؾ��ϴ� actor�� ��� �޸� ������ �߰��� ����� �ϱ⶧����
		// map���� ���Խ�Ű�� �ʴ´�.
		// map���� �޸� ������ �� �� �ʿ䰡 ���� ���͵鸸 �߰��Ѵ�.


		// �� ���ڰ� t�̸� TargetBlock���� ����.
		if (mapChar == 't')
		{
			TargetBlock* targetBlock = new TargetBlock(Vector2(xPosition, yPosition));
			actors.emplace_back(targetBlock);
			map.emplace_back(targetBlock);

			// �� ���ڰ� t�̸� makeMoveBlock�� ���¸� �����Ѵ�.
			makeMoveBlock = !makeMoveBlock;

			if (makeMoveBlock)
			{
				if (moveBlock == nullptr)
				{
					// ����� ���� ����.
					moveBlock = new MoveBlock(Vector2(xPosition + 1, yPosition), this);
				}
				// ���� �� ���� ����.
				++MoveBlockCount;
			}
			else
			{
				// ������� ũ�Ⱑ 1 block �̻��̸� moveBlocks�� ����
				if (moveBlock == nullptr || moveBlock->GetBlockSize())
				{
					moveBlocks.emplace_back(moveBlock);
					actors.emplace_back(moveBlock);
					moveBlock = nullptr;
				}
			}
		}

		// �� ���ڰ� 1�̸� block ���� ����.
		if (mapChar == '1')
		{
			Block* block = new Block(Vector2(xPosition, yPosition));
			if (makeMoveBlock)
			{
				// moveBlockTargetPosition���̿� �ִ� ������ ��Ƽ� ����� �����.
				// t 111     t  -> �� 3��¥�� ���� ���� ���������.
				moveBlock->SetMoveBlock(block);
			}

			actors.emplace_back(block);
			map.emplace_back(block);
		}

		// �� ���ڰ� j�̸� JumpBlock ���� ����.
		if (mapChar == 'j')
		{
			JumpBlock* jumpBlock = new JumpBlock(Vector2(xPosition, yPosition));
			actors.emplace_back(jumpBlock);
			map.emplace_back(jumpBlock);
		}

		// �� ���ڰ� k�̸� JumpBlock ���� ����.
		if (mapChar == 'k')
		{
			BlinkerBlock* blinkerBlock = new BlinkerBlock(Vector2(xPosition, yPosition));
			actors.emplace_back(blinkerBlock);
			map.emplace_back(blinkerBlock);
		}

		// �� ���ڰ� K�̸� JumpBlock ���� ����.
		if (mapChar == 'K')
		{
			BlinkerThornBlock* blinkerThornBlock = new BlinkerThornBlock(Vector2(xPosition, yPosition));
			actors.emplace_back(blinkerThornBlock);
			map.emplace_back(blinkerThornBlock);
		}

		// �� ���ڰ� 0�̸� ThornBlock ���� ����.
		if (mapChar == '0')
		{
			ThornBlock* thornBlock = new ThornBlock(Vector2(xPosition, yPosition));
			actors.emplace_back(thornBlock);
			map.emplace_back(thornBlock);
		}

		// �� ���ڰ� e�̸� ExtinctionBlock ���� ����.
		if (mapChar == 'e')
		{
			ExtinctionBlock* extinctionBlock = new ExtinctionBlock(Vector2(xPosition, yPosition));
			extinctionBlocks.emplace_back(extinctionBlock);
			actors.emplace_back(extinctionBlock);
		}

		// �� ���ڰ� 5�̸� star ���� ����.
		else if (mapChar == '5')
		{
			// ���������� �����ϴ� ��Ÿ ���� ����.
			++stageStarCount;

			Star* star = new Star(Vector2(xPosition, yPosition));
			stars.push_back(star);
			actors.emplace_back(star);
		}

		// �� ���ڰ� p�̸� player ���� ����.
		else if (mapChar == 'p')
		{
			player = new Player(Vector2(xPosition, yPosition), this);
			actors.emplace_back(player);
		}

		++xPosition;
	}

	// ���� ����.
	delete[] buffer;

	// ���� �ݱ�.
	fclose(file);
}

void GameLevel::Update(float deltaTime)
{
	// ���� ���� �ƴ��� Ȯ��.
	CheckGameOver();

	// ������ Ŭ���� �Ǿ����� Ȯ��.
	CheckGameClear();

	Super::Update(deltaTime);

	// ������ Ŭ���� ������, ���� Ŭ���� �޴����� ����.
	if (isGameClear)
	{
		// ������ ����.
		Sleep(500);

		// bgm ���߱�.
		mciSendString(TEXT("stop bgm"), NULL, 0, NULL);

		// gameOverSound ���� �о� ����
		mciSendString(TEXT("open \"../Assets/Sounds/GameClearSound.mp3\" type mpegvideo alias gameClearSound"), NULL, 0, NULL);
		// gameOverSound �÷���(�� ����).
		mciSendString(TEXT("play gameClearSound from 0"), NULL, 0, NULL);
		// ���� �Ҹ� ����.
		mciSendString(TEXT("setaudio gameClearSound volume to 500"), NULL, 0, NULL);

		// Level ��ȯ.
		Game::Get().ToggleGameClearOrOverMenu();
		isGameOver = false;
	}

	if (isGameOver)
	{
		// ������ ����.
		Sleep(500);

		// bgm ���߱�.
		mciSendString(TEXT("stop bgm"), NULL, 0, NULL);

		// gameOverSound ���� �о� ����
		mciSendString(TEXT("open \"../Assets/Sounds/GameOverSound.mp3\" type mpegvideo alias gameOverSound"), NULL, 0, NULL);
		// gameOverSound �÷���(�� ����).
		mciSendString(TEXT("play gameOverSound from 0"), NULL, 0, NULL);
		// ���� �Ҹ� ����.
		mciSendString(TEXT("setaudio gameOverSound volume to 500"), NULL, 0, NULL);

		// Level ��ȯ.
		Game::Get().ToggleGameClearOrOverMenu();
	}
}

void GameLevel::Draw()
{
	// �ش� �������� ���.
	char StageName[10];
	snprintf(StageName, 10, "STAGE-%d", stageIndex + 1);
	Vector2 cursorPositon(Engine::Get().ScreenSize().x / 2 - (int)strlen(StageName) / 2, 0);
	Engine::Get().Draw(cursorPositon, StageName);

	char StarState[15];
	snprintf(StarState, 15, "STAR %d / %d", starCount, stageStarCount);
	cursorPositon = Vector2(1, 1);
	Engine::Get().Draw(cursorPositon, StarState);

	for (auto* actor : actors)
	{
		actor->Draw();
	}

	// �÷��̾� �׸���.
	player->Draw();
}

bool GameLevel::CanPlayerMove(const Vector2& position)
{
	// ������ Ŭ����� ��� �ٷ� ����.
	if (isGameClear)
	{
		return false;
	}

	// ��Ÿ ȹ�� ����.
	for (auto it = stars.begin(); it != stars.end(); ++it)
	{
		// �÷��̾��� ���� ��ġ�� star�� ��Ÿ�� ����.
		if ((*it)->Position() == position)
		{
			// �޸� ����.
			(*it)->Destroy();
			// stars���� ���ο��� ������ ���(���)�� ����.

			it = stars.erase(it);

			++starCount;

			// ObtainStarSound ���� �о����.
			mciSendString(TEXT("open \"../Assets/Sounds/ObtainStarSounnd.mp3\" type mpegvideo alias obtainStarSounnd"), NULL, 0, NULL);
			// ObtainStarSound �÷���(�� ����).
			mciSendString(TEXT("play obtainStarSounnd from 0"), NULL, 0, NULL);

			// ���� �Ҹ� ����.
			mciSendString(TEXT("setaudio obtainStarSounnd volume to 500"), NULL, 0, NULL);

			return true;
		}
	}

	// ExtinctionBlock �μ����� ����.
	for (auto it = extinctionBlocks.begin(); it != extinctionBlocks.end(); ++it)
	{
		if ((*it)->Position() == position)
		{
			if (prePosition.y < position.y && prePosition.x == position.x)
			{
				// �޸� ����.
				(*it)->Destroy();

				// stars���� ���ο��� ������ ���(���)�� ����.
				it = extinctionBlocks.erase(it);

			}

			return false;
		}
	}

	prePosition = Vector2(position);

	// �̵��Ϸ��� ��ġ�� ���� �ִ��� Ȯ��.
	DrawableActor* searchedActor = nullptr;

	// ���� �̵��Ϸ��� ��ġ�� ���� ã��.
	for (auto* actor : map)
	{
		if (actor->Position() == position)
		{
			searchedActor = actor;
			break;
		}
	}

	// �˻� ������ ���Ͱ� �����ϴ��� Ȯ��.
	if (searchedActor)
	{
		// �˻��� ���Ͱ� ThornBlock���� Ȯ��.
		if (searchedActor->As<ThornBlock>())
		{
			isGameOver = true;
			return false;
		}

		// �˻��� ���Ͱ� BlinkerThornBlock���� Ȯ��.
		if (searchedActor->As<BlinkerThornBlock>())
		{
			// BlinkerThornBlock�� Ȱ��ȭ �������� Ȯ��.
			if (searchedActor->As<BlinkerThornBlock>()->isShowedThornBlock())
			{
				isGameOver = true;
				return false;
			}
			else
			{
				return true;
			}
		}

		// �˻��� ���Ͱ� JumpBlock���� Ȯ��.
		if (searchedActor->As<JumpBlock>())
		{
			// ���� ���̸� �ι� ������ ����.
			player->SetCurrentMaxBallUpCount(5);
			return false;
		}

		// �˻��� ���Ͱ� BlinkerBlock���� Ȯ��.
		if (searchedActor->As<BlinkerBlock>())
		{
			// BlinkerBlock�� Ȱ��ȭ �������� Ȯ��.
			if (searchedActor->As<BlinkerBlock>()->isShowedBlock())
			{
				return false;
			}
			else
			{
				return true;
			}
		}

		// �˻��� ���Ͱ� Block�� Ȯ��.
		if (searchedActor->As<Block>())
		{
			return false;
		}
	}

	// ��ĭ�̸�.
	return true;
}

bool GameLevel::CanMoveBlock(const Vector2& position)
{
	// ������ Ŭ����� ��� �ٷ� ����.
	if (isGameClear)
	{
		return false;
	}

	// �̵��Ϸ��� ��ġ�� t�� �ִ��� Ȯ��.
	DrawableActor* searchedActor = nullptr;
	for (auto* actor : map)
	{
		if (actor->Position() == position)
		{
			searchedActor = actor;
		}
	}

	if (searchedActor != nullptr)
	{
		if (searchedActor->As<TargetBlock>())
		{
			return false;
		}
	}
	return true;
}

bool GameLevel::CheckGameClear()
{
	// ��Ÿ�� �� ������� ���� Ŭ����.
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