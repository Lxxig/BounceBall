#include "Player.h"
#include "Engine/Engine.h"
#include "Game/Game.h"
#include "Level/GameLevel.h"
#include "Engine/Timer.h"

Player::Player(const Vector2& position, GameLevel* level)
	: DrawableActor("��"), refLevel(level)
{
	// ��ġ ����.
	this->position = position;

	// ���� ����.
	color = Color::Green;
}

void Player::Update(float deltaTime)
{
	Super::Update(deltaTime);
	
	// ESC ����.
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		// Engine::Get().QuitGame();
		// �޴� ���.
		Game::Get().ToggleMenu();
	}

	// ���� ���� �������� ��ġ���� ���� ����.
	static int previousPositionY = position.y;

	// y���� ��ǥ ������.
	static Timer yTimer(yDelayTime);

	yTimer.Update(deltaTime);

	// ���� ���� Ȯ��.
	if (isBallDown)
	{
		if (yTimer.IsTimeOut())
		{
			// �̵� �������� Ȯ��.
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
			// �̵� �������� Ȯ��.
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

	// x���� �ӵ� ������.
	static Timer xTimer(xDelayTime);
	xTimer.Update(deltaTime);

	if (xTimer.IsTimeOut())
	{
		// ��ȭ �¿�.
		if (Engine::Get().GetKey(VK_LEFT))
		{
			// �̵� �������� Ȯ��.
			if (refLevel->CanPlayerMove(
				Vector2(position.x - 1, position.y))
				)
			{
				// ������ ���¿����� �̵�.
				/*if (position.y != previousPositionY)
				{
					--position.x;
				}*/

				--position.x;
			}
		}

		if (Engine::Get().GetKey(VK_RIGHT))
		{
			// �̵� �������� Ȯ��.
			if (refLevel->CanPlayerMove(
				Vector2(position.x + 1, position.y))
				)
			{
				// ������ ���¿����� �̵�.
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
