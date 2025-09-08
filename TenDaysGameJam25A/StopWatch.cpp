#include "StopWatch.h"

StopWatch::StopWatch() { Initialize(); }

void StopWatch::Initialize() { elapsedTime_ = 0.0f; }

void StopWatch::Update() {
	deltaTime_.Update();
	elapsedTime_ += deltaTime_.deltaTime;
}

void StopWatch::Start() {
	if (isActive_) {
		return;
	}
	isActive_ = true;
}

void StopWatch::Stop() {
	isActive_ = false;
}

int StopWatch::GetTimeI() const { return static_cast<int>(elapsedTime_); }

float StopWatch::GetTimeF() const { return elapsedTime_; }
