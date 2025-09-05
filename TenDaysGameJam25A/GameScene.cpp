#include "GameScene.h"

GameScene::GameScene() { Initialize(); };

void GameScene::Initialize() {

	stage1Scene.Initialize();
	stage2Scene.Initialize();
	stage3Scene.Initialize();
	stage4Scene.Initialize();
	stage5Scene.Initialize();
	player.Initialize();
}

void GameScene::Update() {

	input.Update();
	click.Update();

	backGround.Update();

	if (player.currentStamina > player.kFirstConsumedStamina) {

		if (backGround.click.GetClickTrigger(1)) {

			if (!backGround.isChanging) {
				backGround.Activate();
				player.currentStamina -= player.kFirstConsumedStamina;
			}
		}

		if (backGround.click.GetClickRelease(1)) {

			if (!backGround.isChanging) {
				backGround.Activate();
				player.staminaRecoverCoolTime = player.kStaminaRecoverCoolTime;
			}
		}
	} 

	if (player.currentStamina < 0) {
		player.currentStamina = 0;
		backGround.Activate();
	}

	if (backGround.isChanging) {
		return;
	}

	if (input.GetKeyTrigger(DIK_I)) {
		Initialize();
	}

	if (currentDimension == DimensionState::ONE) {
		player.transform.position.y = 0.0f;
	}

	switch (currentStage) {

	case Stage::STAGE1:

		stage1Scene.Update();
		break;

	case Stage::STAGE2:
		stage2Scene.Update();
		break;

	case Stage::STAGE3:
		stage3Scene.Update();
		break;

	case Stage::STAGE4:
		stage4Scene.Update();
		break;

	case Stage::STAGE5:
		stage5Scene.Update();
		break;
	}

	player.Update();

	CheckHitAll();

	if (player.click.GetClickTrigger(0)) {
		if (currentDimension == DimensionState::ONE) {
			if (player.parry.parryState == ParryState::NONE) {
							player.miss.Activate({ player.transform.position.x, player.transform.position.y + 100.0f }, 0.0f);
			} else if (player.parry.parryState == ParryState::NORMAL) {
				player.nice.Activate({ player.transform.position.x, player.transform.position.y + 100.0f }, 0.0f);
			} else {
				player.just.Activate({ player.transform.position.x, player.transform.position.y + 100.0f }, 0.0f);
			}
		}
	}
}

