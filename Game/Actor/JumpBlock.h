#pragma once

#include "Actor/DrawableActor.h"
#include "Math/Vector2.h"

class JumpBlock : public DrawableActor
{
	RTTI_DECLARATIONS(JumpBlock, DrawableActor)

public:
	JumpBlock(const Vector2& position);

};