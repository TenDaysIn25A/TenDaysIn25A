#include "SampleSceneMidzuki.h"
#include"Dlib.h"

SampleSceneMidzuki::SampleSceneMidzuki() { Initialize(); }

void SampleSceneMidzuki::Initialize() {
	// ここで各初期化を行う。

	samplePlayer.Initialize();

	player.Initialize();

	enemy.Initialize();

	currentDimension = DimensionState::TWO;
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
			break;
		} else if (player.parry.parryState == ParryState::JUST) {
			enemy.bullets[bi].isActive = false;
			break;
		}
	}

	CheckHitAll();
}

void SampleSceneMidzuki::CheckHitAll() {

	for (int bi = 0;bi < enemy.kBulletMax;bi++) {

		if (!enemy.bullets[bi].isActive) {
			continue;
		}

		if (player.parry.isParry) {
			if (Collision::BoxToBox(player.parry.transform.position, player.parry.width, player.parry.height, { enemy.bullets[bi].transform.position.x,0.0f }, enemy.bullets[bi].width, enemy.bullets[bi].height)) {

				float justArea = player.parry.transform.position.x - player.parry.kJustParryAbleGrace * enemy.bullets[bi].speed;

				if (enemy.bullets[bi].transform.position.x >= justArea) {
					player.parry.parryState = ParryState::JUST;
					player.parry.color = 0xFF0000FF;
					player.isUpDamage = true;
					player.damageUpTime = 150;
					
				} else {
					player.parry.parryState = ParryState::NORMAL;
					player.parry.color = 0xFFFF00FF;
				}
				enemy.bullets[bi].effect.SetColor(player.parry.color);

				enemy.bullets[bi].Deactive();
				enemy.bullets[bi].transform.position.x = -1000.0f;
				enemy.bullets[bi].transform.position.y = -1000.0f;
				break;

			} else {

			}
		}
	}


	for (int bi = 0;bi < enemy.kBulletMax;bi++) {

		if (enemy.bullets[bi].isActive) {

			if (Collision::BoxToBox(player.transform.position, player.width, player.height, { enemy.bullets[bi].transform.position.x,0.0f }, enemy.bullets[bi].width, enemy.bullets[bi].height)) {
				enemy.bullets[bi].effect.SetColor(0xFFFFFFFF);

				enemy.bullets[bi].Deactive();

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
}

void SampleSceneMidzuki::Draw() const {
	// ここで各描画を行う。

	// 一次元の背景_黒
	Novice::DrawBox(
		0, 320,
		1280, 80,
		0.0f,
		0x000000FF,
		kFillModeSolid
	);

	// ノーツの描画

	for (int bi = 0;bi < enemy.kBulletMax; bi++) {
		enemy.bullets[bi].Draw();
	}

	// プレイヤーの描画
	player.Draw();


	Novice::ScreenPrintf(0, 0, "parryable%d", player.parry.isParryAble);

	if (player.parry.parryState == ParryState::NONE) {
		Novice::ScreenPrintf(0, 16, "NONE");
	} else if (player.parry.parryState == ParryState::NORMAL) {
		Novice::ScreenPrintf(0, 16, "NOMAL");
	} else if (player.parry.parryState == ParryState::JUST) {
		Novice::ScreenPrintf(0, 16, "JUST");
	} else {
		Novice::ScreenPrintf(0, 16, "else");
	}


	Novice::ScreenPrintf(0, 32, "%d", player.isUpDamage);

	Novice::ScreenPrintf(0, 48, "%d", player.damageUpTime);

	Novice::ScreenPrintf(0, 64, "%d", player.bullets[0].damage);
	


}

void SampleSceneMidzuki::SetCamera() {
	// ここで各SetCameraを行う。

	samplePlayer.SetCamera(camera);
}
