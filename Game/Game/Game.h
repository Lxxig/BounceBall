#pragma once

#include <Engine/Engine.h>
#include <Container/List.h>

class Game : public Engine
{
public:
	Game();
	~Game();

	void ToggleMenu();

	//Getter.
	void SetStageIndex(int stageIndex) { this->stageIndex = stageIndex; }
	//int GetStageIndex() const { return stageIndex; }

	static Game& Get() { return *instance; }

private:
	bool showGame = false;

	// 게임 스테이지 관리.
	List<Level*> gameLevel;
	int stageIndex = 0;

	Level* backLevel = nullptr;

private:
	static Game* instance;
};