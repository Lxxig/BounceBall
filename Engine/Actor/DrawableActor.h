#pragma once

#include "Actor.h"

class ENGINE_API DrawableActor : public Actor
{
	// RTTI.
	RTTI_DECLARATIONS(DrawableActor, Actor)

public:
	DrawableActor(const char* image = "");
	virtual ~DrawableActor();

	virtual void Draw() override;
	virtual void SetPosition(const Vector2& newPosition) override;

	// 충돌 확인 함수.
	bool Intersect(const DrawableActor& other);

	// Getter.
	inline int Width() const { return width; }

protected:
	// 화면에 그릴 문자 값.
	char* image;

	// 너비(image 문자열의 길이).
	int width = 0;

	// 색상
	Color color = Color::White;
};