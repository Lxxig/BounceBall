#pragma once

#include <Actor/DrawableActor.h>

class ExtinctionBlock : public DrawableActor
{
	RTTI_DECLARATIONS(ExtinctionBlock, DrawableActor)

public:
	ExtinctionBlock(const Vector2& position);

};
