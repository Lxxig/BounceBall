#include "TargetBlock.h"

TargetBlock::TargetBlock(const Vector2& position)
	:DrawableActor("*")
{
	this->position = position;

	color = Color::LightYellow;
}