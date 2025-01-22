#include "Player.h"
#include "Engine/Engine.h"
#include "Game/Game.h"
#include "Level/GameLevel.h"
#include "Engine/Timer.h"

#include "Level/MenuLevel.h"

// ���� ����.
#pragma comment(lib, "winmm.lib")

Player::Player(const Vector2& position, GameLevel* level)
	//: DrawableActor("��"), refLevel(level)
	: DrawableActor("0"), refLevel(level)
{
	// ��ġ ����.
	this->position = position;

	// ���� ����.
	color = Color::Green;
}

Player::~Player()
{
	mciSendString(TEXT("close jumpSound"), NULL, 0, NULL);
}

void Player::Update(float deltaTime)
{
	Super::Update(deltaTime);
	
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		// �޴� ���.
		Game::Get().ToggleMenu();
	}

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
				if (ballUpCount == 0)
				{
					// ���� ���� ���� �о����.
					mciSendString(TEXT("open \"../Assets/Sounds/JumpSound.wav\" type mpegvideo alias jumpSound"), NULL, 0, NULL);
					// ���� ���� �÷���(�� ����).
					mciSendString(TEXT("play jumpSound from 0"), NULL, 0, NULL);
					// ���� �Ҹ� ����.
					mciSendString(TEXT("setaudio jumpSound volume to 300"), NULL, 0, NULL);
				}
				position.y -= 1;
				++ballUpCount;
				if (ballUpCount == currentMaxBallUpCount)
				{
					// currentMaxBallUpCount�� ���� ���̳� ������ ������� ���ϰԵǸ� �ٽ� �ʱ�ȭ.
					currentMaxBallUpCount = maxBallUpCount;
					ballUpCount = 0;
					isBallDown = true;
				}
			}
			else
			{
				isBallDown = true;

				// ���� �ε����� 0���� �ʱ�ȭ.
				ballUpCount = 0;
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

				++position.x;
			}
		}

		xTimer.Reset();
	}
}
