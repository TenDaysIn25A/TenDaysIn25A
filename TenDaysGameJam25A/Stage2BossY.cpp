#include "Stage2BossY.h"

Stage2BossY::Stage2BossY() { Initialize(); }

void Stage2BossY::Initialize() {
	speed = 10.0f;
	width = 240.0f;
	height = 480.0f;
	isAlive = true;
	isBackGroundActive = false;
	hp = 450;
	maxHp = 900;

	color = kColor;

	shotTimer = 0;
	shotCounter = 0;
	transform.position = { 640.0f - (width / 2.0f), 0.0f };
	transform.rotation = 0.0f;
	transform.scale = { 1.0f, 1.0f };

	//開始時に実行する攻撃と開始時のフェーズ
	attack = Stage2BossAttackY::STOP;
	attackPhase = AttackPhase::FIRST;

	grHandleBox = Novice::LoadTexture("./Resources/images/box.png");
	grHandleBullet = Novice::LoadTexture("./Resources/images/box.png");
	grHandleEyeFrame = Novice::LoadTexture("./Resources/images/eyeFrame.png");
	grHandleEye = Novice::LoadTexture("./Resources/images/eyeCenter.png");
	grHandleEyeLids = Novice::LoadTexture("./Resources/images/eyeLids.png");
	grHandleBullet = Novice::LoadTexture("./Resources/images/box.png");

	for (int i = 0; i < kBulletMax; i++) {
		InitializeBullets(i, {});
	}

	for (int i = 0; i < kPredictionMax; i++) {
		prediction[i].Initialize();
	}

	for (int i = 0; i < kLaserMax; i++) {
		laser[i].Initialize();
	}

	//HPゲージの初期化と作成
	hpGauge.Initialize();
	hpGauge.CreateHpGauge({ 360.0f,300.0f }, hp, maxHp, 500.0f, 60.0f, color, true);

	AnimInitialize();
}

void Stage2BossY::AnimInitialize() {


	blackEye.position = kBlackEyeDeafaultPos;
	blackEyeFrame.position = kBlackEyeDeafaultPos;
	blackEyeWidth = 224.0f;
	blackEyeHeight = 224.0f;
	directionPlayerToEye = { 0.0f,0.0f };
}

void Stage2BossY::InitializeBullets(int index, const BulletConfig& bulletConfig) {
	bullets[index].Initialize();
	bullets[index].width = bulletConfig.width;
	bullets[index].height = bulletConfig.height;
	bullets[index].damage = bulletConfig.damage;
	bullets[index].speed = bulletConfig.speed;
	bullets[index].color = bulletConfig.color;
	bullets[index].grHandle = bulletConfig.grHandle;
}

void Stage2BossY::Update() {
	input.Update();

	//死んだら、ここで返る
	if (!isAlive) {
		return;
	}

	Shot();

	for (int i = 0; i < kBulletMax; i++) {
		bullets[i].Update();
	}

	//HP残量に応じて形態を変化させる
	if (attackPhase == AttackPhase::FIRST) {
		if (hp <= kExchengePhaseSecondHp) {
			attackPhase = AttackPhase::SECOND;
		}
	} else if (attackPhase == AttackPhase::SECOND) {
		if (hp <= kExchengePhaseThirdHp) {
			attackPhase = AttackPhase::THIRD;
		}
	}

	//HPゲージにHPと最大HPを渡しアップデートする
	hpGauge.ReferenceHp(hp, maxHp);
	hpGauge.Update();

	AnimUpdate();

	for (int i = 0; i < kPredictionMax; i++) {
		prediction[i].UpDate();
	}

	for (int i = 0; i < kLaserMax; i++) {
		laser[i].Update();
	}

	color = kColor;
}

void Stage2BossY::AnimUpdate() {
	directionPlayerToEye.x = playerPos.x - kBlackEyeDeafaultPos.x;
	directionPlayerToEye.y = playerPos.y - kBlackEyeDeafaultPos.y;

	blackEye.position.x = Vector2::Normalize(directionPlayerToEye).x * 45.0f + blackEyeOffSetX;
	blackEye.position.y = Vector2::Normalize(directionPlayerToEye).y * 45.0f;

	blackEyeFrame.Rotate(5.0f);
	transform.Rotate(180.0f);
}

