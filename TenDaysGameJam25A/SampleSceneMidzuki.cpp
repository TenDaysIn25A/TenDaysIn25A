#include "SampleSceneMidzuki.h"
#include"Dlib.h"

SampleSceneMidzuki::SampleSceneMidzuki() { Initialize(); }

void SampleSceneMidzuki::Initialize() {
	// ここで各初期化を行う。

	samplePlayer.Initialize();

	player.Initialize();

	noteX = 360.0f;
	noteWidth = 80.0f;
	noteHeight = 80.0f;
	noteSpeed = 8.0f;
	noteRespawnTimer = 60;
	isNoteShoot = false;

	

	currentDimension = DimensionState::ONE;
}

void SampleSceneMidzuki::Update() {
	// ここで各更新処理を行う
	SetCamera();

	input.Update();

	player.Update();

	if (player.parry.parryState == ParryState::NORMAL) {
		isNoteShoot = false;
		
	} else if (player.parry.parryState == ParryState::JUST) {
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

	CheckHitAll();
}

void SampleSceneMidzuki::CheckHitAll(){

	if (Collision::BoxToBox(player.parry.transform.position, player.parry.width, player.parry.height, { noteX,player.transform.position.y }, noteWidth, noteHeight)) {
		player.parry.isParryAble = true;

		if (noteX >= player.transform.position.x - player.width - player.parry.kJustParryAbleGrace * noteSpeed) {
			player.parry.isCanJust = true;
		}

	} else {
		player.parry.isParryAble = false;
	}

	if (Collision::BoxToBox(player.transform.position, player.width, player.height, { noteX,player.transform.position.y }, noteWidth, noteHeight)) {
		
		isNoteShoot = false;

		if (!player.isHit) {
			player.life--;
			noteX = 0.0f;
			
		}

		if (player.invincibleTimer == 0) {
			player.isHit = true;
		}

	} else {
		player.isHit = false;
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
	player.parry.Draw();

	Novice::DrawLine(
		static_cast<int>(player.transform.position.x - player.width / 2.0f - player.parry.kJustParryAbleGrace * noteSpeed),
		static_cast<int>(player.transform.position.y - player.height / 2.0f),
		static_cast<int>(player.transform.position.x - player.width / 2.0f - player.parry.kJustParryAbleGrace * noteSpeed),
		static_cast<int>(player.transform.position.y + player.height / 2.0f),
		0xFFFF00FF
	);
	
	//Novice::DrawBox(
	//	static_cast<int>(parry.transform.position.x - parry.width / 2.0f),
	//	static_cast<int>(parry.transform.position.y - parry.height / 2.0f),
	//	static_cast<int>(parry.width),
	//	static_cast<int>(parry.height),
	//	0.0f,
	//	0xFFFF00FF,
	//	kFillModeWireFrame
	//);

	if (player.parry.parryState == ParryState::NONE) {
		Novice::ScreenPrintf(0, 0, "NONE");
	} else if (player.parry.parryState == ParryState::NORMAL) {
		Novice::ScreenPrintf(0, 0, "NORMAL");
	} else if (player.parry.parryState == ParryState::JUST) {
		Novice::ScreenPrintf(0, 0, "JUST");
	}

	Novice::ScreenPrintf(0, 16, "isParryAbl : %d", player.parry.isParryAble);
	Novice::ScreenPrintf(0, 32, "canJustTimer : %d", player.parry.canJustTimer);
	Novice::ScreenPrintf(0, 48, "noteRespawnTimer : %d", noteRespawnTimer);
	Novice::ScreenPrintf(0, 64, "isNoteShoot : %d", isNoteShoot);
	Novice::ScreenPrintf(0, 80, "life : %d", player.life);
	Novice::ScreenPrintf(0, 96, "playerPosx : %f", player.transform.position.x);
}

void SampleSceneMidzuki::SetCamera() {
	// ここで各SetCameraを行う。

	samplePlayer.SetCamera(camera);
}
