#pragma once

#include "Core.h"

// �ʽð� Ŭ����.
class ENGINE_API Timer
{
public:
	// �����ڿ��� Ÿ�̸��� ��ǥ �ð� ����.
	Timer(float targetTime);

	void Update(float deltaTime);

	// Ÿ�̸� �ʱ�ȭ.
	void Reset();

	//
	inline bool IsTimeOut() const { return elapsedTime >= targetTime; }
	inline void SetTime(float targetTime) { this->targetTime = targetTime; }


private:
	// ��� �ð�.
	float elapsedTime = 0.0f;

	// ��ǥ �ð�.
	float targetTime = 0.0f;
};