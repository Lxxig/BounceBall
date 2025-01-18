#pragma once

#include <Level/Level.h>
#include <Math/Vector2.h>

// ���ڹ� ���� ����.
class DrawableActor;
class Player;
class Star;
class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	//GameLevel(const char* fileAdress);
	GameLevel(int stageIndex);

	// ������Ʈ �Լ�.
	virtual void Update(float deltaTime) override;

	// ������ �׸��� �Լ�.
	virtual void Draw() override;

	// �÷��̾ �̵� ������ �� Ȯ���ϴ� �Լ�.
	bool CanPlayerMove(const Vector2& position);

	// ���� �������� Ȯ�� �ε���.
	inline void SetStageIndex(int stageIndex) { this->stageIndex = stageIndex; }
	inline int GetStageIndex() { return stageIndex; }

private:
	// ���� �� ��Ƽ� Ŭ���� �ߴ��� Ȯ��.
	bool CheckGameClear();

	// ���� �� ���԰� ������ ��� GameOver.
	bool CheckGameOver();

private:
	// ��/�� ���� �迭.
	List<DrawableActor*> map;

	// ��Ÿ.
	List<Star*> stars;

	// �÷��̾�.
	Player* player = nullptr;

	// �������� ��Ÿ ���� ���� ����.
	int stageStarCount = 0;

	// ���� ��Ÿ ���� ���� ����.
	int starCount = 0;

	// ���� Ŭ���� ����.
	bool isGameClear = false;

	// ���� ���� ������.
	bool isGameOver = false;

	// �������� Ȯ�� �ε���.
	int stageIndex = 0;

};