#include "SampleSceneMidzuki.h"
#include"Dlib.h"

SampleSceneMidzuki::SampleSceneMidzuki() { Initialize(); }

void SampleSceneMidzuki::Initialize() {
	// ここで各初期化を行う。

	samplePlayer.Initialize();

	parry.Initialize();

	noteX = 360.0f;
	noteWidth = 80.0f;
	noteHeight = 80.0f;
	noteSpeed = 8.0f;
	noteRespawnTimer = 60;
	isNoteShoot = false;

	player.transform.position.x= 800.0f;
	player.transform.position.y = 360.0f;
	player.width = 80.0f;
	player.height = 80.0f;

	parry.transform.position.x = player.transform.position.x - player.width;
	parry.transform.position.y = player.transform.position.y;
	parry.width = player.width;
	parry.height = player.height;
	parryState = ParryState::NONE;

	
}

void SampleSceneMidzuki::Update() {
	// ここで各更新処理を行う
	SetCamera();

	input.Update();

	parry.Update(noteX, noteWidth, noteHeight,noteSpeed, parry.transform.position, parry.width, parry.height);



	if (parry.parryState == ParryState::NORMAL) {
		isNoteShoot = false;
		
	} else if (parry.parryState == ParryState::JUST) {
		isNoteShoot = false;
		
	}

	if (isNoteShoot) {
		noteX += noteSpeed;
	} else {
		noteX = 0.0f;
		noteRespawnTimer--;

		if (noteRespawnTimer == 0) {
			isNoteShoot = true;
			noteRespawnTimer = 60;
		}

	}

	if (noteX > 1280.0f) {
		noteX = 0.0f;
	}
}

void SampleSceneMidzuki::Draw() const {
	// ここで各描画を行う。

	// 一次元の背景_黒
	Novice::DrawBox(
		0, static_cast<int>(player.transform.position.y - player.width / 2.0f),
		1280, static_cast<int>(player.width),
		0.0f,
		0x000000FF,
		kFillModeSolid
	);

	// ノーツの描画

	if (isNoteShoot) {
		Novice::DrawBox(
			static_cast<int>(noteX - noteWidth / 2.0f),
			static_cast<int>(player.transform.position.y - noteHeight / 2.0f),
			static_cast<int>(noteWidth),
			static_cast<int>(noteHeight),
			0.0f, 0xFFFFFFFF,
			kFillModeSolid
		);
	}

	// プレイヤーの描画
	Novice::DrawBox(
		static_cast<int>(player.transform.position.x - player.width / 2.0f),
		static_cast<int>(player.transform.position.y - player.height / 2.0f),
		static_cast<int>(player.width),
		static_cast<int>(player.height),
		0.0f, 0x2222FFFF,
		kFillModeSolid
	);

	// パリィ可能範囲
	parry.Draw();
	
	//Novice::DrawBox(
	//	static_cast<int>(parry.transform.position.x - parry.width / 2.0f),
	//	static_cast<int>(parry.transform.position.y - parry.height / 2.0f),
	//	static_cast<int>(parry.width),
	//	static_cast<int>(parry.height),
	//	0.0f,
	//	0xFFFF00FF,
	//	kFillModeWireFrame
	//);

	if (parry.parryState == ParryState::NONE) {
		Novice::ScreenPrintf(0, 0, "NONE");
	} else if (parry.parryState == ParryState::NORMAL) {
		Novice::ScreenPrintf(0, 0, "NORMAL");
	} else if (parry.parryState == ParryState::JUST) {
		Novice::ScreenPrintf(0, 0, "JUST");
	}

	Novice::ScreenPrintf(0, 16, "isParryAbl : %d", parry.isParryAble);
	Novice::ScreenPrintf(0, 32, "canParryTimer : %d", parry.canJustTimer);
	Novice::ScreenPrintf(0, 48, "noteRespawnTimer : %d", noteRespawnTimer);
	Novice::ScreenPrintf(0, 64, "isNoteShoot : %d", isNoteShoot);
}

void SampleSceneMidzuki::SetCamera() {
	// ここで各SetCameraを行う。

	samplePlayer.SetCamera(camera);
}
