#include "Star.h"

Star::Star(const Vector2& position)
	:DrawableActor("��")
{
	this->position = position;
	color = Color::LightYellow;
}
