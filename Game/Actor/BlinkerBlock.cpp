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
			// ���� �������� �����̸� �Ⱥ��̴� ���·� ����.
			showBlock = !showBlock;

			color = Color::Gray;

			timer.Reset();
		}
	}
	else
	{
		if (timer.IsTimeOut())
		{
			// ���� �Ⱥ��̴� �����̸� ���̴� ���·� ����.
			showBlock = !showBlock;

			color = Color::LightAqua;

			timer.Reset();
		}
	}
}