void Stage2BossY::Draw() const {
	//死んだら、ここで返る
	if (!isAlive) {
		return;
	}

	Novice::ScreenPrintf(0, 1000, "%d/%d", hp, maxHp);

	for (int i = 0; i < kLaserMax; i++) {
		laser[i].Draw();
	}

	//一次元と二次元で見た目を変える
	if (currentDimension == DimensionState::TWO) {
		AnimDraw();
	} else {
		renderer.DrawSprite(transform, width, height, 0.0f, grHandleBox, color);
	}

	for (int i = 0; i < kPredictionMax; i++) {
		prediction[i].Draw();
	}

	for (int i = 0; i < kBulletMax; i++) {
		bullets[i].Draw();
	}
}

void Stage2BossY::AnimDraw() const {
	//renderer.DrawSprite(transform, width, height, 0.0f, grHandleBox, color);

	renderer.DrawSprite(blackEye, blackEyeWidth, blackEyeHeight, 0.0f, grHandleEye, color);
	renderer.DrawSprite(blackEyeFrame, blackEyeWidth, blackEyeHeight, 0.0f, grHandleEyeFrame, color);
	renderer.DrawSprite(transform, width, height, 0.0f, grHandleEyeLids, color);
}


void Stage2BossY::SetCamera(const Transform2D& camera) { renderer.SetCamera(camera); }

void Stage2BossY::Move() {

}

void Stage2BossY::TakeDamage(int damage) {
	//死んだら、ここで返る
	if (!isAlive) {
		return;
	}

	hp -= damage;

	color = kDamageColor;

	if (hp <= 0) {
		Destory();
	}
}

void Stage2BossY::Destory() {
	isAlive = false;

	for (int i = 0; i < kBulletMax; i++) {
		bullets[i].Deactive();
	}
}

void Stage2BossY::Shot() {
	switch (attack) {
	case Stage2BossAttackY::NORMAL:
		AttackMeteorShower();
		break;
	case Stage2BossAttackY::STOP:
		//AttackStop();
		AttackMeteor();
		break;
	}

	shotTimer++;
}

void Stage2BossY::CommonAttackSelect() {
	switch (attackPhase) {
	case AttackPhase::FIRST:
		attack = Stage2BossAttackY::NORMAL;
		break;
	case AttackPhase::SECOND:
		attack = Stage2BossAttackY::NORMAL;
		break;
	case AttackPhase::THIRD:
		attack = Stage2BossAttackY::NORMAL;
		break;
	}
}

void Stage2BossY::SpecialAttackSelect() {
	int randomAttack;
	switch (attackPhase) {
	case AttackPhase::FIRST:
		//攻撃を2つの中から一つ抽選して現在の攻撃にする
		randomAttack = Random::RandomInt(1, 2);

		if (randomAttack == 1) {
			attack = Stage2BossAttackY::NORMAL;
		} else if (randomAttack == 2) {
			attack = Stage2BossAttackY::NORMAL;
		} else {
		}
		break;
	case AttackPhase::SECOND:

		break;
	case AttackPhase::THIRD:

		break;
	}
}

void Stage2BossY::AttackMeteorShower() {
	if (shotTimer >= 40) {
		shotTimer = 0;
		int randomPosition = Random::RandomInt(-1, 6);
		int tmpPositionNumber[2];
		tmpPositionNumber[0] = randomPosition;

		for (int i = 0; i < kBulletMax; i++) {
			if (!bullets[i].isActive) {
				InitializeBullets(i, { .height = 80.0f });
				meteorShowerCenterPos[i] = 200.0f - (80.0f * static_cast<float>(randomPosition));
				bullets[i].ShotDir({ 640.0f + (bullets[i].width),200.0f - (80.0f * static_cast<float>(randomPosition)) }, { -1.0f, 0.0f }, 0.0f);

				break;
			}
		}

		do {
			randomPosition = Random::RandomInt(-1, 6);

			for (int i = 0; i < kBulletMax; i++) {
				if (!bullets[i].isActive) {
					if (tmpPositionNumber[0] != randomPosition) {
						InitializeBullets(i, { .height = 80.0f });
						meteorShowerCenterPos[i] = 200.0f - (80.0f * static_cast<float>(randomPosition));
						bullets[i].ShotDir({ 640.0f + (bullets[i].width),200.0f - (80.0f * static_cast<float>(randomPosition)) }, { -1.0f, 0.0f }, 0.0f);
						tmpPositionNumber[1] = randomPosition;
						break;
					}
				}
			}

		} while (tmpPositionNumber[0] == randomPosition);

		do {
			randomPosition = Random::RandomInt(-1, 6);

			for (int i = 0; i < kBulletMax; i++) {
				if (!bullets[i].isActive) {
					if (tmpPositionNumber[0] != randomPosition) {
						if (tmpPositionNumber[1] != randomPosition) {
							InitializeBullets(i, { .height = 80.0f });
							meteorShowerCenterPos[i] = 200.0f - (80.0f * static_cast<float>(randomPosition));
							bullets[i].ShotDir({ 640.0f + (bullets[i].width),200.0f - (80.0f * static_cast<float>(randomPosition)) }, { -1.0f, 0.0f }, 0.0f);
							break;
						}
					}
				}
			}

		} while (tmpPositionNumber[0] == randomPosition || tmpPositionNumber[1] == randomPosition);

		if (shotCounter >= 7) {
			shotCounter = 0;

			SpecialAttackSelect();
		} else {
			shotCounter++;
		}
	}

	for (int i = 0; i < kBulletMax; i++) {
		if (bullets[i].isActive) {
			bullets[i].transform.position.y = meteorShowerCenterPos[i] + (sinf(meteorTheta * (static_cast<float>(M_PI) / 180.0f)) * 100.0f);
		}
	}

	meteorTheta += 2.0f;
}

