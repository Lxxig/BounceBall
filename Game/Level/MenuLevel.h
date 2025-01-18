#pragma once

#include "Level/Level.h"
#include "Container/List.h"

enum class StageType
{
	Stage1 = 0,
	Stage2,
	Stage3
};

struct MenuItem
{
	using OnSelected = void (*)();

	MenuItem(const char* text, OnSelected onSelected)
	{
		size_t length = strlen(text);
		menuText = new char[length + 1];
		strcpy_s(menuText, length + 1, text);

		this->onSelected = onSelected;
	}

	~MenuItem()
	{
		delete[] menuText;
	}

	char* menuText;
	OnSelected onSelected;
};

class MenuLevel : public Level
{
	RTTI_DECLARATIONS(MenuLevel, Level)

public:
	MenuLevel();
	~MenuLevel();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	List<MenuItem*> menuItems;
	int currentIndex = 0;

	Color selectedColor = Color::Green;
	Color unselectedColor = Color::White;

	int length = 0;
	//int currentStageType = 0;

	StageType currentStageType = StageType::Stage1;
};