#pragma once

#include "Actor/DrawableActor.h"
#include "Math/Vector2.h"

class Star : public DrawableActor
{
	RTTI_DECLARATIONS(Star, DrawableActor)

public:
	Star(const Vector2& position);

};