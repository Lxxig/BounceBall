#include "ThornBlock.h"

ThornBlock::ThornBlock(const Vector2& position)
	:DrawableActor("^")
{
	this->position = position;

	color = Color::Brown;
}
