#include "GameLevel.h"
#include "Engine/Engine.h"

#include "Actor/Wall.h"
#include "Actor/Empty.h"
#include "Actor/Player.h"

#include "Engine/Timer.h"

GameLevel::GameLevel(const char* stageAdress)
{
	// Ŀ�� ���߱�.
	Engine::Get().SetCursorType(CursorType::NoCursor);

	// �� ���� �ҷ��� ���� �ε�.
	// ���� �б�.

	FILE* file = nullptr;
	fopen_s(&file, stageAdress, "rb");

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

		// �� ���ڰ� 1�̸� wall ���� ����.
		if (mapChar == '1')
		{
			Wall* wall = new Wall(Vector2(xPosition, yPosition));
			actors.PushBack(wall);
			map.PushBack(wall);
		}

		// �� ���ڰ� .�̸� �׶��� ���� ����.
		else if (mapChar == '.')
		{
			Empty* empty = new Empty(Vector2(xPosition, yPosition));
			actors.PushBack(empty);
			map.PushBack(empty);
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

		// Ŀ�� �̵�.
		Engine::Get().SetCursorPosition(0, Engine::Get().ScreenSize().y);

		// �޽��� ���.
		Log("GameClear!");

		// ������ ����.
		Sleep(2000);

		Engine::Get().QuitGame();
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

		
		// �� ���� �׸���.
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
		if (searchedActor->As<Wall>())
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
	return false;
}