void Stage2BossY::AttackStop() {

	if (shotTimer >= 224) {
	} else if (shotTimer > 194) {
	} else if (shotTimer > 193) {
		for (int i = 0; i < kBulletMax; i++) {
			if (bullets[i].isActive) {
				bullets[i].Deactive();
			}
		}

		currentWalker = DimesionWalker::PLAYER;
		isBackGroundActive = true;
		SpecialAttackSelect();
	} else if (shotTimer > 192) {
	} else if (shotTimer > 162) {
	} else if (shotTimer > 161) {
		if (currentDimension == DimensionState::TWO) {
			isBackGroundActive = true;
		}

	} else if (shotTimer > 151) {
		
	} else if (shotTimer > 141) {
		if (shotTimer % 2 == 0) {
			if (currentWalker == DimesionWalker::PLAYER) {
				currentWalker = DimesionWalker::BOSS;
			} else {
				currentWalker = DimesionWalker::PLAYER;
			}
		}
	} else if (shotTimer > 140) {
		for (int i = 0; i < kBulletMax; i++) {
			if (bullets[i].isActive) {
				bullets[i].velocity.x = 0.0f;
			}
		}

	} else if (shotTimer > 1) {
		if (shotTimer % 16 == 0) {
			if (shotCounter != holePosition && shotCounter != holePosition + 1) {
				for (int i = 0; i < kBulletMax; i++) {
					if (!bullets[i].isActive) {
						if (!bullets[i].effect.GetIsActive()) {
							InitializeBullets(i, { .height = 80.0f });
							bullets[i].ShotDir({ 640.0f + (bullets[i].width),200.0f }, { -1.0f, 0.0f }, 0.0f);
							break;
						}
					}
				}
			}

			shotCounter++;
		} else if (shotTimer % 16 == 8) {
			if (shotCounter != holePosition && shotCounter != holePosition + 1) {
				for (int i = 0; i < kBulletMax; i++) {
					if (!bullets[i].isActive) {
						if (!bullets[i].effect.GetIsActive()) {
							InitializeBullets(i, { .height = 80.0f });
							bullets[i].ShotDir({ 640.0f + (bullets[i].width),-200.0f }, { -1.0f, 0.0f }, 0.0f);
							break;
						}
					}
				}
			}

			shotCounter++;
		}

	} else {
		holePosition = Random::RandomInt(1, 9);
	}

}

//ノーマル1、切り替え1、3連
void Stage2BossY::AttackMeteor(){
	if (shotTimer >= 161) {
	}else if (shotTimer >= 160) {
		for (int i = 0; i < kLaserMax; i++) {
			if (!laser[i].isActive) {
				laser[i].LaserCreate({ 0.0f,100.0f }, 1280.0f, 240.0f, 300);
				break;
			}
		}
	}else if (shotTimer >= 60) {
	}else if(shotTimer >= 59){
		for (int i = 0; i < kPredictionMax; i++) {
			if (!prediction[i].isVisible) {
				prediction[i].LineCharge({0.0f,100.0f},1280.0f,240.0f,100);
				break;
			}
		}
	}
}