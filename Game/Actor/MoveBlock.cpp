#include "MoveBlock.h"
#include "Level/GameLevel.h"
#include "Engine/Timer.h"
#include "Actor/Block.h"

MoveBlock::MoveBlock(const Vector2& position, GameLevel* refLevel)
	: DrawableActor("B"), refLevel(refLevel)
{
	// dnlcl tjfwjd.
	this->position = position;
	// 색상 설정.
	color = Color::LightAqua;
}

void MoveBlock::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// y방향 좌표 딜레이.
	static Timer timer(delayTime);

	timer.Update(deltaTime);

	if (timer.IsTimeOut())
	{
		static int rightIndex = (int)moveBlock.size() - 1;
		// 이동 가능한지 확인.
		//if (refLevel->CanMoveBlock(
		//	Vector2(position.x + 1, position.y))
		//	)
		//{
		//	position.x += 1;
		//}
		
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
		}

		timer.Reset();
	}
}

int MoveBlock::GetBlockSize()
{
	return blockSize;
}
