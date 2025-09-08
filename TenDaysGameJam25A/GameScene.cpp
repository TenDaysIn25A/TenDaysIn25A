#include "GameScene.h"

GameScene::GameScene() { Initialize(); };

void GameScene::Initialize() {

	stage1Scene.Initialize();
	stage2Scene.Initialize();
	stage3Scene.Initialize();
	stage4Scene.Initialize();
	stage5Scene.Initialize();
	backGround.Initialize();
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

		if (backGround.dimansionState == DimensionState::ONE) {
			if (backGround.click.GetClickRelease(1)) {

				if (!backGround.isChanging) {
					backGround.Activate();
					player.staminaRecoverCoolTime = player.kStaminaRecoverCoolTime;
				}
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

	Vector2 reactionPosition = { player.transform.position.x, player.transform.position.y + 100.0f };
	if (player.click.GetClickTrigger(0)) {
		if (currentDimension == DimensionState::ONE) {
			if (player.parry.parryState == ParryState::NONE) {
				if (player.transform.position.x < -640.0f + player.just.width / 2.0f - 128.0f) {
					reactionPosition.x = -640.0f + player.just.width / 2.0f - 128.0f;
				}
				player.miss.Activate({ reactionPosition.x, reactionPosition.y }, 0.0f);
			} else if (player.parry.parryState == ParryState::NORMAL) {
				if (player.transform.position.x < -640.0f + player.just.width / 2.0f - 72.0f) {
					reactionPosition.x = -640.0f + player.just.width / 2.0f - 72.0f;
				}
				player.nice.Activate({ reactionPosition.x, reactionPosition.y }, 0.0f);
			} else {
				if (player.transform.position.x < -640.0f + player.just.width / 2.0f) {
					reactionPosition.x = -640.0f + player.just.width / 2.0f;
				}
				player.just.Activate({ reactionPosition.x, reactionPosition.y }, 0.0f);
			}
		}
	}
}

void GameScene::CheckHitAll() {

	//Novice::ScreenPrintf(148, 116, "%d", player.isInvinciblity);

	switch (currentStage) {

	case Stage::STAGE1:
		Stage1CheckHit();
		
		break;

	case Stage::STAGE2:
		Stage2CheckHit();
		break;

	case Stage::STAGE3:
		Stage3CheckHit();
		break;

	case Stage::STAGE4:
		
		break;

	case Stage::STAGE5:
		
		break;
	}
	

	
}

//ステージ1の当たり判定
void GameScene::Stage1CheckHit() {
	if (currentDimension == DimensionState::ONE) {
		for (int bi = 0; bi < stage1Scene.stage1Boss.kBulletMax; bi++) {

			if (!stage1Scene.stage1Boss.bullets[bi].isActive) {
				continue;
			}

			//パリィの当たり判定
			if (player.parry.isParry) {
				if (Collision::BoxToBox(
					player.parry.transform.position, player.parry.width, player.parry.height, { stage1Scene.stage1Boss.bullets[bi].transform.position.x, 0.0f }, stage1Scene.stage1Boss.bullets[bi].width, stage1Scene.stage1Boss.bullets[bi].height)) {

					float justArea = player.parry.transform.position.x + player.parry.kJustParryAbleGrace * stage1Scene.stage1Boss.bullets[bi].speed;

					if (stage1Scene.stage1Boss.bullets[bi].transform.position.x <= justArea) {
						player.parry.parryState = ParryState::JUST;
						player.parry.color = 0xFF0000FF;
						player.isUpDamage = true;
						player.damageUpTime = 150;
					} else {
						player.parry.parryState = ParryState::NORMAL;
						player.parry.color = 0xFFFF00FF;
						player.magazine++;
					}

					stage1Scene.stage1Boss.bullets[bi].Deactive();

				} else {

				}

				if (player.parry.parryState == ParryState::NONE) {
					player.currentStamina -= player.kMissConsumedStamina;
				}

			}
		}

		// プレイヤーとエネミーの弾の当たり判定（１次元）
		for (int bi = 0; bi < stage1Scene.stage1Boss.kBulletMax; bi++) {
			if (stage1Scene.stage1Boss.bullets[bi].isActive) {
				if (Collision::BoxToBox(player.transform.position, player.width, player.hitBoxHeight, { stage1Scene.stage1Boss.bullets[bi].transform.position.x, 0.0f }, stage1Scene.stage1Boss.bullets[bi].width, stage1Scene.stage1Boss.bullets[bi].height)) {

					stage1Scene.stage1Boss.bullets[bi].Deactive();

					if (!player.isInvinciblity) {
						player.TakeDamage(1);
						stage1Scene.stage1Boss.bullets[bi].transform.position.x = 0.0f;
						player.isInvinciblity = true;
					}

				}
			}
		}
	} else {
		// プレイヤーとエネミーの弾の当たり判定（２次元）
		for (int bi = 0; bi < stage1Scene.stage1Boss.kBulletMax; bi++) {
			if (stage1Scene.stage1Boss.bullets[bi].isActive) {
				// 縦幅を少し小さくして、ちょうど当たってるときは当たらないようにする
				if (Collision::BoxToBox(player.transform.position, player.hitBoxWidth, player.hitBoxWidth - 6.0f, stage1Scene.stage1Boss.bullets[bi].transform.position, stage1Scene.stage1Boss.bullets[bi].width, stage1Scene.stage1Boss.bullets[bi].height)) {

					stage1Scene.stage1Boss.bullets[bi].Deactive();

					if (!player.isInvinciblity) {
						player.TakeDamage(1);
						stage1Scene.stage1Boss.bullets[bi].transform.position.x = 0.0f;
						player.isInvinciblity = true;
					}
				}
			}
		}
	}

	// プレイヤーの弾とエネミーの弾
	for (int i = 0; i < player.kBulletMax; i++) {
		for (int j = 0; j < stage1Scene.stage1Boss.kBulletMax; j++) {
			if (player.bullets[i].isActive) {
				if (stage1Scene.stage1Boss.bullets[j].isActive) {
					if (Collision::BoxToBox(
						stage1Scene.stage1Boss.bullets[j].transform.position, stage1Scene.stage1Boss.bullets[j].width, stage1Scene.stage1Boss.bullets[j].height, player.bullets[i].transform.position, player.bullets[i].width,
						player.bullets[i].height)) {
						if (stage1Scene.stage1Boss.bullets[j].type == BulletType::HERMITCLAB) {

							player.bullets[i].effect.SetColor(player.bullets[i].color);
							player.bullets[i].Deactive();

							stage1Scene.stage1Boss.bullets[j].PlayerBulletHit();
						} else {
							player.bullets[i].effect.SetColor(player.bullets[i].color);
							player.bullets[i].Deactive();

							if (player.isUpDamage) {
								stage1Scene.stage1Boss.bullets[j].Deactive();
							}
						}

					}
				}
			}
		}
	}

	// プレイヤーの弾とエネミー
	for (int i = 0; i < player.kBulletMax; i++) {
		if (player.bullets[i].isActive) {
			if (Collision::BoxToBox(stage1Scene.stage1Boss.transform.position, stage1Scene.stage1Boss.width, stage1Scene.stage1Boss.height, player.bullets[i].transform.position, player.bullets[i].width, player.bullets[i].height)) {
				stage1Scene.stage1Boss.TakeDamage(player.bullets[i].damage);
				player.bullets[i].effect.SetColor(player.bullets[i].color);
				player.bullets[i].Deactive();
			}
		}
	}

	//光とプレイヤー(プレイヤーの4頂点が、光がさえぎられていない領域にあるか)
	if (currentDimension == DimensionState::TWO) {
		if (stage1Scene.stage1Boss.light[0].isActive) {
			if (stage1Scene.stage1Boss.light[0].isPlayerInTheShadow(stage1Scene.stage1Boss.bullets[60].transform, stage1Scene.stage1Boss.bullets[60].width, stage1Scene.stage1Boss.bullets[60].height, player.leftTop.position)) {

			} else {
				player.TakeDamage(2);
			}

			if (stage1Scene.stage1Boss.light[0].isPlayerInTheShadow(stage1Scene.stage1Boss.bullets[60].transform, stage1Scene.stage1Boss.bullets[60].width, stage1Scene.stage1Boss.bullets[60].height, player.rightTop.position)) {

			} else {
				player.TakeDamage(2);
			}

			if (stage1Scene.stage1Boss.light[0].isPlayerInTheShadow(stage1Scene.stage1Boss.bullets[60].transform, stage1Scene.stage1Boss.bullets[60].width, stage1Scene.stage1Boss.bullets[60].height, player.leftBottom.position)) {

			} else {
				player.TakeDamage(2);
			}

			if (stage1Scene.stage1Boss.light[0].isPlayerInTheShadow(stage1Scene.stage1Boss.bullets[60].transform, stage1Scene.stage1Boss.bullets[60].width, stage1Scene.stage1Boss.bullets[60].height, player.rightBottom.position)) {

			} else {
				player.TakeDamage(2);
			}
		}
	} else {

		if (stage1Scene.stage1Boss.light[0].isActive) {

			if (stage1Scene.stage1Boss.bullets[60].isActive) {

				if (player.transform.position.x <= stage1Scene.stage1Boss.bullets[60].transform.position.x) {

				} else {
					player.TakeDamage(2);
				}

			} else {
				player.TakeDamage(2);
			}
		}

	}
}

//ステージ2の当たり判定
void GameScene::Stage2CheckHit() {
	if (currentDimension == DimensionState::ONE) {
		for (int bi = 0; bi < stage2Scene.stage2Boss.kBulletMax; bi++) {

			if (!stage2Scene.stage2Boss.bullets[bi].isActive) {
				continue;
			}

			//パリィの当たり判定
			if (player.parry.isParry) {
				if (Collision::BoxToBox(
					player.parry.transform.position, player.parry.width, player.parry.height, { stage2Scene.stage2Boss.bullets[bi].transform.position.x, 0.0f }, stage2Scene.stage2Boss.bullets[bi].width, stage2Scene.stage2Boss.bullets[bi].height)) {
					float justArea = player.parry.transform.position.x + player.parry.kJustParryAbleGrace * stage2Scene.stage2Boss.bullets[bi].speed;
					if (stage2Scene.stage2Boss.bullets[bi].transform.position.x <= justArea) {
						player.parry.parryState = ParryState::JUST;
						player.parry.color = 0xFF0000FF;
						player.isUpDamage = true;
						player.damageUpTime = 150;
					} else {
						player.parry.parryState = ParryState::NORMAL;
						player.parry.color = 0xFFFF00FF;
						player.magazine++;
					}
					stage2Scene.stage2Boss.bullets[bi].Deactive();
				} else {

				}

				if (player.parry.parryState == ParryState::NONE) {
					player.currentStamina -= player.kMissConsumedStamina;
				}
			}
		}

		// プレイヤーとエネミーの弾の当たり判定（１次元）
		for (int bi = 0; bi < stage2Scene.stage2Boss.kBulletMax; bi++) {
			if (stage2Scene.stage2Boss.bullets[bi].isActive) {
				if (Collision::BoxToBox(player.transform.position, player.width, player.hitBoxHeight, { stage2Scene.stage2Boss.bullets[bi].transform.position.x, 0.0f }, stage2Scene.stage2Boss.bullets[bi].width, stage2Scene.stage2Boss.bullets[bi].height)) {
					stage2Scene.stage2Boss.bullets[bi].Deactive();

					if (!player.isInvinciblity) {
						player.TakeDamage(1);
						stage2Scene.stage2Boss.bullets[bi].transform.position.x = 0.0f;
						player.isInvinciblity = true;
					}
				}
			}
		}
	} else {
		// プレイヤーとエネミーの弾の当たり判定（２次元）
		for (int bi = 0; bi < stage2Scene.stage2Boss.kBulletMax; bi++) {
			if (stage2Scene.stage2Boss.bullets[bi].isActive) {
				// 縦幅を少し小さくして、ちょうど当たってるときは当たらないようにする
				if (Collision::BoxToBox(player.transform.position, player.hitBoxWidth, player.hitBoxWidth - 6.0f, stage2Scene.stage2Boss.bullets[bi].transform.position, stage2Scene.stage2Boss.bullets[bi].width, stage2Scene.stage2Boss.bullets[bi].height)) {

					stage2Scene.stage2Boss.bullets[bi].Deactive();

					if (!player.isInvinciblity) {
						player.TakeDamage(1);
						stage2Scene.stage2Boss.bullets[bi].transform.position.x = 0.0f;
						player.isInvinciblity = true;
					}
				}
			}
		}
	}

	// プレイヤーの弾とエネミーの弾
	for (int i = 0; i < player.kBulletMax; i++) {
		for (int j = 0; j < stage2Scene.stage2Boss.kBulletMax; j++) {
			if (player.bullets[i].isActive) {
				if (stage2Scene.stage2Boss.bullets[j].isActive) {
					if (Collision::BoxToBox(
						stage2Scene.stage2Boss.bullets[j].transform.position, stage2Scene.stage2Boss.bullets[j].width, stage2Scene.stage2Boss.bullets[j].height, player.bullets[i].transform.position, player.bullets[i].width,
						player.bullets[i].height)) {

						player.bullets[i].effect.SetColor(player.bullets[i].color);
						player.bullets[i].Deactive();

						if (player.isUpDamage) {
							stage2Scene.stage2Boss.bullets[j].Deactive();
						}
					}
				}
			}
		}
	}

	// プレイヤーの弾とエネミー
	for (int i = 0; i < player.kBulletMax; i++) {
		if (player.bullets[i].isActive) {
			if (Collision::BoxToBox(stage2Scene.stage2Boss.transform.position, stage2Scene.stage2Boss.width, stage2Scene.stage2Boss.height, player.bullets[i].transform.position, player.bullets[i].width, player.bullets[i].height)) {
				stage2Scene.stage2Boss.TakeDamage(player.bullets[i].damage);
				player.bullets[i].effect.SetColor(player.bullets[i].color);
				player.bullets[i].Deactive();
			}
		}
	}
}

void GameScene::Stage3CheckHit() {

	if (currentDimension == DimensionState::ONE) {
		for (int bi = 0; bi < stage3Scene.stage3Boss.kBulletMax; bi++) {

			if (!stage3Scene.stage3Boss.bullets[bi].isActive) {
				continue;
			}

			//パリィの当たり判定
			if (player.parry.isParry) {
				if (Collision::BoxToBox(
					player.parry.transform.position, player.parry.width, player.parry.height, { stage3Scene.stage3Boss.bullets[bi].transform.position.x, 0.0f }, stage3Scene.stage3Boss.bullets[bi].width, stage3Scene.stage3Boss.bullets[bi].height)) {
					float justArea = player.parry.transform.position.x + player.parry.kJustParryAbleGrace * stage3Scene.stage3Boss.bullets[bi].speed;
					if (stage3Scene.stage3Boss.bullets[bi].transform.position.x <= justArea) {
						player.parry.parryState = ParryState::JUST;
						player.parry.color = 0xFF0000FF;
						player.isUpDamage = true;
						player.damageUpTime = 150;
					} else {
						player.parry.parryState = ParryState::NORMAL;
						player.parry.color = 0xFFFF00FF;
						player.magazine++;
					}
					stage3Scene.stage3Boss.bullets[bi].Deactive();
				} else {

				}

				if (player.parry.parryState == ParryState::NONE) {
					player.currentStamina -= player.kMissConsumedStamina;
				}
			}
		}

		// プレイヤーとエネミーの弾の当たり判定（１次元）
		for (int bi = 0; bi < stage3Scene.stage3Boss.kBulletMax; bi++) {
			if (stage3Scene.stage3Boss.bullets[bi].isActive) {
				if (Collision::BoxToBox(player.transform.position, player.width, player.hitBoxHeight, { stage3Scene.stage3Boss.bullets[bi].transform.position.x, 0.0f }, stage3Scene.stage3Boss.bullets[bi].width, stage3Scene.stage3Boss.bullets[bi].height)) {
					stage3Scene.stage3Boss.bullets[bi].Deactive();

					if (!player.isInvinciblity) {
						player.TakeDamage(1);
						stage3Scene.stage3Boss.bullets[bi].transform.position.x = 0.0f;
						player.isInvinciblity = true;
					}
				}
			}
		}
	} else {
		// プレイヤーとエネミーの弾の当たり判定（２次元）
		for (int bi = 0; bi < stage3Scene.stage3Boss.kBulletMax; bi++) {
			if (stage3Scene.stage3Boss.bullets[bi].isActive) {
				// 縦幅を少し小さくして、ちょうど当たってるときは当たらないようにする
				if (Collision::BoxToBox(player.transform.position, player.hitBoxWidth, player.hitBoxWidth - 6.0f, stage3Scene.stage3Boss.bullets[bi].transform.position, stage3Scene.stage3Boss.bullets[bi].width, stage3Scene.stage3Boss.bullets[bi].height)) {

					stage3Scene.stage3Boss.bullets[bi].Deactive();

					if (!player.isInvinciblity) {
						player.TakeDamage(1);
						stage3Scene.stage3Boss.bullets[bi].transform.position.x = 0.0f;
						player.isInvinciblity = true;
					}
				}
			}
		}
	}

	// プレイヤーの弾とエネミーの弾
	for (int i = 0; i < player.kBulletMax; i++) {
		for (int j = 0; j < stage3Scene.stage3Boss.kBulletMax; j++) {
			if (player.bullets[i].isActive) {
				if (stage3Scene.stage3Boss.bullets[j].isActive) {
					if (Collision::BoxToBox(
						stage3Scene.stage3Boss.bullets[j].transform.position, stage3Scene.stage3Boss.bullets[j].width, stage3Scene.stage3Boss.bullets[j].height, player.bullets[i].transform.position, player.bullets[i].width,
						player.bullets[i].height)) {

						player.bullets[i].effect.SetColor(player.bullets[i].color);
						player.bullets[i].Deactive();

						if (player.isUpDamage) {
							stage3Scene.stage3Boss.bullets[j].Deactive();
						}
					}
				}
			}
		}
	}

	// プレイヤーの弾とエネミー
	for (int i = 0; i < player.kBulletMax; i++) {
		if (player.bullets[i].isActive) {
			if (Collision::BoxToBox(stage3Scene.stage3Boss.transform.position, stage3Scene.stage3Boss.width, stage3Scene.stage3Boss.height, player.bullets[i].transform.position, player.bullets[i].width, player.bullets[i].height)) {
				stage3Scene.stage3Boss.TakeDamage(player.bullets[i].damage);
				player.bullets[i].effect.SetColor(player.bullets[i].color);
				player.bullets[i].Deactive();
			}
		}
	}
}

void GameScene::Draw()const {

	Novice::DrawBox(0, 120, 1281, 480, 0.0f, 0x000000FF, kFillModeSolid);

	//Novice::ScreenPrintf(132, 132, "%d", stage1Scene.stage1Boss.light.lightNotice);
	//Novice::ScreenPrintf(148, 132, "%d", stage1Scene.stage1Boss.shotTimer);
	
	for (int i = 0; i < stage1Scene.stage1Boss.kLightMax; i++) {
		if (stage1Scene.stage1Boss.light[i].lightNotice) {
			Transform2D lightBg;
			lightBg.position.x = 0.0f;
			lightBg.position.y = 0.0f;
			renderer.DrawBox(lightBg, 1280.0f, 720.0f, 0.0f, stage1Scene.stage1Boss.light[i].backGroundColor, kFillModeSolid);
		}
	}

	switch (currentStage) {

	case Stage::STAGE1:


		stage1Scene.Draw();

		//Novice::ScreenPrintf(100, 16, "Stage1");

		break;

	case Stage::STAGE2:
		//stage2Boss.hpGauge.Draw();

		stage2Scene.Draw();

		//Novice::ScreenPrintf(100, 16, "Stage2");

		break;

	case Stage::STAGE3:
		stage3Scene.Draw();

		//Novice::ScreenPrintf(100, 16, "Stage3");

		break;

	case Stage::STAGE4:
		stage4Scene.Draw();

		//Novice::ScreenPrintf(100, 16, "Stage4");

		break;

	case Stage::STAGE5:
		stage5Scene.Draw();

		//Novice::ScreenPrintf(100, 16, "Stage5");

		break;
	}


	player.Draw();

	backGround.Draw();

	if (player.currentStamina >= 0.0f) {
		renderer.DrawSprite(player.stamina, player.currentStamina * 1.3f, player.kStaminaHeight, 0.0f, player.grhandleStamina, 0x00FF00FF);
	}

	player.miss.Draw();
	player.nice.Draw();
	player.just.Draw();

	switch (currentStage) {

	case Stage::STAGE1:

		stage1Scene.stage1Boss.hpGauge.Draw();

		break;

	case Stage::STAGE2:

		stage2Scene.stage2Boss.hpGauge.Draw();

		break;
	}

	for (int i = 0;i < player.currentLife;i++) {
		renderer.DrawSprite(player.life[i], player.lifeWidth, player.lifeHeight, 0.0f, player.grhandleLife, 0xFFFFFFFF);
	}

	//Novice::ScreenPrintf(640, 360, "%f", player.currentStamina);
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