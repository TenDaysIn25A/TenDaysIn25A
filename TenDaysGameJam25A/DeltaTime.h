#pragma once
#include <windows.h>

// 参考資料:
// https://learn.microsoft.com/en-us/windows/win32/sysinfo/acquiring-high-resolution-time-stamps
// https://learn.microsoft.com/en-us/windows/win32/dxtecharts/game-timing-and-multicore-processors


class DeltaTime {
public:
	DeltaTime();
	void Initialize();
	void Update();

	float deltaTime;

private:
	// 周波数取得
	LARGE_INTEGER frequency;

	// 開始時刻を取得
	LARGE_INTEGER prevTime;

};
