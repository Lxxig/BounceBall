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
	// ���� ������ �����ϴ� ����.
	GameLevel* refLevel = nullptr;

	// ������ ���� ����.
	float xDelayTime = 0.09f;
	float yDelayTime = 0.09f;

	// ���� ���� Ȯ�� ����.
	bool isBallDown = true;
	int ballUpCount = 0;
	int maxBallUpCount = 3;
};