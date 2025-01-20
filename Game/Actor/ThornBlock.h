#pragma once

#include <Actor/DrawableActor.h>

class ThornBlock : public DrawableActor
{
	RTTI_DECLARATIONS(ThornBlock, DrawableActor)

public:
	ThornBlock(const Vector2& position);
};