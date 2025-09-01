#include "SampleSceneDaichi.h"

SampleSceneDaichi::SampleSceneDaichi() { Initialize(); }

void SampleSceneDaichi::Initialize() {
	// ここで各初期化を行う。

	samplePlayer.Initialize();
}

void SampleSceneDaichi::Update() {
	// ここで各更新処理を行う
	SetCamera();

	samplePlayer.Update();
}

void SampleSceneDaichi::Draw() const {
	// ここで各描画を行う。
	
	samplePlayer.Draw();
}

void SampleSceneDaichi::SetCamera() {
	// ここで各SetCameraを行う。

	samplePlayer.SetCamera(camera);
}

