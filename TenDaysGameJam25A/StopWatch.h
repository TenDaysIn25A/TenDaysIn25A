#pragma once
#include "DeltaTime.h"

class StopWatch {
public:
	StopWatch();
	~StopWatch() = default;

	void Initialize();
	void Update();
	
	void Start();
	void Stop();
	
	int GetTimeI() const;
	float GetTimeF() const;

private:
	bool isActive_;
	float elapsedTime_;
	DeltaTime deltaTime_;
};

