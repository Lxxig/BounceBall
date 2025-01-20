#include "GameLevel.h"
#include "Engine/Engine.h"
#include "Game/Game.h"

#include "Actor/Empty.h"
#include "Actor/Block.h"
#include "Actor/MoveBlock.h"
#include "Actor/ThornBlock.h"
#include "Actor/ExtinctionBlock.h"
#include "Actor/Star.h"
#include "Actor/Player.h"

#include "Engine/Timer.h"

GameLevel::GameLevel(int stageIndex)
{
	// Ŀ�� ���߱�.
	Engine::Get().SetCursorType(CursorType::NoCursor);

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

		// ��
		// .: Empty
		// 0: ThornBlock
		// 1: Block
		// e: ExtinctionBlock
		// 
		// ������.
		// 2: DoubleJump
		// 5: Star

		// ���� ó���� �ؾ��ϴ� actor�� ��� �޸� ������ �߰��� ����� �ϱ⶧����
		// map���� ���Խ�Ű�� �ʴ´�.
		// map���� �޸� ������ �� �� �ʿ䰡 ���� ���͵鸸 �߰��Ѵ�.


		// �� ���ڰ� t�̸� MoveBlockStartPosition�� targetPosition�� ���� ����.
		if (mapChar == 't')
		{
			// �� ���ڰ� t�̸� makeMoveBlock�� ���¸� �����Ѵ�.
			makeMoveBlock = !makeMoveBlock;

			if (makeMoveBlock)
			{
				// t�� �������� ����.
				moveBlockTargetPosition.push_back(Vector2(xPosition, yPosition));

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
			//else
			//{
			//	// ������� ũ�Ⱑ 1 block �̻��̸� moveBlocks�� ����
			//	if (moveBlock == nullptr || moveBlock->GetBlockSize())
			//	{
			//		moveBlocks.emplace_back(moveBlock);
			//		//actors.emplace_back(moveBlock);
			//		moveBlock = nullptr;
			//	}
			//}

			actors.emplace_back(block);
			map.emplace_back(block);
		}

		// �� ���ڰ� 0�̸� ThornBlock ���� ����.
		if (mapChar == '0')
		{
			ThornBlock* thornBlock = new ThornBlock(Vector2(xPosition, yPosition));
			actors.emplace_back(thornBlock);
			map.emplace_back(thornBlock);
		}

		// �� ���ڰ� .�̸� empty ���� ����.
		//else if (mapChar == '.')
		//{
		//	/*Empty* empty = new Empty(Vector2(xPosition, yPosition));
		//	actors.emplace_back(empty);
		//	map.emplace_back(empty);*/
		//}

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

	for (auto* block : moveBlocks)
	{
		block->Update(deltaTime);
	}


	// ������ Ŭ���� ������, ���� Ŭ���� �޴����� ����.
	if (isGameClear)
	{
		// �뷫 �� ������ ������ �ð� ���.
		static Timer timer(0.1f);
		timer.Update(deltaTime);
		if (!timer.IsTimeOut())
		{
			return;
		}

		const char* gameClearText = "GameClear!";
		size_t gameClearTextLength = strlen(gameClearText);

		// Ŀ�� �̵�.
		//Engine::Get().ScreenSize().y / 2 - 4
		Vector2 cursorPosition(Engine::Get().ScreenSize().x / 2 - (int)gameClearTextLength / 2, Engine::Get().ScreenSize().y / 2 - 4);

		// �޽��� ���.
		Engine::Get().Draw(cursorPosition, gameClearText);

		// ������ ����.
		Sleep(2000);

		// Level ��ȯ.
		Game::Get().ToggleGameClearOrOverMenu();
		isGameOver = false;
	}

	if (isGameOver)
	{
		// �뷫 �� ������ ������ �ð� ���.
		static Timer timer(0.1f);
		timer.Update(deltaTime);
		if (!timer.IsTimeOut())
		{
			return;
		}

		const char* GameOverText = "GameOver!";
		size_t GameOverTextLength = strlen(GameOverText);

		// Ŀ�� �̵�.
		Vector2 cursorPosition(Engine::Get().ScreenSize().x / 2 - (int)GameOverTextLength / 2, Engine::Get().ScreenSize().y / 2 - 4);

		// �޽��� ���.
		Engine::Get().Draw(cursorPosition, GameOverText);

		// ������ ����.
		Sleep(2000);

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

		// �˻��� ���Ͱ� Block�� Ȯ��.
		if (searchedActor->As<Block>())
		{
			return false;
		}

		// �˻��� ���Ͱ� �̵������� ��ĭ�̸� �̵�,,.
		/*if (searchedActor->As<Empty>())
		{
			return true;
		}*/
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

	if( position.x )
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
