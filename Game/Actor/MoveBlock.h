#pragma once

#include <Actor/DrawableActor.h>
#include <vector>
#include <Engine/Timer.h>

// 전방 선언.
class GameLevel;
class Block;
class MoveBlock : public DrawableActor
{
	RTTI_DECLARATIONS(MoveBlock, DrawableActor)

public:
	MoveBlock(const Vector2& position, GameLevel* refLevel);

	virtual void Update(float deltaTime) override;

	// 무브 블럭을 만드는 함수.
	inline void SetMoveBlock(Block* block)
	{
		moveBlock.emplace_back(block);
		++blockSize;
	}

	// 무브블럭에 포함된 블럭의 개수를 반환 하는 함수.
	int GetBlockSize();

	// 방향 제어 함수.

private:
	// 게임 레벨을 참조하는 변수.
	GameLevel* refLevel = nullptr;

	// 이동 블럭을 저장하는 변수.
	std::vector<Block*> moveBlock;

	// BlockSize
	int blockSize = 0;

	// 좌우 이동 제어 변수.
	bool isRight = true;

	// 딜레이 시간 저장.
	float delayTime = 0.15f;

	// 타이머 변수.
	Timer timer;
};