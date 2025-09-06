#include "SampleSceneMidzuki.h"
#include"Dlib.h"

SampleSceneMidzuki::SampleSceneMidzuki() { Initialize(); }

void SampleSceneMidzuki::Initialize() {
	// ここで各初期化を行う。

	samplePlayer.Initialize();

	player.Initialize();

	enemy.Initialize();

	light.Initialize();

	currentDimension = DimensionState::TWO;

	box.position = { -150,0.0f };
	boxWidth = 80.0f;
	boxHeight = 160.0f;


	playerLeftTop.position = { player.transform.position.x - player.width / 2.0f,player.transform.position.y + player.height / 2.0f };
	playerRightTop.position = { player.transform.position.x + player.width / 2.0f,player.transform.position.y + player.height / 2.0f };
	playerLeftBottom.position = { player.transform.position.x - player.width / 2.0f,player.transform.position.y - player.height / 2.0f };
	playerRightBottom.position = { player.transform.position.x + player.width / 2.0f,player.transform.position.y - player.height / 2.0f };

	radius = { 5.0f,5.0f };

	leftTopColor = 0xFFFFFFFF;
	rightTopColor = 0xFFFFFFFF;
	leftBottomColor = 0xFFFFFFFF;
	rightBottomColor = 0xFFFFFFFF;
}

void SampleSceneMidzuki::Update() {
	// ここで各更新処理を行う
	SetCamera();

	input.Update();

	player.Update();

	playerLeftTop.position = { player.transform.position.x - player.width / 2.0f,player.transform.position.y + player.height / 2.0f };
	playerRightTop.position = { player.transform.position.x + player.width / 2.0f,player.transform.position.y + player.height / 2.0f };
	playerLeftBottom.position = { player.transform.position.x - player.width / 2.0f,player.transform.position.y - player.height / 2.0f };
	playerRightBottom.position = { player.transform.position.x + player.width / 2.0f,player.transform.position.y - player.height / 2.0f };

	enemy.Update();

	if (light.isPlayerInTheShadow(box,boxWidth,boxHeight,playerLeftTop.position)) {
		leftTopColor = 0xFF0000FF;
	} else {
		leftTopColor = 0xFFFFFFFF;
	}

	if (light.isPlayerInTheShadow(box,boxWidth,boxHeight,playerRightTop.position)) {
		rightTopColor = 0xFF0000FF;
	} else {
		rightTopColor = 0xFFFFFFFF;
	}

	if (light.isPlayerInTheShadow(box, boxWidth, boxHeight, playerLeftBottom.position)) {
		leftBottomColor = 0xFF0000FF;
	} else {
		leftBottomColor = 0xFFFFFFFF;
	}

	if (light.isPlayerInTheShadow(box, boxWidth, boxHeight, playerRightBottom.position)) {
		rightBottomColor = 0xFF0000FF;
	} else {
		rightBottomColor = 0xFFFFFFFF;
	}

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

				if (!player.isInvinciblity) {
					player.currentLife--;
					enemy.bullets[bi].transform.position.x = 0.0f;

				}

				if (player.invincibleTimer == 0) {
					player.isInvinciblity = true;
				}

			} else {
				player.isInvinciblity = false;
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
	
	renderer.DrawEllipse(playerLeftTop, radius, { 0,0 }, 0.0f, leftTopColor, kFillModeSolid);
	renderer.DrawEllipse(playerRightTop, radius, { 0,0 }, 0.0f, rightTopColor, kFillModeSolid);
	renderer.DrawEllipse(playerLeftBottom, radius, { 0,0 }, 0.0f, leftBottomColor, kFillModeSolid);
	renderer.DrawEllipse(playerRightBottom, radius, { 0,0 }, 0.0f, rightBottomColor, kFillModeSolid);
	renderer.DrawEllipse(light.transform, light.radius, { 0,0 }, 0.0f, 0xFFFF00FF, kFillModeSolid);

	renderer.DrawBox(box, boxWidth, boxHeight, 0.0f, 0xFFFFFFFF, kFillModeSolid);
	
}

void SampleSceneMidzuki::SetCamera() {
	// ここで各SetCameraを行う。

	samplePlayer.SetCamera(camera);
}
