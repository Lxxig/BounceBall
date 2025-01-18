#pragma once

#include <Engine/Engine.h>
#include <Container/List.h>

class Game : public Engine
{
public:
	Game();
	virtual ~Game();

	void ToggleMenu();

	// Getter.
	inline void SetStageIndex(int stageIndex) { this->stageIndex = stageIndex; }
	const int GetStageIndex() { return stageIndex; }

	// 삭제된 메뉴레벨을 nullptr로 지정.
	void SetMenuLvelToNullptr() { this->menuLevel = nullptr; }

	// GameAndClearOrOverToggleMenu() 생성.
	void ToggleGameClearMenu();

	static Game& Get() { return *instance; }

public:
	List<const char*> stageAdress;

private:
	int stageIndex = -1;

	Level* menuLevel = nullptr;
	Level* backLevel = nullptr;

	//Level* backGameClearMenuLevel = nullptr;

private:
	static Game* instance;
};