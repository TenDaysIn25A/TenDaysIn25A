#include "GameScene.h"

GameScene::GameScene() { Initialize(); }

void GameScene::Initialize() {

	player.Initialize();

	enemy.Initialize();

	currentDimension = DimensionState::TWO;
}

void GameScene::Update() {
	// ここで各更新処理を行う
	if (isChanging) {
		return;
	}

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

	if (currentDimension == DimensionState::ONE) {
		player.transform.position.y = 0.0f;
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

	SetCamera();
}

void GameScene::Draw() const {

		Novice::DrawBox(
			0, 120,
			1281, 480,
			0.0f,
			0x000000FF,
			kFillModeSolid
		);

	enemy.Draw();

	player.Draw();
}

void GameScene::SetCamera() {
	player.SetCamera(camera);
	enemy.SetCamera(camera);
}

void GameScene::CheckHitAll() {

	if (currentDimension == DimensionState::ONE) {
		for (int bi = 0;bi < enemy.kBulletMax;bi++) {

			if (!enemy.bullets[bi].isActive) {
				continue;
			}
			// 
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

				}
			}
		}
		// プレイヤーとエネミーの弾の当たり判定（１次元）
		for (int bi = 0;bi < enemy.kBulletMax;bi++) {
			if (enemy.bullets[bi].isActive) {
				if (Collision::BoxToBox(player.transform.position, player.width, player.height, { enemy.bullets[bi].transform.position.x,0.0f }, enemy.bullets[bi].width, enemy.bullets[bi].height)) {

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
	} else {
		// プレイヤーとエネミーの弾の当たり判定（２次元）
		for (int bi = 0;bi < enemy.kBulletMax;bi++) {
			if (enemy.bullets[bi].isActive) {
				if (Collision::BoxToBox(player.transform.position, player.width, player.height, enemy.bullets[bi].transform.position, enemy.bullets[bi].width, enemy.bullets[bi].height)) {

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
				enemy.TakeDamage(player.bullets[i].damage);
				player.bullets[i].Deactive();
			}
		}
	}
}
