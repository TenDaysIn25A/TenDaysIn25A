#include "Stage2Boss.h"

Stage2Boss::Stage2Boss() { Initialize(); }

void Stage2Boss::Initialize() {
	speed = 10.0f;
	width = 240.0f;
	height = 480.0f;
	isAlive = true;
	hp = 900;
	maxHp = 900;

	color = kColor;

	shotTimer = 0;
	shotCounter = 0;
	transform.position = { 640.0f - (width / 2.0f), 0.0f };
	transform.rotation = 0.0f;
	transform.scale = { 1.0f, 1.0f };

	//開始時に実行する攻撃と開始時のフェーズ
	attack = Stage2BossAttack::NORMAL;
	attackPhase = AttackPhase::FIRST;

	grHandleBox = Novice::LoadTexture("./Resources/images/box.png");
	grHandleBullet = Novice::LoadTexture("./Resources/images/box.png");
	grHandleEyeFrame = Novice::LoadTexture("./Resources/images/eyeFrame.png");
	grHandleEye = Novice::LoadTexture("./Resources/images/eyeCenter.png");
	grHandleEyeLids = Novice::LoadTexture("./Resources/images/eyeLids.png");
	grHandleBlackHole0 = Novice::LoadTexture("./Resources/images/blackHole0.png");
	grHandleBlackHole1 = Novice::LoadTexture("./Resources/images/blackHole1.png");
	grHandleBlackHole2 = Novice::LoadTexture("./Resources/images/blackHole2.png");
	grHandleBlackHole3 = Novice::LoadTexture("./Resources/images/blackHole3.png");
	for (int i = 0; i < kBulletMax; i++) {
		InitializeBullets(i, {});
	}

	//HPゲージの初期化と作成
	hpGauge.Initialize();
	hpGauge.CreateHpGauge({ 360.0f,300.0f }, hp, maxHp, 500.0f, 60.0f, color, true);

	blackHoleWidth = 160.0f;
	blackHoleHeight = 160.0f;
	blackHoleAnimatioCount = 0;
	blackHolePhase = 0;
	gravityAreaWidth = 480.0f;
	gravityAreaHeight = 480.0f;
	satelliteRotateTheta = -0.7f;
	barrageTimer = 0;
	isFusion = false;

	blackEye.position = kBlackEyeDeafaultPos;
	blackEyeFrame.position = kBlackEyeDeafaultPos;
	blackEyeWidth = 224.0f;
	blackEyeHeight = 224.0f;
	directionPlayerToEye = { 0.0f,0.0f };

	AnimInitialize();
}

void Stage2Boss::AnimInitialize() {

}

void Stage2Boss::InitializeBullets(int index, const BulletConfig& bulletConfig) {
	bullets[index].Initialize();
	bullets[index].width = bulletConfig.width;
	bullets[index].height = bulletConfig.height;
	bullets[index].damage = bulletConfig.damage;
	bullets[index].speed = bulletConfig.speed;
	bullets[index].color = bulletConfig.color;
	bullets[index].grHandle = bulletConfig.grHandle;
}

void Stage2Boss::Update() {
	input.Update();

	//死んだら、ここで返る
	if (!isAlive) {
		return;
	}

	directionPlayerToEye.x = playerPos.x - kBlackEyeDeafaultPos.x;
	directionPlayerToEye.y = playerPos.y - kBlackEyeDeafaultPos.y;

	blackEye.position.x = Vector2::Normalize(directionPlayerToEye).x * 45.0f + blackEyeOffSetX;
	blackEye.position.y = Vector2::Normalize(directionPlayerToEye).y * 45.0f;

	blackEyeFrame.Rotate(5.0f);
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

	color = kColor;
}

void Stage2Boss::AnimUpdate() {

}

void Stage2Boss::Draw() const {
	//死んだら、ここで返る
	if (!isAlive) {
		return;
	}

	Novice::ScreenPrintf(0, 1000, "%d/%d", hp, maxHp);

	//一次元と二次元で見た目を変える
	if (currentDimension == DimensionState::TWO) {
		AnimDraw();
	} else {
		renderer.DrawSprite(transform, width, height, 0.0f, grHandleBox, color);
	}

	for (int i = 0; i < kBulletMax; i++) {
		bullets[i].Draw();
	}

	if (isFusion) {

		if (blackHoleAnimatioCount == 0) {
			renderer.DrawSprite(blackHole, blackHoleWidth, blackHoleHeight, 0.0f, grHandleBlackHole0, 0xFFFFFFFF);
		}else if (blackHoleAnimatioCount == 1) {
			renderer.DrawSprite(blackHole, blackHoleWidth, blackHoleHeight, 0.0f, grHandleBlackHole1, 0xFFFFFFFF);
		} else if (blackHoleAnimatioCount == 2) {
			renderer.DrawSprite(blackHole, blackHoleWidth, blackHoleHeight, 0.0f, grHandleBlackHole2, 0xFFFFFFFF);
		} else if (blackHoleAnimatioCount == 3) {
			renderer.DrawSprite(blackHole, blackHoleWidth, blackHoleHeight, 0.0f, grHandleBlackHole3, 0xFFFFFFFF);
		} 
	}

	if (bullets[60].isActive) {
		renderer.DrawSprite(newSatellite, bullets[61].width, bullets[61].height, 0.0f, grHandleBox, 0xFFFFFFFF);
	}
}

