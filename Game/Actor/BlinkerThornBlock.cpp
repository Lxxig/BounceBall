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

			color = Color::Brown;

			timer.Reset();
		}
	}
}
