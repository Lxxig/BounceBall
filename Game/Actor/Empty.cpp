#include "Empty.h"

Empty::Empty(const Vector2& position)
	: DrawableActor(" ")
{
	// ��ġ ����.
	this->position = position;

	// ���� ����.
	color = Color::Red;
}
