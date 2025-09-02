#include "DeltaTime.h"

DeltaTime::DeltaTime() { }

void DeltaTime::Initialize() {
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&prevTime);
}

void DeltaTime::Update() { 
	// 現在の時刻を取得
	LARGE_INTEGER currentTime; 
	QueryPerformanceCounter(&currentTime);

	deltaTime = static_cast <float> (currentTime.QuadPart - prevTime.QuadPart) / static_cast<float>(frequency.QuadPart);

	prevTime = currentTime;
}
