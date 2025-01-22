#include "Player.h"
#include "Engine/Engine.h"
#include "Game/Game.h"
#include "Level/GameLevel.h"
#include "Engine/Timer.h"

#include "Level/MenuLevel.h"

// 사운드 적용.
#pragma comment(lib, "winmm.lib")

Player::Player(const Vector2& position, GameLevel* level)
	//: DrawableActor("●"), refLevel(level)
	: DrawableActor("0"), refLevel(level)
{
	// 위치 설정.
	this->position = position;

	// 생상 설정.
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
		// 메뉴 토글.
		Game::Get().ToggleMenu();
	}

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
				if (ballUpCount == 0)
				{
					// 점프 사운드 파일 읽어오기.
					mciSendString(TEXT("open \"../Assets/Sounds/JumpSound.wav\" type mpegvideo alias jumpSound"), NULL, 0, NULL);
					// 점프 사운드 플레이(한 번만).
					mciSendString(TEXT("play jumpSound from 0"), NULL, 0, NULL);
					// 볼륨 소리 조절.
					mciSendString(TEXT("setaudio jumpSound volume to 300"), NULL, 0, NULL);
				}
				position.y -= 1;
				++ballUpCount;
				if (ballUpCount == currentMaxBallUpCount)
				{
					// currentMaxBallUpCount가 점프 블럭이나 아이템 사용으로 변하게되면 다시 초기화.
					currentMaxBallUpCount = maxBallUpCount;
					ballUpCount = 0;
					isBallDown = true;
				}
			}
			else
			{
				isBallDown = true;

				// 블럭에 부딛히면 0으로 초기화.
				ballUpCount = 0;
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

				++position.x;
			}
		}

		xTimer.Reset();
	}
}
