#pragma once

#include <Actor/DrawableActor.h>
#include <Engine/Timer.h>

class BlinkerBlock : public DrawableActor
{
	RTTI_DECLARATIONS(BlinkerBlock, DrawableActor)

public:
	BlinkerBlock(const Vector2& position);

	virtual void Update(float deltaTime) override;

	// 블럭의 상태를 반환하는 함수.
	inline const bool isShowedBlock()
	{
		return showBlock;
	}

private:
	// 깜빡이는지 확이하는 변수.
	bool showBlock = true;

	// 깜빡이는 로직에 delayTime 걸기.
	Timer timer;

	// delayTime 변수.
	float delayTime = 3.0f;

};
