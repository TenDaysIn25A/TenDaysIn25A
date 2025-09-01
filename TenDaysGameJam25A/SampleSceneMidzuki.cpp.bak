#include "SampleSceneMidzuki.h"

SampleSceneMidzuki::SampleSceneMidzuki() { Initialize(); }

void SampleSceneMidzuki::Initialize() {
	// ここで各初期化を行う。

	samplePlayer.Initialize();
}

void SampleSceneMidzuki::Update() {
	// ここで各更新処理を行う
	SetCamera();

	samplePlayer.Update();
}

void SampleSceneMidzuki::Draw() const {
	// ここで各描画を行う。

	samplePlayer.Draw();
}

void SampleSceneMidzuki::SetCamera() {
	// ここで各SetCameraを行う。

	samplePlayer.SetCamera(camera);
}
