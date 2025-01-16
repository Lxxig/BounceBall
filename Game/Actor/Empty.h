#pragma once

#include <Actor/DrawableActor.h>

class Empty : public DrawableActor
{
	RTTI_DECLARATIONS(Empty, DrawableActor)

public:
	Empty(const Vector2& position);
};