#pragma once

#include <Level/Level.h>
#include <Math/Vector2.h>
#include <vector>

// 소코반 게임 레벨.
class DrawableActor;
class Player;
class Star;
class ExtinctionBlock;
class Block;
class MoveBlock;
class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	//GameLevel(const char* fileAdress);
	GameLevel(int stageIndex);

	// 업데이트 함수.
	virtual void Update(float deltaTime) override;

	// 레벨의 그리기 함수.
	virtual void Draw() override;

	// 플레이어가 이동 가능한 지 확인하는 함수.
	bool CanPlayerMove(const Vector2& position);

	// moveBlock이 이동가능한지 확인하는 함수.
	bool CanMoveBlock(const Vector2& position);

	// 게임 스테이지 확인 인덱스.
	inline void SetStageIndex(int stageIndex) { this->stageIndex = stageIndex; }
	inline int GetStageIndex() { return stageIndex; }
	inline bool IsGameClear() { return isGameClear; }
	inline bool IsGameOver() { return isGameOver; }

private:
	// 별을 다 모아서 클리어 했는지 확인.
	bool CheckGameClear();

	// 별을 다 못먹고 떨어진 경우 GameOver.
	bool CheckGameOver();

private:
	// 벽/땅 액터 배열.
	std::vector<DrawableActor*> map;

	// 스타.
	std::vector<Star*> stars;

	// ExtinctionBlock
	std::vector<ExtinctionBlock*> extinctionBlocks;

	// MoveBlocks
	std::vector<MoveBlock*> moveBlocks;

	// MoveBlock
	MoveBlock* moveBlock = nullptr;

	// TargetPosition 무브블럭의 도착지의 좌표를 저장하는 변수.
	std::vector<Vector2> moveBlockTargetPosition;

	// MoveBlock의 수를 저장하는 변수.
	int MoveBlockCount = -1;

	// MoveBlock을 계속 만들지 말지 결정하는 변수.
	bool makeMoveBlock = false;

	// 플레이어.
	Player* player = nullptr;

	// 플레이어의 이전 위치 저장 변수.
	Vector2 prePosition;

	// 스테이지 스타 개수 저장 변수.
	int stageStarCount = 0;

	// 모은 스타 개수 저장 변수.
	int starCount = 0;

	// 게임 클리어 변수.
	bool isGameClear = false;

	// 게임 오버 변변수.
	bool isGameOver = false;

	// 스테이지 확인 인덱스.
	int stageIndex = 0;

};