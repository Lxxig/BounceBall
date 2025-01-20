#include "ThornBlock.h"

ThornBlock::ThornBlock(const Vector2& position)
	:DrawableActor("i")
{
	this->position = position;

	color = Color::Blue;
}
