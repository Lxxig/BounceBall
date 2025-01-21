#pragma once

#include <Actor/DrawableActor.h>
#include <Engine/Timer.h>

class BlinkerBlock : public DrawableActor
{
	RTTI_DECLARATIONS(BlinkerBlock, DrawableActor)

public:
	BlinkerBlock(const Vector2& position);

	virtual void Update(float deltaTime) override;

	// ���� ���¸� ��ȯ�ϴ� �Լ�.
	inline const bool isShowedBlock()
	{
		return showBlock;
	}

private:
	// �����̴��� Ȯ���ϴ� ����.
	bool showBlock = true;

	// �����̴� ������ delayTime �ɱ�.
	Timer timer;

	// delayTime ����.
	float delayTime = 3.0f;

};
