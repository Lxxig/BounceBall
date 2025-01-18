#pragma once

#include "Actor/DrawableActor.h"

class GameLevel;
class Player : public DrawableActor
{
	RTTI_DECLARATIONS(Player, DrawableActor)

public:
	Player(const Vector2& position, GameLevel* level);

	virtual void Update(float deltaTime) override;

private:
	// 게임 레벨을 참조하는 변수.
	GameLevel* refLevel = nullptr;

	// 딜레이 관련 변수.
	float xDelayTime = 0.05f;
	float yDelayTime = 0.07f;

	// 공의 상태 확인 변수.
	bool isBallDown = true;
	int ballUpCount = 0;
	int maxBallUpCount = 3;
};