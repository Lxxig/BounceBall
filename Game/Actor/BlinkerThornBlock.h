#pragma once

#include <Actor/DrawableActor.h>
#include <Engine/Timer.h>

class BlinkerThornBlock : public DrawableActor
{
	RTTI_DECLARATIONS(BlinkerThornBlock, DrawableActor)

public:
	BlinkerThornBlock(const Vector2& position);

	virtual void Update(float deltaTime) override;

	// ���� ���¸� ��ȯ�ϴ� �Լ�.
	inline const bool isShowedThornBlock()
	{
		return showBlock;
	}

private:
	// �����̴��� Ȯ���ϴ� ����.
	bool showBlock = false;

	// �����̴� ������ delayTime �ɱ�.
	Timer timer;

	// delayTime ����.
	float delayTime = 3.0f;

};
