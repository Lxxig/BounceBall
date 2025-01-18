#include <iostream>
#include "Engine/Engine.h"
#include "Game/Game.h"
#include "Level/MenuLevel.h"
#include <vector>

int main()
{
	// 메모리 누수 확인.
	CheckMemoryLeak();

	Game game;
	game.LoadLevel(new MenuLevel());
	game.Run();
}