void GameScene::CheckHitAll() {

	Novice::ScreenPrintf(116, 116, "%d", player.isInvinciblity);

	if (currentDimension == DimensionState::ONE) {
		for (int bi = 0; bi < enemy.kBulletMax; bi++) {

			if (!stage1Scene.enemy.bullets[bi].isActive) {
				continue;
			}
			
			//パリィの当たり判定
			if (player.parry.isParry) {
				if (Collision::BoxToBox(
					player.parry.transform.position, player.parry.width, player.parry.height, { stage1Scene.enemy.bullets[bi].transform.position.x, 0.0f }, stage1Scene.enemy.bullets[bi].width, stage1Scene.enemy.bullets[bi].height)) {

					float justArea = player.parry.transform.position.x - player.parry.kJustParryAbleGrace * stage1Scene.enemy.bullets[bi].speed;
					
					if (stage1Scene.enemy.bullets[bi].transform.position.x >= justArea) {
						player.parry.parryState = ParryState::JUST;
						player.parry.color = 0xFF0000FF;
						player.isUpDamage = true;
						player.damageUpTime = 150;
					} else {
						player.parry.parryState = ParryState::NORMAL;
						player.parry.color = 0xFFFF00FF;
					}

					stage1Scene.enemy.bullets[bi].effect.SetColor(player.parry.color);

					stage1Scene.enemy.bullets[bi].Deactive();
					stage1Scene.enemy.bullets[bi].transform.position.x = -1000.0f;
					stage1Scene.enemy.bullets[bi].transform.position.y = -1000.0f;
					break;
				}
			}
		}

		// プレイヤーとエネミーの弾の当たり判定（１次元）
		for (int bi = 0; bi < stage1Scene.enemy.kBulletMax; bi++) {
			if (stage1Scene.enemy.bullets[bi].isActive) {
				if (Collision::BoxToBox(player.transform.position, player.width, player.height, { stage1Scene.enemy.bullets[bi].transform.position.x, 0.0f }, stage1Scene.enemy.bullets[bi].width, stage1Scene.enemy.bullets[bi].height)) {

					stage1Scene.enemy.bullets[bi].Deactive();

					if (!player.isInvinciblity) {
						player.TakeDamage(1);
						stage1Scene.enemy.bullets[bi].transform.position.x = 0.0f;
						player.isInvinciblity = true;
					}

				}
			}
		}
	} else {
		// プレイヤーとエネミーの弾の当たり判定（２次元）
		for (int bi = 0; bi < stage1Scene.enemy.kBulletMax; bi++) {
			if (stage1Scene.enemy.bullets[bi].isActive) {
				// 縦幅を少し小さくして、ちょうど当たってるときは当たらないようにする
				if (Collision::BoxToBox(player.transform.position, player.width, player.height - 6.0f, stage1Scene.enemy.bullets[bi].transform.position, stage1Scene.enemy.bullets[bi].width, stage1Scene.enemy.bullets[bi].height)) {

					stage1Scene.enemy.bullets[bi].Deactive();

					if (!player.isInvinciblity) {
						player.TakeDamage(1);
						stage1Scene.enemy.bullets[bi].transform.position.x = 0.0f;
						player.isInvinciblity = true;
					}

				}
			}
		}
	}

	// プレイヤーの弾とエネミーの弾
	for (int i = 0; i < player.kBulletMax; i++) {
		for (int j = 0; j < stage1Scene.enemy.kBulletMax; j++) {
			if (player.bullets[i].isActive) {
				if (stage1Scene.enemy.bullets[j].isActive) {
					if (Collision::BoxToBox(
						stage1Scene.enemy.bullets[j].transform.position, stage1Scene.enemy.bullets[j].width, stage1Scene.enemy.bullets[j].height, player.bullets[i].transform.position, player.bullets[i].width,
						player.bullets[i].height)) {

						player.bullets[i].effect.SetColor(player.bullets[i].color);
						player.bullets[i].Deactive();
					}
				}
			}
		}
	}

	// プレイヤーの弾とエネミー
	for (int i = 0; i < player.kBulletMax; i++) {
		if (player.bullets[i].isActive) {
			if (Collision::BoxToBox(stage1Scene.enemy.transform.position, stage1Scene.enemy.width, stage1Scene.enemy.height, player.bullets[i].transform.position, player.bullets[i].width, player.bullets[i].height)) {
				stage1Scene.enemy.TakeDamage(player.bullets[i].damage);
				player.bullets[i].effect.SetColor(player.bullets[i].color);
				player.bullets[i].Deactive();
			}
		}
	}

}

void GameScene::Draw()const {

	Novice::DrawBox(0, 120, 1281, 480, 0.0f, 0x000000FF, kFillModeSolid);

	switch (currentStage) {

	case Stage::STAGE1:

		stage1Scene.Draw();

		Novice::ScreenPrintf(100, 16, "Stage1");

		break;

	case Stage::STAGE2:
		stage2Scene.Draw();

		Novice::ScreenPrintf(100, 16, "Stage2");

		break;

	case Stage::STAGE3:
		stage3Scene.Draw();

		Novice::ScreenPrintf(100, 16, "Stage3");

		break;

	case Stage::STAGE4:
		stage4Scene.Draw();

		Novice::ScreenPrintf(100, 16, "Stage4");

		break;

	case Stage::STAGE5:
		stage5Scene.Draw();

		Novice::ScreenPrintf(100, 16, "Stage5");

		break;
	}


	player.Draw();

	backGround.Draw();

	if (player.currentStamina >= 0.0f) {
		renderer.DrawSprite(player.stamina, player.currentStamina * 2, player.kStaminaHeight, 0.0f, player.grhandleStamina, 0x00FF00FF);
	}

	player.miss.Draw();
	player.nice.Draw();
	player.just.Draw();

	for (int i = 0;i < player.currentLife;i++) {
		renderer.DrawSprite(player.life[i], player.lifeWidth, player.lifeHeight, 0.0f,player.grhandleLife, 0xFF6666FF);
	}

	Novice::ScreenPrintf(640, 360, "%f", player.currentStamina);
}

void GameScene::ExchangeStage(Stage changeStage) {

	switch (changeStage) {

	case Stage::STAGE1:
		stage1Scene.Initialize();
		currentStage = Stage::STAGE1;

		break;

	case Stage::STAGE2:
		stage2Scene.Initialize();
		currentStage = Stage::STAGE2;

		break;

	case Stage::STAGE3:
		stage3Scene.Initialize();
		currentStage = Stage::STAGE3;

		break;

	case Stage::STAGE4:
		stage4Scene.Initialize();
		currentStage = Stage::STAGE4;

		break;

	case Stage::STAGE5:
		stage5Scene.Initialize();
		currentStage = Stage::STAGE5;

		break;
	}
}