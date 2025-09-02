#include "SampleSceneMidzuki.h"
#include"Dlib.h"

SampleSceneMidzuki::SampleSceneMidzuki() { Initialize(); }

void SampleSceneMidzuki::Initialize() {
	// ここで各初期化を行う。

	samplePlayer.Initialize();

	parry.Initialize();

	noteX = 200.0f;
	noteWidth = 50.0f;
	noteHeight = 50.0f;

	player.x = 400.0f;
	player.y = 200.0f;
	playerWidth = 50.0f;
	playerHeight = 50.0f;
}

void SampleSceneMidzuki::Update() {
	// ここで各更新処理を行う
	SetCamera();

	parry.Update(noteX, noteWidth, noteHeight, player, playerWidth, playerHeight);

	noteX += 4.0f;

	if (noteX > 1280.0f) {
		noteX = 0.0f;
	}

	if (input.GetKey(DIK_W)) {
		player.y -= 4.0f;
	}

	if (input.GetKey(DIK_A)) {
		player.x -= 4.0f;
	}

	if (input.GetKey(DIK_S)) {
		player.y += 4.0f;
	}

	if (input.GetKey(DIK_D)) {
		player.x += 4.0f;
	}
}

void SampleSceneMidzuki::Draw() const {
	// ここで各描画を行う。

	samplePlayer.Draw();

	// ノーツの描画
	Novice::DrawBox(
		static_cast<int>(noteX - noteWidth / 2.0f),
		static_cast<int>(player.y - noteHeight / 2.0f),
		static_cast<int>(noteWidth),
		static_cast<int>(noteHeight),
		0.0f, 0xFFFFFFFF,
		kFillModeSolid
	);

	// プレイヤーの描画
	Novice::DrawBox(
		static_cast<int>(player.x - playerWidth / 2.0f),
		static_cast<int>(player.y - playerHeight / 2.0f),
		static_cast<int>(playerWidth),
		static_cast<int>(playerHeight),
		0.0f, 0xFFFFFFFF,
		kFillModeSolid
	);

	if (parry.parryState == ParryState::NONE) {
		Novice::ScreenPrintf(0, 0, "NONE");
	} else if (parry.parryState == ParryState::NORMAL) {
		Novice::ScreenPrintf(0, 0, "NORMAL");
	} else if (parry.parryState == ParryState::JUST) {
		Novice::ScreenPrintf(0, 0, "JUST");
	}

	Novice::ScreenPrintf(0, 16, "isParryAbl : %d", parry.isParryAble);
	Novice::ScreenPrintf(0, 32, "canParryTimer : %d", parry.canParryTimer);
}

void SampleSceneMidzuki::SetCamera() {
	// ここで各SetCameraを行う。

	samplePlayer.SetCamera(camera);
}
