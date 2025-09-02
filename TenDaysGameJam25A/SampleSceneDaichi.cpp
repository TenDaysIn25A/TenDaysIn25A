#include "SampleSceneDaichi.h"

SampleSceneDaichi::SampleSceneDaichi() { Initialize(); }

void SampleSceneDaichi::Initialize() {
	// ここで各初期化を行う。

	samplePlayer.Initialize();
	deltaTime.Initialize();
	
	currentDimension = DimensionState::ONE;
}

void SampleSceneDaichi::Update() {
	// ここで各更新処理を行う
	SetCamera();
	deltaTime.Update();

	samplePlayer.Update();
	
}

void SampleSceneDaichi::Draw() const {
	// ここで各描画を行う。

	samplePlayer.Draw();
	Novice::ScreenPrintf(0, 0, "FPS : %d", static_cast<int>(1.0f / deltaTime.deltaTime));
}

void SampleSceneDaichi::SetCamera() {
	// ここで各SetCameraを行う。

	samplePlayer.SetCamera(camera);
}

