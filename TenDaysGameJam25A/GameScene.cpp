#include "GameScene.h"

GameScene::GameScene() { Initialize(); }

void GameScene::Initialize() {

	player.Initialize();

	enemy.Initialize();

	currentDimension = DimensionState::TWO;
}

void GameScene::Update() {
	// ここで各更新処理を行う

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
	
	SetCamera();

}

void GameScene::Draw() const {

}

void GameScene::SetCamera() {
	player.SetCamera(camera);
	enemy.SetCamera(camera);
}

void GameScene::CheckHitAll() {

	// プレイヤーの弾とエネミーの弾
	for (int i = 0; i < player.kBulletMax; i++) {
		for (int j = 0; j < enemy.kBulletMax; j++) {
			if (player.bullets[i].isActive) {
				if (enemy.bullets[j].isActive) {
					if (Collision::BoxToBox(
					        enemy.bullets[j].transform.position, enemy.bullets[j].width, enemy.bullets[j].height, player.bullets[i].transform.position, player.bullets[i].width,
					        player.bullets[i].height)) {
						player.bullets[i].Deactive();
					}
				}
			}
		}
	}

	// プレイヤーの弾とエネミー
	for (int i = 0; i < player.kBulletMax; i++) {
		if (player.bullets[i].isActive) {
			if (Collision::BoxToBox(enemy.transform.position, enemy.radius, enemy.radius, player.bullets[i].transform.position, player.bullets[i].width, player.bullets[i].height)) {
				enemy.TakeDamage(1);
				player.bullets[i].Deactive();
			}
		}
	}
}
