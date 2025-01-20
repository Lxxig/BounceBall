#pragma once

#include <Actor/DrawableActor.h>

class Block : public DrawableActor
{
	RTTI_DECLARATIONS(Block, DrawableActor)

public:
	Block(const Vector2& position);

	inline void SetPosition(const Vector2& position)
	{
		this->position = position;
	}

};
