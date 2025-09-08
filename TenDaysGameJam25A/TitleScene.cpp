#include "TitleScene.h"

TitleScene::TitleScene() { Initialize(); };

void TitleScene::Initialize() {
	transform.position = { 0.0f,100.0f };
	width = 732.0f;
	height = 192.0f;
	grHandle = Novice::LoadTexture("./Resources/images/only_title.png");

	buttonToStageSelect.Initialize(Novice::LoadTexture("./Resources/images/start.png"), 196.0f, 48.0f);
	buttonToConfig.Initialize(Novice::LoadTexture("./Resources/images/config.png"), 248.0f, 48.0f);
	buttonToCredit.Initialize(Novice::LoadTexture("./Resources/images/credit.png"), 248.0f, 48.0f);
	buttonToEnd.Initialize(Novice::LoadTexture("./Resources/images/quit.png"), 240.0f, 48.0f);

	buttonToStageSelect.transform.position = { 0.0f, -100.0f };
	buttonToConfig.transform.position = { 0.0f, -170.0f };
	buttonToCredit.transform.position = { 0.0f, -240.0f };
	buttonToEnd.transform.position = { 550.0f, -330.0f };

	backGround.Initialize();
	player.Initialize();

	for (int bi = 0;bi < kBulletMax;bi++) {
		bullets[bi].Initialize();
		bullets[bi].height = 80.0f;
		bullets[bi].width = 80.0f;
		bullets[bi].direction = { -1.0f, 0.0f };
		bullets[bi].damage = 0;
		bullets[bi].speed = 20.0f;
		bullets[bi].transform.position = { 600.0f,0.0f };
	}

	shotCoolTime = 60;
	isStartMinigame = false;
	miniGameScore = 0;
	memHighScore = 0;
	miniGameEndTime = 15;
	scoreHeight = 64;

	highScoreHeight = 128;
	scorePos = kScoreDefaultPos;
	highScorePos = kHighScoreDefaultPos;
	comboPos = { -550,-250 };
	comboHeight = 128;
	comboBonus = 1;
	currentCombo = 0;
	memHighCombo = 0;
	currentDimension = DimensionState::TWO;
}

void TitleScene::Update() {
	input.Update();
	click.Update();

	//Novice::ScreenPrintf(16, 16, "%d", isStartMinigame);
	//Novice::ScreenPrintf(16, 32, "%d", isEndMinigame);
	//Novice::ScreenPrintf(16, 48, "%d", miniGameEndTime);

	if (click.GetClickTrigger(1)) {

		if (!isStartMinigame) {
			MiniGameInitialize();
			isStartMinigame = true;
			backGround.Initialize();
			player.Initialize();
			backGround.Activate();
		}
	}

	if (isStartMinigame) {
		MiniGame();
		return;
	}

	buttonToStageSelect.Update();
	buttonToConfig.Update();
	buttonToCredit.Update();
	buttonToEnd.Update();

}

void TitleScene::MiniGame() {
	if (currentDimension == DimensionState::ONE) {
		player.Update();
	}

	player.transform.position.x = -270.0f;

	if (click.GetClickNotAnswer(1)) {

		if (isStartMinigame) {
			isEndMinigame = true;
		}
	}


	if (isEndMinigame) {
		miniGameEndTime--;

		if (miniGameEndTime == 0) {
			miniGameEndTime = 15;
			if (miniGameScore > memHighScore) {
				memHighScore = miniGameScore;
			}

			if (currentCombo > memHighCombo) {
				memHighCombo = currentCombo;
			}
			isStartMinigame = false;
			isEndMinigame = false;
		}
	}

	shotCoolTime--;

	if (shotCoolTime <= 0) {
		for (int bi = 0;bi < kBulletMax;bi++) {

			if (!bullets[bi].isActive) {
				if (!bullets[bi].effect.GetIsActive()) {
					bullets[bi].speed = Random::RandomFloat(10.0f, 30.0f);
					bullets[bi].ShotDir({ 600.0f,0.0f }, bullets[bi].direction, 0.0f);

					break;
				}
			}
		}
		shotCoolTime = Random::RandomInt(30, 60);
	}

	for (int bi = 0;bi < kBulletMax;bi++) {

		bullets[bi].Update();
	}

	backGround.Update();

	MiniGameCheckHitAll();

	Vector2 reactionPosition = { player.transform.position.x, player.transform.position.y + 100.0f };
	if (player.click.GetClickTrigger(0)) {
		if (currentDimension == DimensionState::ONE) {
			if (player.parry.parryState == ParryState::NONE) {
				if (player.transform.position.x < -640.0f + player.just.width / 2.0f - 128.0f) {
					reactionPosition.x = -640.0f + player.just.width / 2.0f - 128.0f;

				}
				player.miss.Activate({ reactionPosition.x, reactionPosition.y }, 0.0f);
				currentCombo = 0;

				if (currentCombo > memHighCombo) {
					memHighCombo = currentCombo;
				}
			} else if (player.parry.parryState == ParryState::NORMAL) {
				if (player.transform.position.x < -640.0f + player.just.width / 2.0f - 72.0f) {
					reactionPosition.x = -640.0f + player.just.width / 2.0f - 72.0f;
				}
				player.nice.Activate({ reactionPosition.x, reactionPosition.y }, 0.0f);
				currentCombo++;
			} else {
				if (player.transform.position.x < -640.0f + player.just.width / 2.0f) {
					reactionPosition.x = -640.0f + player.just.width / 2.0f;
				}
				player.just.Activate({ reactionPosition.x, reactionPosition.y }, 0.0f);
				currentCombo++;
			}
		}
	}
}

