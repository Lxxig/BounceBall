#pragma once

#include <Level/Level.h>
#include <Math/Vector2.h>
#include <vector>

// ���ڹ� ���� ����.
class DrawableActor;
class Player;
class Star;
class ExtinctionBlock;
class Block;
class MoveBlock;
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

	// moveBlock�� �̵��������� Ȯ���ϴ� �Լ�.
	bool CanMoveBlock(const Vector2& position);

	// ���� �������� Ȯ�� �ε���.
	inline void SetStageIndex(int stageIndex) { this->stageIndex = stageIndex; }
	inline int GetStageIndex() { return stageIndex; }
	inline bool IsGameClear() { return isGameClear; }
	inline bool IsGameOver() { return isGameOver; }

private:
	// ���� �� ��Ƽ� Ŭ���� �ߴ��� Ȯ��.
	bool CheckGameClear();

	// ���� �� ���԰� ������ ��� GameOver.
	bool CheckGameOver();

private:
	// ��/�� ���� �迭.
	std::vector<DrawableActor*> map;

	// ��Ÿ.
	std::vector<Star*> stars;

	// ExtinctionBlock
	std::vector<ExtinctionBlock*> extinctionBlocks;

	// MoveBlocks
	std::vector<MoveBlock*> moveBlocks;

	// MoveBlock
	MoveBlock* moveBlock = nullptr;

	// TargetPosition ������� �������� ��ǥ�� �����ϴ� ����.
	std::vector<Vector2> moveBlockTargetPosition;

	// MoveBlock�� ���� �����ϴ� ����.
	int MoveBlockCount = -1;

	// MoveBlock�� ��� ������ ���� �����ϴ� ����.
	bool makeMoveBlock = false;

	// �÷��̾�.
	Player* player = nullptr;

	// �÷��̾��� ���� ��ġ ���� ����.
	Vector2 prePosition;

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