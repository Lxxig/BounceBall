#pragma once

#include <Level/Level.h>
#include <Math/Vector2.h>

// 소코반 게임 레벨.
class DrawableActor;
class Player;
class Box;
class Target;
class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel(const char* fileAdress);

	// 업데이트 함수.
	virtual void Update(float deltaTime) override;

	// 레벨의 그리기 함수.
	virtual void Draw() override;

	// 플레이어가 이동 가능한 지 확인하는 함수.
	bool CanPlayerMove(const Vector2& position);

private:
	// 박스를 옮긴 뒤 게임을 클리어했는지 확이하는 함수.
	bool CheckGameClear();

private:
	// 벽/땅 액터 배열.
	List<DrawableActor*> map;

	// 플레이어.
	Player* player = nullptr;

	// 게임 클리어 변수.
	bool isGameClear = false;

};