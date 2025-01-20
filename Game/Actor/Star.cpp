#include "Star.h"

Star::Star(const Vector2& position)
	:DrawableActor("S")
{
	this->position = position;
	color = Color::LightYellow;
}
