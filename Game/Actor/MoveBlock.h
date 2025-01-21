#pragma once

#include <Actor/DrawableActor.h>
#include <vector>
#include <Engine/Timer.h>

// ���� ����.
class GameLevel;
class Block;
class MoveBlock : public DrawableActor
{
	RTTI_DECLARATIONS(MoveBlock, DrawableActor)

public:
	MoveBlock(const Vector2& position, GameLevel* refLevel);

	virtual void Update(float deltaTime) override;

	// ���� ���� ����� �Լ�.
	inline void SetMoveBlock(Block* block)
	{
		moveBlock.emplace_back(block);
		++blockSize;
	}

	// ������� ���Ե� ���� ������ ��ȯ �ϴ� �Լ�.
	int GetBlockSize();

	// ���� ���� �Լ�.

private:
	// ���� ������ �����ϴ� ����.
	GameLevel* refLevel = nullptr;

	// �̵� ���� �����ϴ� ����.
	std::vector<Block*> moveBlock;

	// BlockSize
	int blockSize = 0;

	// �¿� �̵� ���� ����.
	bool isRight = true;

	// ������ �ð� ����.
	float delayTime = 0.15f;

	// Ÿ�̸� ����.
	Timer timer;
};