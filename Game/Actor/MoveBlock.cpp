#include "MoveBlock.h"
#include "Level/GameLevel.h"
#include "Engine/Timer.h"
#include "Actor/Block.h"

MoveBlock::MoveBlock(const Vector2& position, GameLevel* refLevel)
	: DrawableActor(""), refLevel(refLevel)
{
	// dnlcl tjfwjd.
	this->position = position;

	// 색상 설정.
	color = Color::LightAqua;

	// 타이머 설정.
	timer = Timer(delayTime);
}

void MoveBlock::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// y방향 좌표 딜레이.
	//Timer timer(delayTime);
	timer.Update(deltaTime);

	if (timer.IsTimeOut())
	{
		int rightIndex = (int)moveBlock.size() - 1;
		
		if (isRight)
		{
			if (refLevel->CanMoveBlock(Vector2(
				moveBlock[rightIndex]->Position().x + 1, moveBlock[rightIndex]->Position().y)))
			{
				for (auto* block : moveBlock)
				{
					block->SetPosition(Vector2(
						block->Position().x + 1, block->Position().y));
				}
			}
			else
			{
				isRight = !isRight;
			}
		}
		else
		{
			if (refLevel->CanMoveBlock(Vector2(
				moveBlock[0]->Position().x - 1, moveBlock[0]->Position().y)))
			{
				for (auto* block : moveBlock)
				{
					block->SetPosition(Vector2(
						block->Position().x - 1, block->Position().y));
				}
			}
			else
			{
				isRight = !isRight;
			}
		}

		timer.Reset();
	}
}

int MoveBlock::GetBlockSize()
{
	return blockSize;
}
