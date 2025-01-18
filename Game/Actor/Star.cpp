#include "Star.h"

Star::Star(const Vector2& position)
	:DrawableActor("¡Ú")
{
	this->position = position;
	color = Color::LightYellow;
}