void Stage2Boss::AnimDraw() const {
	renderer.DrawSprite(blackEye, blackEyeWidth, blackEyeHeight, 0.0f, grHandleEye, color);
	renderer.DrawSprite(blackEyeFrame, blackEyeWidth, blackEyeHeight, 0.0f, grHandleEyeFrame, color);
	renderer.DrawSprite(transform, width, height, 0.0f, grHandleEyeLids, color);

}

void Stage2Boss::SetCamera(const Transform2D& camera) { renderer.SetCamera(camera); }

void Stage2Boss::Move() {

}

void Stage2Boss::TakeDamage(int damage) {
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

void Stage2Boss::Destory() {
	isAlive = false;

	for (int i = 0; i < kBulletMax; i++) {
		bullets[i].Deactive();
	}
}

void Stage2Boss::Shot() {
	switch (attack) {
	case Stage2BossAttack::NORMAL:
		AttackNormal();
		break;

	case Stage2BossAttack::ALL_WALL:
		AttackAllWall();
		break;

	case Stage2BossAttack::BLACK_HOLE:
		AttackBlackHole();
		break;
	}

	shotTimer++;
}

void Stage2Boss::CommonAttackSelect() {
	switch (attackPhase) {
	case AttackPhase::FIRST:
		attack = Stage2BossAttack::NORMAL;
		break;
	case AttackPhase::SECOND:
		attack = Stage2BossAttack::ALL_WALL;
		break;
	case AttackPhase::THIRD:
		attack = Stage2BossAttack::ALL_WALL;
		break;
	}
}

void Stage2Boss::SpecialAttackSelect() {
	int randomAttack;
	switch (attackPhase) {
	case AttackPhase::FIRST:
		//攻撃を2つの中から一つ抽選して現在の攻撃にする
		randomAttack = Random::RandomInt(2, 2);

		if (randomAttack == 1) {
			attack = Stage2BossAttack::NORMAL;
		} else if (randomAttack == 2) {
			attack = Stage2BossAttack::BLACK_HOLE;
		} else {
		}
		break;
	case AttackPhase::SECOND:

		randomAttack = Random::RandomInt(2, 2);

		if (randomAttack == 1) {
			attack = Stage2BossAttack::NORMAL;
		} else if (randomAttack == 2) {
			attack = Stage2BossAttack::ALL_WALL;
		} else {
		}

		break;
	case AttackPhase::THIRD:

		randomAttack = Random::RandomInt(2, 2);

		if (randomAttack == 1) {
			attack = Stage2BossAttack::NORMAL;
		} else if (randomAttack == 2) {
			attack = Stage2BossAttack::ALL_WALL;
		} else {
		}

		break;
	}
}

void Stage2Boss::AttackNormal() {
	if (shotTimer >= 80) {
		shotTimer = 0;

		int randomPosition = Random::RandomInt(-1, 1);

		for (int i = 0; i < kBulletMax; i++) {
			if (!bullets[i].isActive) {
				InitializeBullets(i, {});
				bullets[i].ShotDir({ transform.position.x + width / 2.0f, 0 + (160.0f * static_cast<float>(randomPosition)) }, { -1.0f, 0.0f }, 0.0f);
				break;
			}
		}

		if (shotCounter >= 7) {
			shotCounter = 0;

			SpecialAttackSelect();
		} else {
			shotCounter++;
		}
	}
}

void Stage2Boss::AttackAllWall() {

	if (shotTimer >= 80) {
		shotTimer = 0;

		int randomPosition;

		int randomWall;

		if (shotCounter >= 7) {


			for (int i = 0; i < kBulletMax; i++) {
				if (!bullets[i].isActive) {
					InitializeBullets(i, {});
					bullets[i].height = 480.0f;

					bullets[i].ShotDir({ transform.position.x, 0.0f }, { -1.0f, 0.0f }, 0.0f);

					break;
				}
			}
		} else {
			randomPosition = Random::RandomInt(-1, 1);
			randomWall = Random::RandomInt(0, 3);

			if (randomWall <= 2) {
				for (int i = 0; i < kBulletMax; i++) {
					if (!bullets[i].isActive) {
						InitializeBullets(i, {});
						bullets[i].ShotDir({ transform.position.x, 0 + (160.0f * static_cast<float>(randomPosition)) }, { -1.0f, 0.0f }, 0.0f);
						break;
					}
				}
			} else {
				for (int i = 0; i < kBulletMax; i++) {
					if (!bullets[i].isActive) {
						InitializeBullets(i, {});
						bullets[i].height = 480.0f;

						bullets[i].ShotDir({ transform.position.x, 0.0f }, { -1.0f, 0.0f }, 0.0f);

						break;
					}
				}
			}
		}

		if (shotCounter >= 7) {
			shotCounter = 0;

			SpecialAttackSelect();
		} else {
			shotCounter++;
		}
	}
}

void Stage2Boss::AttackBlackHole() {

	if (blackHolePhase == 2) {

		blackHoleAnimatioCount++;
		if (blackHoleAnimatioCount > 3) {
			blackHoleAnimatioCount = 0;
		}

		if (barrageTimer < 60) {

			barrageTimer++;
		} else {


			if (shotTimer >= 3) {

				shotTimer = 0;

				if (shotCounter < 100) {

					int randomPosition = Random::RandomInt(-3, 2);

					for (int i = 0; i < kBulletMax; i++) {
						if (!bullets[i].isActive) {
							if (!bullets[i].effect.GetIsActive()) {
								InitializeBullets(i, { .width = 80.0f,.height = 80.0f });

								if (isFusion) {

									bullets[i].ShotPos({ transform.position.x + width / 2.0f, 0 + (80.0f * static_cast<float>(randomPosition) + 40.0f) }, { blackHole.position }, 0.0f);

								} else {
									bullets[i].ShotDir({ transform.position.x + width / 2.0f, 0 + (80.0f * static_cast<float>(randomPosition) + 40.0f) }, { -1.0f, 0.0f }, 0.0f);
								}

								break;
							}
						}
					}
					shotCounter++;
				} else {

					for (int bi = 0;bi < kBulletMax;bi++) {



						if (bullets[bi].isActive) {
							break;
						}

						if (bi == kBulletMax - 1) {
							CommonAttackSelect();
							barrageTimer = 0;
							shotCounter = 0;
							isFusion = false;
							blackHolePhase = 0;
						}
					}
				}
			}

			for (int bi = 0;bi < kBulletMax;bi++) {

				if (bullets[bi].transform.position.x <= blackHole.position.x) {

					if (bullets[bi].isActive) {
						bullets[bi].Deactive();
						break;
					}
				}
			}

		}

	} else if (blackHolePhase == 1) {

		satelliteRotateTheta += 0.02f;
		newSatellite.position.x = bullets[61].transform.position.x * cosf(satelliteRotateTheta) - bullets[61].transform.position.y * sinf(satelliteRotateTheta) + bullets[60].transform.position.x;
		newSatellite.position.y = bullets[61].transform.position.y * cosf(satelliteRotateTheta) + bullets[61].transform.position.x * sinf(satelliteRotateTheta) + bullets[60].transform.position.y;

		if (bullets[60].isActive) {
			blackHole.position = bullets[60].transform.position;
		}

		if (currentDimension == DimensionState::ONE) {

			newSatellite.position.y = 0.0f;
			if (Collision::BoxToBox({ bullets[60].transform.position.x,0.0f }, bullets[60].width, bullets[60].height, { newSatellite.position.x,0.0f }, bullets[61].width, bullets[61].height)) {

				bullets[60].Deactive();
				isFusion = true;
				blackHolePhase = 2;
				satelliteRotateTheta = -0.7f;
				shotTimer = 0;
			}
		}

		if (bullets[60].transform.position.x <= -800.0f) {
			blackHolePhase = 2;
			shotTimer = 0;
			satelliteRotateTheta = -0.7f;
		}

	} else {
		if (!bullets[60].isActive) {
			InitializeBullets(60, { .speed = 3.0f,.width = 160.0f,.height = 160.0f, });
			InitializeBullets(61, { .width = 80.0f,.height = 80.0f,.color = 0x00000000 });
			bullets[61].transform.position = { 160.0f,0.0f };
			bullets[60].ShotDir({ transform.position.x + width / 2.0f, 0.0f }, { -1.0f, 0.0f }, 0.0f);
		}
		blackHoleAnimatioCount = 0;
		blackHolePhase = 1;
	}
}