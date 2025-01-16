#include "Wall.h"

Wall::Wall(const Vector2& position)
	:DrawableActor("▒")
{
	// dnlcl tjfwjd.
	this->position = position;
	// 색상 설정.
	color = Color::Green;
}
