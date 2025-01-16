#pragma once

#include "Core.h"

// 초시계 클래스.
class ENGINE_API Timer
{
public:
	// 생성자에서 타이머의 목표 시간 설정.
	Timer(float targetTime);

	void Update(float deltaTime);

	// 타이머 초기화.
	void Reset();

	//
	inline bool IsTimeOut() const { return elapsedTime >= targetTime; }
	inline void SetTime(float targetTime) { this->targetTime = targetTime; }


private:
	// 경과 시간.
	float elapsedTime = 0.0f;

	// 목표 시간.
	float targetTime = 0.0f;
};