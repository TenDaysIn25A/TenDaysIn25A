#include "SampleSceneYuto.h"

SampleSceneYuto::SampleSceneYuto() { Initialize(); }

void SampleSceneYuto::Initialize() {
	// ここで各初期化を行う。

	player.Initialize();
	enemy.Initialize();
}

void SampleSceneYuto::Update() {
	// ここで各更新処理を行う
	SetCamera();

	input.Update();

	if (input.GetKeyTrigger(DIK_0)) {
		if (currentDimension == DimensionState::ONE) {
			currentDimension = DimensionState::TWO;
		} else {
			currentDimension = DimensionState::ONE;
		}
	}

	enemy.Update();

	player.Update();

	/*if (Collision::BoxToBox(enemy.transform.position, enemy.radius, enemy.radius, player.transform.position, player.radius,player.radius)) {
		enemy.TakeDamage(1);
	}*/
}

void SampleSceneYuto::Draw() const {
	// ここで各描画を行う。

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

	enemy.Draw();

	player.Draw();
	Novice::ScreenPrintf(0, 0, "FPS : %d", static_cast<int>(1.0f / deltaTime.deltaTime));
	Novice::ScreenPrintf(0, 20, "%s", currentDimension == DimensionState::ONE ? "one" : "two");
	Novice::ScreenPrintf(0, 40, "enemyPosX:%f,Y:%f", enemy.transform.position.x, enemy.transform.position.y);
	Novice::ScreenPrintf(0, 60, "playerPosX:%f,Y:%f", player.transform.position.x, player.transform.position.y);
}

void SampleSceneYuto::SetCamera() {
	// ここで各SetCameraを行う。

	player.SetCamera(camera);
}
