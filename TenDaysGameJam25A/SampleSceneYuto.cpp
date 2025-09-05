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

	click.Update();

	if (click.GetClickTrigger(0)) {
		Novice::ScreenPrintf(0,100,"Left:Trigger");
	}

	if (click.GetClick(0)) {
		Novice::ScreenPrintf(0,116,"Left:Press");
	}

	if (click.GetClickRelease(0)) {
		Novice::ScreenPrintf(0,132,"Left:Release");
	}


	if (input.GetKeyTrigger(DIK_0)) {
		if (currentDimension == DimensionState::ONE) {
			currentDimension = DimensionState::TWO;
		} else {
			currentDimension = DimensionState::ONE;
		}
	}

	enemy.Update();

	player.Update();

	for (int i = 0; i < player.kBulletMax; i++) {
		for (int j = 0; j < enemy.kBulletMax; j++) {
			if (player.bullets[i].isActive) {
				if (enemy.bullets[j].isActive) {
					if (Collision::BoxToBox(enemy.bullets[j].transform.position, enemy.bullets[j].width, enemy.bullets[j].height, player.bullets[i].transform.position, player.bullets[i].width, player.bullets[i].height)) {
						player.bullets[i].Deactive();
					}
				}
			}
		}
	}

	for (int i = 0; i < player.kBulletMax; i++) {
		if (player.bullets[i].isActive) {
			if (Collision::BoxToBox(enemy.transform.position, enemy.width, enemy.height, player.bullets[i].transform.position, player.bullets[i].width, player.bullets[i].height)) {
				enemy.TakeDamage(1);
				player.bullets[i].Deactive();
			}
		}
	}
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
	Novice::ScreenPrintf(0, 40, "%d/%d", enemy.hp, enemy.maxHp);
	Novice::ScreenPrintf(0, 60, "enemyPosX:%f,Y:%f", enemy.transform.position.x, enemy.transform.position.y);
	Novice::ScreenPrintf(0, 80, "playerPosX:%f,Y:%f", player.transform.position.x, player.transform.position.y);
}

void SampleSceneYuto::SetCamera() {
	// ここで各SetCameraを行う。

	player.SetCamera(camera);
}
