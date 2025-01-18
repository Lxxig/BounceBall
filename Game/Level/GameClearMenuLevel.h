#pragma once

#include "Level/Level.h"
#include "Container/List.h"
#include <vector>

class GameClearMenuLvel : public Level
{
	RTTI_DECLARATIONS(GameClearMenuLvel, Level)

public:
	GameClearMenuLvel();
	~GameClearMenuLvel();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	std::vector<struct MenuItem*> menuItems;
	int currentIndex = 0;

	Color selectedColor = Color::Green;
	Color unselectedColor = Color::White;

	int length = 0;
};