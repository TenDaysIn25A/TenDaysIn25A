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
	buttonToCredit.transform.position = { 0.0f, -240.0f};
	buttonToEnd.transform.position = { 550.0f, -330.0f};

	backGround.Initialize();
	player.Initialize();
	for (int bi = 0;bi < kBulletMax;bi++) {
		bullets[bi].Initialize();
	}

	isStartMinigame = false;
	miniGameEndTime = 15;
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
			isStartMinigame = false;
			isEndMinigame = false;
		}
	}

	backGround.Update();

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

void TitleScene::MiniGameCheckHitAl() {

	if (currentDimension == DimensionState::ONE) {
		for (int bi = 0; bi < kBulletMax; bi++) {

			if (!bullets[bi].isActive) {
				continue;
			}

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
					} else {
						player.parry.parryState = ParryState::NORMAL;
						player.parry.color = 0xFFFF00FF;
					}

					bullets[bi].Deactive();

				} else {

				}

				if (player.parry.parryState == ParryState::NONE) {
					player.currentStamina -= player.kMissConsumedStamina;
				}

			}
		}

		// プレイヤーとエネミーの弾の当たり判定（１次元）
		for (int bi = 0; bi < kBulletMax; bi++) {
			if (bullets[bi].isActive) {
				if (Collision::BoxToBox(player.transform.position, player.width, player.hitBoxHeight, { bullets[bi].transform.position.x, 0.0f }, bullets[bi].width,bullets[bi].height)) {

					bullets[bi].Deactive();

					if (!player.isInvinciblity) {
						player.TakeDamage(1);
						bullets[bi].transform.position.x = 0.0f;
						player.isInvinciblity = true;
					}

				}
			}
		}
	}

}

void TitleScene::Draw() const {
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x000000FF, kFillModeSolid);
	if (currentDimension == DimensionState::TWO){
		renderer.DrawSprite(transform, width, height, 0.0f, grHandle, 0xFFFFFFFF); 
		buttonToStageSelect.Draw();
		buttonToConfig.Draw();
		buttonToCredit.Draw();
		buttonToEnd.Draw();
	} else {
		player.Draw();
	}

	if (isStartMinigame) {
		backGround.Draw();
		player.miss.Draw();
		player.nice.Draw();
		player.just.Draw();
	}
}

void TitleScene::SetCamera() {


}