#include "Wall.h"

Wall::Wall(const Vector2& position)
	:DrawableActor("��")
{
	// dnlcl tjfwjd.
	this->position = position;
	// ���� ����.
	color = Color::Green;
}
