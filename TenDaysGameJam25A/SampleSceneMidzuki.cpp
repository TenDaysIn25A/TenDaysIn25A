#include "SampleSceneMidzuki.h"
#include"Dlib.h"

SampleSceneMidzuki::SampleSceneMidzuki() { Initialize(); }

void SampleSceneMidzuki::Initialize() {
	// ここで各初期化を行う。

	samplePlayer.Initialize();

	player.Initialize();

	enemy.Initialize();

	currentDimension = DimensionState::ONE;
}

void SampleSceneMidzuki::Update() {
	// ここで各更新処理を行う
	SetCamera();

	input.Update();

	player.Update();

	enemy.Update();

	for (int bi = 0;bi < enemy.kBulletMax;bi++) {
		if (player.parry.parryState == ParryState::NORMAL) {
			enemy.bullets[bi].isActive = false;

		} else if (player.parry.parryState == ParryState::JUST) {
			enemy.bullets[bi].isActive = false;

		}

	
	}

	CheckHitAll();
}

void SampleSceneMidzuki::CheckHitAll(){

	for (int bi = 0;bi < enemy.kBulletMax;bi++) {
		if (Collision::BoxToBox(player.parry.transform.position, player.parry.width, player.parry.height, enemy.bullets[bi].transform.position, enemy.bullets[bi].width, enemy.bullets[bi].height)) {
			player.parry.isParryAble = true;

			if (enemy.bullets[bi].transform.position.x >= player.transform.position.x - player.width - player.parry.kJustParryAbleGrace * enemy.bullets[bi].transform.position.x) {
				player.parry.isCanJust = true;
			}

		} else {
			player.parry.isParryAble = false;
		}

		if (Collision::BoxToBox(player.transform.position, player.width, player.height, enemy.bullets[bi].transform.position, enemy.bullets[bi].width, enemy.bullets[bi].height)) {

			enemy.bullets[bi].isActive = false;

			if (!player.isHit) {
				player.life--;
				enemy.bullets[bi].transform.position.x = 0.0f;

			}

			if (player.invincibleTimer == 0) {
				player.isHit = true;
			}

		} else {
			player.isHit = false;
		}

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

	enemy.Draw();

	// プレイヤーの描画
	 
	
	 
	 
	//Novice::DrawBox(
	//	static_cast<int>(player.transform.position.x - player.width / 2.0f),
	//	static_cast<int>(player.transform.position.y - player.height / 2.0f),
	//	static_cast<int>(player.width),
	//	static_cast<int>(player.height),
	//	0.0f, 0x2222FFFF,
	//	kFillModeSolid
	//);

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
