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

		// �� ���ڰ� 1�̸� block ���� ����.
		if (mapChar == '1')
		{
			Block* block = new Block(Vector2(xPosition, yPosition));
			actors.PushBack(block);
			map.PushBack(block);
		}

		// �� ���ڰ� .�̸� �׶��� ���� ����.
		else if (mapChar == '.')
		{
			Empty* empty = new Empty(Vector2(xPosition, yPosition));
			actors.PushBack(empty);
			map.PushBack(empty);
		}

		// �� ���ڰ� 5�̸� �׶��� ���� ����.
		else if (mapChar == '5')
		{
			// ���������� �����ϴ� ��Ÿ ���� ����.
			++stageStarCount;

			Empty* empty = new Empty(Vector2(xPosition, yPosition));
			actors.PushBack(empty);
			map.PushBack(empty);

			Star* star = new Star(Vector2(xPosition, yPosition));
			actors.PushBack(star);
			//stars.PushBack(star);
		}

		// �� ���ڰ� p�̸� �׶��� ���� ����.
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

	// ���� ����.
	delete[] buffer;

	// ���� �ݱ�.
	fclose(file);
}

void GameLevel::Update(float deltaTime)
{
	// ���ŵ� star�� �����ϰ� ���� star���� stars�� Ǫ��
	stars.Clear();
	for (Actor* actor : actors)
	{
		Star* star = actor->As<Star>();
		if (star)
		{
			stars.PushBack(star);
		}
	}

	// ������ Ŭ���� �Ǿ����� Ȯ��.
	CheckGameClear();

	Super::Update(deltaTime);


	// ������ Ŭ���� ������, ���� ���� ó��.
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
		Engine::Get().SetCursorPosition(Engine::Get().ScreenSize().x / 2 - (int)gameClearTextLength / 2, Engine::Get().ScreenSize().y/2 - 4);

		// �޽��� ���.
		Log("GameClear!");

		// ������ ����.
		Sleep(2000);

		// Level ��ȯ.
		Game::Get().ToggleGameClearMenu();
	}
}

void GameLevel::Draw()
{
	// ���� ���Ŷ� Super�� �ϸ�ȵ�.
	// �� �׸���.

	for (auto* actor : map)
	{
		// �÷��̾� ��ġ Ȯ��.
		if (actor->Position() == player->Position()) continue;

		// ��Ÿ�� ������ Draw�׸��� �ʰ��ϴ� ����.
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
		
		// �� ���� �׸���.
		actor->Draw();
	}

	// ��Ÿ �׸���.
	for (auto* star : stars)
	{
		// �÷��̾� ��ġ Ȯ��.
		if (star->Position() == player->Position()) continue;

		star->Draw();
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

	//for (Star* star : stars)
	for (int ix = 0; ix < stars.Size(); ++ix)
	{
		Star* star = stars[ix];

		// �˻��� ���Ͱ� star���� Ȯ��.
		if (star->Position() == position)
		{
			// Star��� ��Ÿ�� ��Ÿ�� ȹ�� �� ����.
			star->Destroy();
			++starCount;
			
			return true;
		}
	}

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
		// �˻��� ���Ͱ� ������ Ȯ��.
		if (searchedActor->As<Block>())
		{
			return false;
		}

		// �˻��� ���Ͱ� �̵������� ��ĭ�̸� �̵�,,.
		if (searchedActor->As<Empty>())
		{
			return true;
		}
	}
}

bool GameLevel::CheckGameClear()
{
	// ��Ÿ�� �� ������� ���� Ŭ����.
	if (starCount == stageStarCount)
	{
		isGameClear = true;
	}
	return false;
}
