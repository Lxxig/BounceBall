#include "Player.h"
#include "Engine/Engine.h"
#include "Game/Game.h"
#include "Level/GameLevel.h"
#include "Engine/Timer.h"

Player::Player(const Vector2& position, GameLevel* level)
	: DrawableActor("●"), refLevel(level)
{
	// 위치 설정.
	this->position = position;

	// 생상 설정.
	color = Color::Green;
}

void Player::Update(float deltaTime)
{
	Super::Update(deltaTime);
	
	// ESC 종료.
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		// Engine::Get().QuitGame();
		// 메뉴 토글.
		Game::Get().ToggleMenu();
	}

	// 공의 이전 프레임의 위치상태 저장 변수.
	static int previousPositionY = position.y;

	// y방향 좌표 딜레이.
	static Timer yTimer(yDelayTime);

	yTimer.Update(deltaTime);

	// 공의 상태 확인.
	if (isBallDown)
	{
		if (yTimer.IsTimeOut())
		{
			// 이동 가능한지 확인.
			if (refLevel->CanPlayerMove(
				Vector2(position.x, position.y + 1))
				)
			{
				position.y += 1;
			}
			else
			{
				isBallDown = false;
			}

			yTimer.Reset();
		}
	}
	else
	{
		if (yTimer.IsTimeOut())
		{
			// 이동 가능한지 확인.
			if (refLevel->CanPlayerMove(
				Vector2(position.x, position.y + -1))
				)
			{
				position.y -= 1;
				++ballUpCount;
				if (ballUpCount == maxBallUpCount)
				{
					ballUpCount = 0;
					isBallDown = true;
				}
			}
			else
			{
				isBallDown = true;
			}

			yTimer.Reset();
		}
	}

	// x방향 속도 딜레이.
	static Timer xTimer(xDelayTime);
	xTimer.Update(deltaTime);

	if (xTimer.IsTimeOut())
	{
		// 상화 좌우.
		if (Engine::Get().GetKey(VK_LEFT))
		{
			// 이동 가능한지 확인.
			if (refLevel->CanPlayerMove(
				Vector2(position.x - 1, position.y))
				)
			{
				// 점프한 상태에서만 이동.
				/*if (position.y != previousPositionY)
				{
					--position.x;
				}*/

				--position.x;
			}
		}

		if (Engine::Get().GetKey(VK_RIGHT))
		{
			// 이동 가능한지 확인.
			if (refLevel->CanPlayerMove(
				Vector2(position.x + 1, position.y))
				)
			{
				// 점프한 상태에서만 이동.
				/*if (position.y != previousPositionY)
				{
					++position.x;
				}*/

				++position.x;
			}
		}

		xTimer.Reset();
	}

	previousPositionY = position.y;
}