void TitleScene::MiniGameCheckHitAll() {

	for (int bi = 0; bi < kBulletMax; bi++) {

		if (bullets[bi].isActive) {

			//パリィの当たり判定
			if (player.parry.isParry) {
				if (Collision::BoxToBox(
					player.parry.transform.position, player.parry.width, player.parry.height, { bullets[bi].transform.position.x, 0.0f }, bullets[bi].width, bullets[bi].height)) {

					float justArea = player.parry.transform.position.x + player.parry.kJustParryAbleGrace * bullets[bi].speed;

					if (bullets[bi].transform.position.x <= justArea) {
						player.parry.parryState = ParryState::JUST;
						player.parry.color = 0xFF0000FF;
						player.isUpDamage = true;
						player.damageUpTime = 150;
						miniGameScore += 3 * comboBonus;
					} else {
						player.parry.parryState = ParryState::NORMAL;
						player.parry.color = 0xFFFF00FF;
						miniGameScore += 1 * comboBonus;
					}

					bullets[bi].Deactive();
					break;

				} else {

				}
			}
		}
	}

	// プレイヤーとエネミーの弾の当たり判定（１次元）
	for (int bi = 0; bi < kBulletMax; bi++) {
		if (bullets[bi].isActive) {
			if (Collision::BoxToBox(player.transform.position, player.width, player.hitBoxHeight, { bullets[bi].transform.position.x, 0.0f }, bullets[bi].width, bullets[bi].height)) {

				bullets[bi].Deactive();

				if (!player.isInvinciblity) {
					player.TakeDamage(1);
					bullets[bi].transform.position.x = 600.0f;
					player.isInvinciblity = true;
				}

				break;
			}
		}
	}
}

void TitleScene::MiniGameInitialize() {

	shotCoolTime = 60;
	miniGameScore = 0;
	miniGameEndTime = 15;
	scoreHeight = 64;
	highScoreHeight = 128;
	scorePos = kScoreDefaultPos;
	highScorePos = kHighScoreDefaultPos;
	for (int bi = 0;bi < kBulletMax;bi++) {
		bullets[bi].Initialize();
		bullets[bi].height = 80.0f;
		bullets[bi].width = 80.0f;
		bullets[bi].direction = { -1.0f, 0.0f };
		bullets[bi].damage = 0;
		bullets[bi].speed = 20.0f;
		bullets[bi].transform.position = { 600.0f,0.0f };
	}
	comboPos = { -550,-250 };
	comboHeight = 128;
	comboBonus = 1;
	currentCombo = 0;
}

void TitleScene::Draw() const {
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x000000FF, kFillModeSolid);
	if (currentDimension == DimensionState::TWO) {
		renderer.DrawSprite(transform, width, height, 0.0f, grHandle, 0xFFFFFFFF);
		buttonToStageSelect.Draw();
		buttonToConfig.Draw();
		buttonToCredit.Draw();
		buttonToEnd.Draw();
	} else {
		player.Draw();
	}
	if (currentDimension == DimensionState::ONE) {
		for (int bi = 0;bi < kBulletMax;bi++) {
			bullets[bi].Draw();
		}
	}

	if (isStartMinigame) {
		backGround.Draw();
		font.DrawNumber(scorePos, miniGameScore, scoreHeight, 0.0f, 0xFF0000FF);
		font.DrawNumber(highScorePos, memHighScore, highScoreHeight, 0.0f, 0xFF0000FF);
		font.DrawNumber(comboPos, currentCombo, comboHeight, 0.0f, 0xFF0000FF);
		player.miss.Draw();
		player.nice.Draw();
		player.just.Draw();
	}


	Novice::ScreenPrintf(100, 360, "%d", isStartMinigame);
	Novice::ScreenPrintf(116, 360, "%d", isEndMinigame);
	Novice::ScreenPrintf(132, 360, "%d", miniGameEndTime);
}

void TitleScene::SetCamera() {


}