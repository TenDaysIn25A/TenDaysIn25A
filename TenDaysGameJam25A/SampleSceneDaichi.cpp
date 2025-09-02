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
	input.Update();
	SetCamera();
	deltaTime.Update();

	samplePlayer.Update();

	if (input.GetKeyTrigger(DIK_0)) {
		if (currentDimension == DimensionState::ONE) {
			currentDimension = DimensionState::TWO;
		} else {
			currentDimension = DimensionState::ONE;
		}
	}
}

void SampleSceneDaichi::Draw() const {
	// ここで各描画を行う。

	samplePlayer.Draw();
	Novice::ScreenPrintf(0, 0, "FPS : %d", static_cast<int>(1.0f / deltaTime.deltaTime));
	Novice::ScreenPrintf(0, 20, "%s", currentDimension == DimensionState::ONE ? "one" : "two");
}

void SampleSceneDaichi::SetCamera() {
	// ここで各SetCameraを行う。

	samplePlayer.SetCamera(camera);
}

