#include "ExtinctionBlock.h"

ExtinctionBlock::ExtinctionBlock(const Vector2& position)
	:DrawableActor("E")
{
	this->position = position;

	color = Color::LightWhite;
}
