#include "BlinkerThornBlock.h"

BlinkerThornBlock::BlinkerThornBlock(const Vector2& position)
	: DrawableActor("^")
{
	this->position = position;

	color = Color::Brown;

	timer = Timer(delayTime);
}

void BlinkerThornBlock::Update(float deltaTime)
{
	Super::Update(deltaTime);

	timer.Update(deltaTime);

	if (showBlock)
	{
		if (timer.IsTimeOut())
		{
			// 블럭이 보여지는 상태이면 안보이는 상태로 변경.
			showBlock = !showBlock;

			color = Color::Gray;

			timer.Reset();
		}
	}
	else
	{
		if (timer.IsTimeOut())
		{
			// 블럭이 안보이는 상태이면 보이는 생태로 변경.
			showBlock = !showBlock;

			color = Color::Brown;

			timer.Reset();
		}
	}
}
