#include <iostream>
#include "Engine/Engine.h"
#include "Game/Game.h"
#include "Level/MenuLevel.h"

int main()
{
	// �޸� ���� Ȯ��.
	CheckMemoryLeak();

	Game game;
	game.LoadLevel(new MenuLevel());
	game.Run();
}