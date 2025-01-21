#include "JumpBlock.h"

JumpBlock::JumpBlock(const Vector2& position)
	:DrawableActor("J")
{
	this->position = position;

	color = Color::Purple;
}
