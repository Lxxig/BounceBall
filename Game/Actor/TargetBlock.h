#pragma once

#include "Actor/DrawableActor.h"
#include "Math/Vector2.h"

class TargetBlock : public DrawableActor
{
	RTTI_DECLARATIONS(TargetBlock, DrawableActor)

public:
	TargetBlock(const Vector2& position);

};