#pragma once

#include <Actor/DrawableActor.h>

class Block : public DrawableActor
{
	RTTI_DECLARATIONS(Block, DrawableActor)

public:
	Block(const Vector2& position);

};
