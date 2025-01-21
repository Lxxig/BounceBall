#pragma once

#include <Actor/DrawableActor.h>
#include <Engine/Timer.h>

class BlinkerThornBlock : public DrawableActor
{
	RTTI_DECLARATIONS(BlinkerThornBlock, DrawableActor)

public:
	BlinkerThornBlock(const Vector2& position);

	virtual void Update(float deltaTime) override;

	// 블럭의 상태를 반환하는 함수.
	inline const bool isShowedThornBlock()
	{
		return showBlock;
	}

private:
	// 깜빡이는지 확이하는 변수.
	bool showBlock = false;

	// 깜빡이는 로직에 delayTime 걸기.
	Timer timer;

	// delayTime 변수.
	float delayTime = 3.0f;

};
