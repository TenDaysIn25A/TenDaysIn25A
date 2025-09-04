#include "SampleSceneDaichi.h"

SampleSceneDaichi::SampleSceneDaichi() { Initialize(); }

void SampleSceneDaichi::Initialize() {
	// ここで各初期化を行う。
	samplePlayer.Initialize();
	deltaTime.Initialize();
	button.Initialize(Novice::LoadTexture("./Resources/images/box.png"),128.0f,32.0f);
	currentDimension = DimensionState::ONE;
}

void SampleSceneDaichi::Update() {
	// ここで各更新処理を行う
	input.Update();
	SetCamera();
	deltaTime.Update();
	button.Update();
	samplePlayer.Update();

	if (input.GetKeyTrigger(DIK_F)) {
		if (currentDimension == DimensionState::ONE) {
			currentDimension = DimensionState::TWO;
		} else {
			currentDimension = DimensionState::ONE;
		}
	}
}

void SampleSceneDaichi::Draw() const {
	// ここで各描画を行う。
	// 背景描画
	// ----------------------------------------------------
	Novice::DrawBox(
		0, 120,
		1281, 480,
		0.0f,
		0x000000FF,
		kFillModeSolid
	);

	Novice::DrawBox(
		0, 120,
		1281, 480,
		0.0f,
		0xFFFFFFFF,
		kFillModeWireFrame
	);

	samplePlayer.Draw();
	button.Draw();
}

void SampleSceneDaichi::SetCamera() {
	// ここで各SetCameraを行う。

 	samplePlayer.SetCamera(camera);

}

