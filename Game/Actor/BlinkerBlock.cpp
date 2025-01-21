#include "BlinkerBlock.h"

BlinkerBlock::BlinkerBlock(const Vector2& position)
	: DrawableActor("B")
{
	this->position = position;

	color = Color::LightAqua;

	timer = Timer(delayTime);
}

void BlinkerBlock::Update(float deltaTime)
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

			color = Color::LightAqua;

			timer.Reset();
		}
	}
}
