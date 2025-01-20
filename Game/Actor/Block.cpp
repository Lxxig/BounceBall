#include "Block.h"

Block::Block(const Vector2& position)
	:DrawableActor("▒")
{
	// dnlcl tjfwjd.
	this->position = position;
	// 색상 설정.
	color = Color::LightAqua;
}
