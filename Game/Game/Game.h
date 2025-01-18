#pragma once

#include <Engine/Engine.h>
#include <vector>

class Game : public Engine
{
public:
	Game();
	virtual ~Game();

	virtual void LoadLevel(Level* newLevel) override;

	void ToggleMenu();

	// Getter.
	inline void SetStageIndex(int stageIndex) { this->stageIndex = stageIndex; }
	const int GetStageIndex() { return stageIndex; }

	// GameAndClearOrOverToggleMenu() »ý¼º.
	void ToggleGameClearMenu();

	static Game& Get() { return *instance; }

public:
	std::vector<const char*> stageAdress;

private:
	int stageIndex = -1;

	Level* menuLevel = nullptr;
	Level* backLevel = nullptr;

	//Level* backGameClearMenuLevel = nullptr;

private:
	static Game* instance;
};