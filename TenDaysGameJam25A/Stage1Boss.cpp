#include "Stage1Boss.h"

Stage1Boss::Stage1Boss() { Initialize(); }

void Stage1Boss::Initialize() {
	speed = 10.0f;
	width = 320.0f;
	height = 480.0f;
	isAlive = true;
	isPhase3Start = false;
	isAnger = false;
	isTemptation = false;
	hp = 600;
	maxHp = 600;

	color = kColor;

	exchengePhaseSecondHp = 400;
	exchengePhaseThirdHp = 200;

	shotTimer = 0;
	shotCounter = 0;
	transform.position = { 640.0f - (width / 2.0f), 0.0f };
	transform.rotation = 0.0f;
	transform.scale = { 1.0f, 1.0f };
	attack = Stage1BossAttack::FISHSWIM;
	attackPhase = AttackPhase::FIRST;

	grHandleBox = Novice::LoadTexture("./Resources/images/box.png");
	grHandleBullet = Novice::LoadTexture("./Resources/images/box.png");
	grHandleBulletFish = Novice::LoadTexture("./Resources/images/chochinFish1.png");
	grHandleFishBoneTop = Novice::LoadTexture("./Resources/images/fhishBoneTop.png");
	grHandleFishBoneBottom = Novice::LoadTexture("./Resources/images/fhishBoneBottom.png");
	grHandleBigFishBoneTop = Novice::LoadTexture("./Resources/images/fishBoneBickTop.png");
	grHandleBigFishBoneBottom = Novice::LoadTexture("./Resources/images/fishBoneBickBottom.png");

	for (int i = 0; i < kBulletMax; i++) {
		InitializeBullets(i, {});
		bullets[i].effect.Initialize(grHandleBullet, 30.0f, 30.0f);
	}

	hpGauge.Initialize();
	hpGauge.CreateHpGauge({ 360.0f,300.0f }, hp, maxHp, 500.0f, 60.0f, color, true);

	AnimInitialize();

	light.Initialize();
}

void Stage1Boss::AnimInitialize() {
	chochinMouthBottom.position = { kChochinMouthOffsetX,kChochinMouthOffsetY };
	chochinMouthBottomWidth = 480.0f;
	chochinMouthBottomHeight = 480.0f;
	chochinMouthBottomTheta = 0.0f;
	grHandleChochinMouthBottom0 = Novice::LoadTexture("./Resources/images/chochinMouthBottom0.png");
	grHandleChochinMouthBottom1 = Novice::LoadTexture("./Resources/images/chochinMouthBottom1.png");
	grHandleChochinMouthBottom2 = Novice::LoadTexture("./Resources/images/chochinMouthBottom2.png");
	grHandleChochinMouthBottom3 = Novice::LoadTexture("./Resources/images/chochinMouthBottom3.png");

	chochinMouthTop.position = { kChochinMouthOffsetX,kChochinMouthOffsetY };
	chochinMouthTopWidth = 480.0f;
	chochinMouthTopHeight = 480.0f;
	chochinMouthTopTheta = 0.0f;
	grHandleChochinMouthTop0 = Novice::LoadTexture("./Resources/images/chochinMouthTop0.png");
	grHandleChochinMouthTop1 = Novice::LoadTexture("./Resources/images/chochinMouthTop1.png");
	grHandleChochinMouthTop2 = Novice::LoadTexture("./Resources/images/chochinMouthTop2.png");
	grHandleChochinMouthTop3 = Novice::LoadTexture("./Resources/images/chochinMouthTop3.png");
	chochinAnimationCount = 0;

	chochinAmplitudeX = 30.0f;
	chochinAmplitudeY = 36.0f;
	chochinWavingThetaX = float(M_PI) / 2.0f;
	chochinWavingThetaY = 0.0f;
	chochinEies.position = { kChochinEiesOffsetX,kChochinEiesOffsetY };
	chochinEiesWidth = 96.0f;
	chochinEiesHeight = 96.0f;
	grHandleChochinEies = Novice::LoadTexture("./Resources/images/chochinEies.png");
	chochinEiesTheta = float(M_PI) * 0.0f;
	chochinEiesRotateTimer = 4;
	chochinLight.position = { 0.0f,0.0f };
	chochinLightWidth = 480.0f;
	chochinLightHeight = 220.0f;
	grHandleChochinLight0 = Novice::LoadTexture("./Resources/images/chochinLight0.png");
	grHandleChochinLight1 = Novice::LoadTexture("./Resources/images/chochinLight1.png");
	grHandleChochinLight2 = Novice::LoadTexture("./Resources/images/chochinLight2.png");
	grHandleChochinLight3 = Novice::LoadTexture("./Resources/images/chochinLight3.png");
	chochinLightTheta = 0.0f;
	chochinLightThetaSpeed = 0.5f;
	chochinLightIsActive = false;

	chochinThetaSpeed = 0.07f;
	chochinColor = 0x00EEEEFF;
}

void Stage1Boss::InitializeBullets(int index, const BulletConfig& bulletConfig) {
	bullets[index].Initialize();
	bullets[index].width = bulletConfig.width;
	bullets[index].height = bulletConfig.height;
	bullets[index].damage = bulletConfig.damage;
	bullets[index].speed = bulletConfig.speed;
	bullets[index].color = bulletConfig.color;
	bullets[index].type = bulletConfig.type;
	bullets[index].grHandle = bulletConfig.grHandle;
}

void Stage1Boss::Update() {
	input.Update();

	//死んだら、ここで返る
	if (!isAlive) {
		return;
	}

	Shot();

	for (int i = 0; i < kBulletMax; i++) {
		bullets[i].Update();
	}

	if (light.lightNotice) {
		bullets[60].color = 0x000000FF;
	} else {
		bullets[60].color = 0xFFFFFFFF;
	}

	if (light.isActive) {
		light.backGroundColor = 0XFFFF00FF;
	} else {
		light.backGroundColor = 0x00FFFFFF;
	}

	if (attackPhase == AttackPhase::FIRST) {
		if (hp <= exchengePhaseSecondHp) {
			attackPhase = AttackPhase::SECOND;
		}
	} else if (attackPhase == AttackPhase::SECOND) {
		if (hp <= exchengePhaseThirdHp) {
			isPhase3Start = true;
			attackPhase = AttackPhase::THIRD;
		}
	}

	if (attack == Stage1BossAttack::LIGHT) {


	}

	hpGauge.ReferenceHp(hp, maxHp);
	hpGauge.Update();

	AnimUpdate();

	if (isAnger) {
		if (isTemptation) {
			color = kTemptationColor;
		} else {
			color = kAngerColor;
		}
	} else {
		if (isTemptation) {
			color = kTemptationColor;
		} else {
			color = kColor;
		}
	}
	
}

void Stage1Boss::AnimUpdate() {
	if (input.GetKeyTrigger(DIK_SPACE)) {
		
		isAnger = !isAnger;

		chochinLightIsActive = !chochinLightIsActive;

		if (chochinLightIsActive) {

			chochinLightThetaSpeed = 3.0f;
		} else {

			chochinLightThetaSpeed /= 3.0f;

		}

	}

	chochinMouthBottom.position.x = cosf(chochinWavingThetaX) * chochinAmplitudeX + kChochinMouthOffsetX;
	chochinMouthBottom.position.y = sinf(chochinWavingThetaY) * chochinAmplitudeY + kChochinMouthOffsetY;



	if (chochinAnimationCount > 3) {
		chochinAnimationCount = 0;
	} else {
		chochinAnimationCount++;
	}

	chochinMouthTop.position.x = cosf(chochinWavingThetaX) * chochinAmplitudeX + kChochinMouthOffsetX;
	chochinMouthTop.position.y = sinf(chochinWavingThetaY) * chochinAmplitudeY + kChochinMouthOffsetY;

	chochinEies.position.x = chochinMouthBottom.position.x + kChochinEiesOffsetX;
	chochinEies.position.y = chochinMouthBottom.position.y + kChochinEiesOffsetY;

	chochinLight.position.x = chochinMouthBottom.position.x + kChochinLightOffsetX;
	chochinLight.position.y = chochinMouthBottom.position.y + kChochinLightOffsetY;

	if (chochinLightIsActive) {

		if (chochinLightTheta > 30.0f) {
			chochinLightThetaSpeed = -1.0f;
			chochinLightTheta = 30.0f;
		} else if (chochinLightTheta < 0.0f) {
			chochinLightThetaSpeed = 1.0f;
			chochinLightTheta = 0.0f;
		}

	} else {

		if (chochinLightTheta > 30.0f) {
			chochinLightThetaSpeed = -0.5f;
		} else if (chochinLightTheta < 0.0f) {
			chochinLightThetaSpeed = 0.5f;
		}

	}
	Novice::ScreenPrintf(116, 116, "%f", chochinLightThetaSpeed);

	chochinLightTheta += chochinLightThetaSpeed;

	if (chochinEiesRotateTimer > 0) {
		chochinEiesRotateTimer--;
	} else {
		chochinEiesTheta += float(M_PI) / 2.0f;

		if (chochinColor == 0x00EEEEFF) {
			chochinEiesRotateTimer = 4;


		} else {
			chochinEiesRotateTimer = 1;
		}
	}

	if (chochinColor == 0x00EEEEFF) {

		chochinWavingThetaX += float(M_PI) / 90.0f;
		chochinWavingThetaY += float(M_PI) / 60.0f;
	} else {
		chochinWavingThetaX += float(M_PI) / 60.0f;
		chochinWavingThetaY += float(M_PI) / 30.0f;
	}

	chochinMouthBottomTheta += chochinThetaSpeed;
	chochinMouthTopTheta -= chochinThetaSpeed;

	if (chochinMouthBottomTheta > 3.0f || chochinMouthBottomTheta < 0.0f) {
		chochinThetaSpeed *= -1.0f;
	}
}


void Stage1Boss::Draw() const {
	//死んだら、ここで返る
	if (!isAlive) {
		return;
	}

	Novice::ScreenPrintf(0, 0, "%d/%d", hp, maxHp);

	//renderer.DrawSprite(transform, width, height, 0.0f, grHandleCaracter, color);
	if (currentDimension == DimensionState::TWO) {
		AnimDraw();
	} else {
		renderer.DrawSprite(transform, width, height, 0.0f, grHandleBox, color);
	}

	if (attack == Stage1BossAttack::LIGHT) {

		if (shotTimer >= 120) {
			renderer.DrawEllipse(light.transform, light.radius, { 0,0 }, 0.0f, 0xFFFF00FF, kFillModeSolid);


			if (light.lightNotice) {

				if (currentDimension == DimensionState::TWO) {
					light.DrawShadow(bullets[60].transform, bullets[60].width, bullets[60].height, 0x0000000FF);
				} else {
					Transform2D oneDimShadow;
					oneDimShadow.position = { bullets[60].transform.position.x,0.0f };

					light.DrawShadow(oneDimShadow, bullets[60].width, bullets[60].height, 0x0000000FF);
				}
			}
		}
	}

	for (int i = 0; i < kBulletMax; i++) {
		bullets[i].Draw();
	}
}

void Stage1Boss::AnimDraw() const {
	if (chochinAnimationCount == 0) {
		renderer.DrawSprite(chochinMouthBottom, chochinMouthBottomWidth, chochinMouthBottomHeight, chochinMouthBottomTheta, grHandleChochinMouthBottom0, color);
		renderer.DrawSprite(chochinMouthTop, chochinMouthTopWidth, chochinMouthTopHeight, chochinMouthTopTheta, grHandleChochinMouthTop0, color);
		renderer.DrawSprite(chochinLight, chochinLightWidth, chochinLightHeight, chochinLightTheta, grHandleChochinLight0, color);
	} else if (chochinAnimationCount == 1) {
		renderer.DrawSprite(chochinMouthBottom, chochinMouthBottomWidth, chochinMouthBottomHeight, chochinMouthBottomTheta, grHandleChochinMouthBottom1, color);
		renderer.DrawSprite(chochinMouthTop, chochinMouthTopWidth, chochinMouthTopHeight, chochinMouthTopTheta, grHandleChochinMouthTop1, color);
		renderer.DrawSprite(chochinLight, chochinLightWidth, chochinLightHeight, chochinLightTheta, grHandleChochinLight1, color);
	} else if (chochinAnimationCount == 2) {
		renderer.DrawSprite(chochinMouthBottom, chochinMouthBottomWidth, chochinMouthBottomHeight, chochinMouthBottomTheta, grHandleChochinMouthBottom2, color);
		renderer.DrawSprite(chochinMouthTop, chochinMouthTopWidth, chochinMouthTopHeight, chochinMouthTopTheta, grHandleChochinMouthTop2, color);
		renderer.DrawSprite(chochinLight, chochinLightWidth, chochinLightHeight, chochinLightTheta, grHandleChochinLight2, color);

	} else {
		renderer.DrawSprite(chochinMouthBottom, chochinMouthBottomWidth, chochinMouthBottomHeight, chochinMouthBottomTheta, grHandleChochinMouthBottom3, color);
		renderer.DrawSprite(chochinMouthTop, chochinMouthTopWidth, chochinMouthTopHeight, chochinMouthTopTheta, grHandleChochinMouthTop3, color);
		renderer.DrawSprite(chochinLight, chochinLightWidth, chochinLightHeight, chochinLightTheta, grHandleChochinLight3, color);
	}
	renderer.DrawSprite(chochinEies, chochinEiesWidth, chochinEiesHeight, chochinEiesTheta * 180 / float(M_PI), grHandleChochinEies, color);
}

void Stage1Boss::SetCamera(const Transform2D& camera) { renderer.SetCamera(camera); }

void Stage1Boss::Move() {

}

void Stage1Boss::TakeDamage(int damage) {
	if (!isAlive) {
		return;
	}

	hp -= damage;

	color = kDamageColor;

	if (hp <= 0) {
		Destory();
	}
}

void Stage1Boss::Destory() {
	isAlive = false;

	for (int i = 0; i < kBulletMax; i++) {
		bullets[i].Deactive();
	}
}

void Stage1Boss::Shot() {
	if (isPhase3Start) {
		AttackLight();
		attack = Stage1BossAttack::LIGHT;
	} else {
		switch (attack) {
		case Stage1BossAttack::MADNESS_TEMPTATION:
			AttackMadnessTemptation();
			break;
		case Stage1BossAttack::SQUIDSWIM:
			AttackMachingun();
			break;
		case Stage1BossAttack::FISHBONE:
			AttackFishBone();
			break;
		case Stage1BossAttack::FISHSWIM:
			AttackFishSwim();
			break;
		case Stage1BossAttack::FOURWALL:
			AttackFourWall();
			break;
		case Stage1BossAttack::LIGHT:
			AttackLight();
			break;
		case Stage1BossAttack::TURN:
			AttackTurn();
			break;
		case Stage1BossAttack::RANDOMFISH:
			AttackRandomFish();
			break;
		}
	}
	

	shotTimer++;
}

void Stage1Boss::CommonAttackSelect() {
	switch (attackPhase) {
	case AttackPhase::FIRST:
		attack = Stage1BossAttack::FISHSWIM;
		break;
	case AttackPhase::SECOND:
		attack = Stage1BossAttack::SQUIDSWIM;
		break;
	case AttackPhase::THIRD:
		attack = Stage1BossAttack::FOURWALL;
		break;
	}
}

void Stage1Boss::SpecialAttackSelect() {
	int randomAttack;
	switch (attackPhase) {
	case AttackPhase::FIRST:
		randomAttack = 1;//Random::RandomInt(1, 2);

		if (randomAttack == 1) {
			attack = Stage1BossAttack::RANDOMFISH;
		} else if (randomAttack == 2) {
			attack = Stage1BossAttack::LIGHT;
		} else {
		}
		break;
	case AttackPhase::SECOND:
		randomAttack = Random::RandomInt(1, 2);

		if (randomAttack == 1) {
			attack = Stage1BossAttack::TURN;
		} else if (randomAttack == 2) {
			attack = Stage1BossAttack::FISHBONE;
		} else {
		}
		break;
	case AttackPhase::THIRD:
		randomAttack = Random::RandomInt(1, 2);

		if (randomAttack == 1) {
			attack = Stage1BossAttack::LIGHT;
		} else if (randomAttack == 2) {
			attack = Stage1BossAttack::MADNESS_TEMPTATION;
		} else {
		}
		break;
	}
}

void Stage1Boss::AttackMadnessTemptation() {
	if (shotTimer >= 100) {
		shotTimer = 0;

		if (shotCounter == 3) {
			isTemptation = true;

			for (int i = 0; i < kBulletMax; i++) {
				if (bullets[i].isActive) {
					bullets[i].FishLightShine({ 0.0f,0.0f });
				}
			}
		}

		if (shotCounter >= 4) {
			shotCounter = 0;

			isTemptation = false;
			CommonAttackSelect();
		} else {
			shotCounter++;
		}
	} else if (shotTimer > 41) {
	} else if (shotTimer > 40) {
		int randomPosition;
		if (shotCounter == 0) {
			for (int i = 0; i < 6; i++) {
				returnFishPosY[i] = 0;
			}
		}

		if (shotCounter >= 3) {
		} else {
			for (int j = 0; j < 2; j++) {
				while (shotCounter < 3) {
					randomPosition = Random::RandomInt(0, 5);

					if (returnFishPosY[randomPosition] == 0) {
						for (int i = 0; i < kBulletMax; i++) {
							if (!bullets[i].effect.GetIsActive()) {
								if (!bullets[i].isActive) {
									InitializeBullets(i, { .height = 80.0f,.type = BulletType::RETURNFISH,.grHandle = grHandleBulletFish });
									bullets[i].ShotDir({ 640.0f + (bullets[i].width),200.0f - (80.0f * static_cast<float>(randomPosition)) }, { -1.0f, 0.0f }, 0.0f);
									break;
								}
							}
						}

						returnFishPosY[randomPosition] = 1;
						break;
					}
				}
			}
		}


		if (shotCounter <= 2) {
			shotCounter++;
			shotTimer = 0;
		}


	}
}

void Stage1Boss::AttackFourWall() {

	if (shotTimer >= 120) {
		shotTimer = 0;

		if (shotCounter >= 5) {
			shotCounter = 0;

			SpecialAttackSelect();
		} else {
			shotCounter++;
		}
	} else if (shotTimer >= 41) {
	} else if (shotTimer >= 40) {
		if (randomPositionY == 0) {
			for (int j = 0; j < 2; j++) {
				for (int i = 0; i < kBulletMax; i++) {
					if (!bullets[i].isActive) {
						if (!bullets[i].effect.GetIsActive()) {
							InitializeBullets(i, { .height = 80.0f,.speed = kBulletHighSpeed ,.grHandle = grHandleBulletFish });
							bullets[i].ShotDir({ 640.0f + (bullets[i].width), 120.0f + (80.0f * static_cast<float>(j)) }, { -1.0f, 0.0f }, 0.0f);
							break;
						}
					}
				}
			}
		} else if (randomPositionY == 1) {
			for (int j = 0; j < 2; j++) {
				for (int i = 0; i < kBulletMax; i++) {
					if (!bullets[i].isActive) {
						if (!bullets[i].effect.GetIsActive()) {
							InitializeBullets(i, { .height = 80.0f,.speed = kBulletHighSpeed ,.grHandle = grHandleBulletFish });
							bullets[i].ShotDir({ 640.0f + (bullets[i].width), -40.0f + (80.0f * static_cast<float>(j)) }, { -1.0f, 0.0f }, 0.0f);
							break;
						}
					}
				}
			}
		} else {
			for (int j = 0; j < 2; j++) {
				for (int i = 0; i < kBulletMax; i++) {
					if (!bullets[i].isActive) {
						if (!bullets[i].effect.GetIsActive()) {
							InitializeBullets(i, { .height = 80.0f, .speed = kBulletHighSpeed  ,.grHandle = grHandleBulletFish });
							bullets[i].ShotDir({ 640.0f + (bullets[i].width), -200.0f + (80.0f * static_cast<float>(j)) }, { -1.0f, 0.0f }, 0.0f);
							break;
						}
					}
				}
			}
		}
	} else if (shotTimer > 1) {
	} else if (shotTimer > 0) {

		randomPositionY = Random::RandomInt(0, 2);

		if (randomPositionY == 0) {
			for (int j = 0; j < 4; j++) {
				for (int i = 0; i < kBulletMax; i++) {
					if (!bullets[i].isActive) {
						if (!bullets[i].effect.GetIsActive()) {
							InitializeBullets(i, { .height = 80.0f, .speed = 8.0f ,.grHandle = grHandleBulletFish });
							bullets[i].ShotDir({ 640.0f + (bullets[i].width), -200.0f + (80.0f * static_cast<float>(j)) }, { -1.0f, 0.0f }, 0.0f);
							break;
						}
					}
				}
			}
		} else if (randomPositionY == 1) {
			for (int j = 0; j < 2; j++) {
				for (int i = 0; i < kBulletMax; i++) {
					if (!bullets[i].isActive) {
						if (!bullets[i].effect.GetIsActive()) {
							InitializeBullets(i, { .height = 80.0f, .speed = 8.0f ,.grHandle = grHandleBulletFish });
							bullets[i].ShotDir({ 640.0f + (bullets[i].width), -200.0f + (80.0f * static_cast<float>(j)) }, { -1.0f, 0.0f }, 0.0f);
							break;
						}
					}
				}
			}

			for (int j = 0; j < 2; j++) {
				for (int i = 0; i < kBulletMax; i++) {
					if (!bullets[i].isActive) {
						if (!bullets[i].effect.GetIsActive()) {
							InitializeBullets(i, { .height = 80.0f, .speed = 8.0f ,.grHandle = grHandleBulletFish });
							bullets[i].ShotDir({ 640.0f + (bullets[i].width), 120.0f + (80.0f * static_cast<float>(j)) }, { -1.0f, 0.0f }, 0.0f);
							break;
						}
					}
				}
			}
		} else {
			for (int j = 0; j < 4; j++) {
				for (int i = 0; i < kBulletMax; i++) {
					if (!bullets[i].isActive) {
						if (!bullets[i].effect.GetIsActive()) {
							InitializeBullets(i, { .height = 80.0f, .speed = 8.0f ,.grHandle = grHandleBulletFish });
							bullets[i].ShotDir({ 640.0f + (bullets[i].width), -40.0f + (80.0f * static_cast<float>(j)) }, { -1.0f, 0.0f }, 0.0f);
							break;
						}
					}
				}
			}
		}
	}
}

void Stage1Boss::AttackRandomFish() {
	int randomPosition;

	if (shotTimer >= 60) {
		shotTimer = 0;
		CommonAttackSelect();


	} else if (shotTimer >= 31) {

	} else if (shotTimer >= 30) {
		randomPosition = Random::RandomInt(0, 2);

		if (randomPosition == 0) {
			for (int i = 0; i < kBulletMax; i++) {
				if (!bullets[i].isActive) {
					if (!bullets[i].effect.GetIsActive()) {
						InitializeBullets(i, { .height = 480.0f });
						bullets[i].ShotDir({ 640.0f + (bullets[i].width), 0.0f }, { -1.0f, 0.0f }, 0.0f);
						break;
					}
				}
			}
		} else if (randomPosition == 1) {
			randomPosition = Random::RandomInt(0, 200);

			for (int i = 0; i < kBulletMax; i++) {
				if (!bullets[i].isActive) {
					if (!bullets[i].effect.GetIsActive()) {
						InitializeBullets(i, { .height = 80.0f,.speed = 12.0f,.grHandle = grHandleBulletFish });
						bullets[i].TurnDir({ 640.0f + (bullets[i].width),0.0f }, { -1.0f,1.0f }, static_cast<float>(randomPosition));
						break;
					}
				}
			}

			for (int i = 0; i < kBulletMax; i++) {
				if (!bullets[i].isActive) {
					if (!bullets[i].effect.GetIsActive()) {
						InitializeBullets(i, { .height = 80.0f,.speed = 12.0f,.grHandle = grHandleBulletFish });
						bullets[i].TurnDir({ 640.0f + (bullets[i].width),0.0f }, { -1.0f,-1.0f }, static_cast<float>(randomPosition));
						break;
					}
				}
			}
		} else if (randomPosition == 2) {
			randomPosition = Random::RandomInt(0, 200);

			for (int i = 0; i < kBulletMax; i++) {
				if (!bullets[i].effect.GetIsActive()) {
					if (!bullets[i].isActive) {
						InitializeBullets(i, { .height = 80.0f,.grHandle = grHandleBulletFish });
						bullets[i].WaveDir({ 640.0f + (bullets[i].width),0.0f }, { -1.0f, 0.0f }, 0.0f, static_cast<float>(randomPosition), 0.0f);
						break;
					}
				}
			}

			for (int i = 0; i < kBulletMax; i++) {
				if (!bullets[i].effect.GetIsActive()) {
					if (!bullets[i].isActive) {
						InitializeBullets(i, { .height = 80.0f,.grHandle = grHandleBulletFish });
						bullets[i].WaveDir({ 640.0f + (bullets[i].width),0.0f }, { -1.0f, 0.0f }, 180.0f, static_cast<float>(randomPosition), 0.0f);
						break;
					}
				}
			}
		}
	}
}

void Stage1Boss::AttackTurn() {
	if (shotTimer >= 40) {
		shotTimer = 0;

		//int randomPosition = Random::RandomInt(0, 3);

		if (shotCounter < 16) {
			for (int i = 0; i < kBulletMax; i++) {
				if (!bullets[i].isActive) {
					if (!bullets[i].effect.GetIsActive()) {
						InitializeBullets(i, { .height = 80.0f,.speed = 12.0f,.grHandle = grHandleBulletFish });
						if (Random::RandomInt(0, 1) == 1) {
							bullets[i].TurnDir({ 640.0f + (bullets[i].width),0.0f }, { -1.0f,1.0f }, Random::RandomFloat(0.0f, 200.0f));
						} else {
							bullets[i].TurnDir({ 640.0f + (bullets[i].width),0.0f }, { -1.0f,-1.0f }, Random::RandomFloat(0.0f, 200.0f));
						}
						break;
					}
				}
			}
		}

		if (shotCounter >= 19) {
			shotCounter = 0;

			SpecialAttackSelect();

		} else {
			shotCounter++;
		}
	}
}

void Stage1Boss::AttackMachingun() {
	if (shotTimer >= 40) {
		shotTimer = 0;

		int randomPosition = Random::RandomInt(0, 3);

		if (shotCounter < 16) {
			for (int i = 0; i < kBulletMax; i++) {
				if (!bullets[i].isActive) {
					if (!bullets[i].effect.GetIsActive()) {
						InitializeBullets(i, { .height = 80.0f ,.type = BulletType::SQUID });
						bullets[i].ShotDir({ 640.0f + (bullets[i].width), -180.0f + (120.0f * static_cast<float>(randomPosition)) }, { -1.0f, 0.0f }, 0.0f);
						break;
					}
				}
			}
		}

		if (shotCounter >= 19) {
			shotCounter = 0;

			CommonAttackSelect();

		} else {
			shotCounter++;
		}
	}
}

void Stage1Boss::AttackFishBone() {
	if (shotCounter >= 44) {
		if (shotTimer >= 20) {
			shotCounter = 0;
			shotTimer = 0;
			CommonAttackSelect();
		}
	} else if (shotCounter >= 41) {
		if (shotTimer % 20 == 0) {
			shotTimer = 0;
			for (int i = 0; i < kBulletMax; i++) {
				if (!bullets[i].isActive) {
					if (!bullets[i].effect.GetIsActive()) {
						InitializeBullets(i, { .height = 480.0f });
						bullets[i].ShotDir({ 640.0f + (bullets[i].width), 0.0f }, { -1.0f, 0.0f }, 0.0f);
						break;
					}
				}
			}

			shotCounter++;

		}
	} else if (shotCounter >= 40) {
		if (shotTimer == 30) {
			shotCounter++;
		}
	} else {
		if (shotTimer % 5 == 0) {
			if (shotTimer >= 20) {
				shotTimer = 0;
			}

			if (shotCounter % 2 == 0) {
				for (int i = 0; i < kBulletMax; i++) {
					if (shotCounter % 14 == 6) {
						if (!bullets[i].isActive) {
							if (!bullets[i].effect.GetIsActive()) {
								InitializeBullets(i, { .height = 210.0f,.grHandle = grHandleBigFishBoneBottom });
								bullets[i].ShotDir({ 640.0f + (bullets[i].width), 135.0f }, { -1.0f, 0.0f }, 0.0f);
								break;
							}
						}
					} else {
						if (!bullets[i].isActive) {
							if (!bullets[i].effect.GetIsActive()) {
								InitializeBullets(i, { .height = 120.0f,.grHandle = grHandleFishBoneBottom });
								bullets[i].ShotDir({ 640.0f + (bullets[i].width), 180.0f }, { -1.0f, 0.0f }, 0.0f);
								break;
							}
						}
					}
				}
			} else {
				for (int i = 0; i < kBulletMax; i++) {
					if (shotCounter % 14 == 13) {
						if (!bullets[i].isActive) {
							if (!bullets[i].effect.GetIsActive()) {
								InitializeBullets(i, { .height = 210.0f,.grHandle = grHandleBigFishBoneTop });
								bullets[i].ShotDir({ 640.0f + (bullets[i].width), -135.0f }, { -1.0f, 0.0f }, 0.0f);
								break;
							}
						}

					} else {
						if (!bullets[i].isActive) {
							if (!bullets[i].effect.GetIsActive()) {
								InitializeBullets(i, { .height = 120.0f,.grHandle = grHandleFishBoneTop });
								bullets[i].ShotDir({ 640.0f + (bullets[i].width), -180.0f }, { -1.0f, 0.0f }, 0.0f);
								break;
							}
						}
					}
				}
			}

			shotCounter++;

		}
	}
}

void Stage1Boss::AttackFishSwim() {
	if (shotTimer > 40) {
		shotTimer = 0;

		if (shotCounter < 8) {
			if (shotCounter % 4 == 3) {
				int randomPosition = Random::RandomInt(0, 3);

				for (int i = 0; i < kBulletMax; i++) {
					if (!bullets[i].effect.GetIsActive()) {
						if (!bullets[i].isActive) {
							InitializeBullets(i, { .height = 80.0f,.grHandle = grHandleBulletFish });
							bullets[i].WaveDir({ 640.0f + (bullets[i].width),0.0f }, { -1.0f, 0.0f }, 0.0f, 60.0f, 120.0f - (80.0f * static_cast<float>(randomPosition)));
							break;
						}
					}
				}
			} else {
				int randomPosition = Random::RandomInt(0, 5);

				for (int i = 0; i < kBulletMax; i++) {
					if (!bullets[i].effect.GetIsActive()) {
						if (!bullets[i].isActive) {
							InitializeBullets(i, { .height = 80.0f,.grHandle = grHandleBulletFish });
							bullets[i].ShotDir({ 640.0f + (bullets[i].width),200.0f - (80.0f * static_cast<float>(randomPosition)) }, { -1.0f, 0.0f }, 0.0f);
							break;
						}
					}
				}
			}

		}

		if (attackPhase == AttackPhase::SECOND) {
			if (shotCounter >= 9) {
				shotCounter = 0;
				SpecialAttackSelect();
			} else {
				shotCounter++;
			}
		} else {
			if (shotCounter >= 7) {
				shotCounter = 0;
				SpecialAttackSelect();
			} else {
				shotCounter++;
			}
		}

	}
}

void Stage1Boss::AttackBoneTussle() {

	if (shotTimer >= 160) {
		shotTimer = 0;

		if (shotCounter >= 3) {
			shotCounter = 0;

			SpecialAttackSelect();
		} else {
			shotCounter++;
		}
	} else if (shotTimer >= 41) {
	} else if (shotTimer >= 40) {
		if (randomPositionY == 0) {
			for (int i = 0; i < kBulletMax; i++) {
				if (!bullets[i].isActive) {
					if (!bullets[i].effect.GetIsActive()) {
						InitializeBullets(i, { .speed = kBulletHighSpeed });
						bullets[i].ShotDir({ 640.0f + (bullets[i].width), 160.0f }, { -1.0f, 0.0f }, 0.0f);
						break;
					}
				}
			}
		} else if (randomPositionY == 1) {
			for (int i = 0; i < kBulletMax; i++) {
				if (!bullets[i].isActive) {
					if (!bullets[i].effect.GetIsActive()) {
						InitializeBullets(i, { .speed = kBulletHighSpeed });
						bullets[i].ShotDir({ 640.0f + (bullets[i].width), 0.0f }, { -1.0f, 0.0f }, 0.0f);
						break;
					}
				}
			}
		} else {
			for (int i = 0; i < kBulletMax; i++) {
				if (!bullets[i].isActive) {
					if (!bullets[i].effect.GetIsActive()) {
						InitializeBullets(i, { .speed = kBulletHighSpeed });
						bullets[i].ShotDir({ 640.0f + (bullets[i].width), -160.0f }, { -1.0f, 0.0f }, 0.0f);
						break;
					}
				}
			}
		}
	} else if (shotTimer > 1) {
	} else {

		randomPositionY = Random::RandomInt(0, 1);

		if (randomPositionY == 0) {
			for (int i = 0; i < kBulletMax; i++) {
				if (!bullets[i].isActive) {
					if (!bullets[i].effect.GetIsActive()) {
						InitializeBullets(i, { .speed = 8.0f });
						bullets[i].ShotDir({ 640.0f + (bullets[i].width), -160.0f }, { -1.0f, 0.0f }, 0.0f);
						break;
					}
				}
			}
		} else {
			for (int i = 0; i < kBulletMax; i++) {
				if (!bullets[i].isActive) {
					if (!bullets[i].effect.GetIsActive()) {
						InitializeBullets(i, { .speed = 8.0f });
						bullets[i].ShotDir({ 640.0f + (bullets[i].width), 0.0f }, { -1.0f, 0.0f }, 0.0f);
						break;
					}
				}
			}
		}
	}
}

void Stage1Boss::AttackLight() {

	if (shotTimer >= 380) {
		shotTimer = 0;
		shotCounter = 0;

		light.isActive = false;

		light.lightNotice = false;
		chochinLightIsActive = false;

		bullets[60].Deactive();

		CommonAttackSelect();

	} else if (shotTimer >= 288) {

		if (isPhase3Start) {
			isPhase3Start = false;
			isAnger = true;
		}

		light.isActive = true;

		light.lightNotice = true;

	} else if (shotTimer >= 228) {

		light.lightNotice = false;
	} else if (shotTimer >= 226) {

		light.lightNotice = true;
	} else if (shotTimer >= 186) {

		light.lightNotice = false;

	} else if (shotTimer >= 184) {

		light.lightNotice = true;

		chochinLightIsActive = true;

	} else if (shotTimer >= 180) {

	} else if (shotTimer > 61) {
		if (bullets[60].velocity.x >= 0.0f) {
			bullets[60].velocity.x = 0.0f;

		} else {
			if (bullets[60].transform.position.x <= 0.0f) {
				//bullets[60].transform.position.x = -200.0f;
				bullets[60].velocity.x += 0.5f;
			}
		}

	} else if (shotTimer > 60) {

		int randomPattern;

		if (isPhase3Start) {
			randomPattern = 0;
		} else {
			randomPattern = Random::RandomInt(0, 2);
		}

		if (randomPattern == 0) {

			if (!bullets[60].isActive) {
				if (!bullets[60].effect.GetIsActive()) {
					InitializeBullets(60, { .height = 160.0f });
					bullets[60].ShotDir({ 640.0f + (bullets[60].width), 0.0f }, { -1.0f, 0.0f }, 0.0f);
				}
			}
		} else if (randomPattern == 1) {

			if (!bullets[60].effect.GetIsActive()) {
				if (!bullets[60].isActive) {
					InitializeBullets(60, { .height = 80.0f });
					bullets[60].ShotDir({ 640.0f + (bullets[60].width), 200.0f }, { -1.0f, 0.0f }, 0.0f);
				}
			}

		} else {

			if (!bullets[60].effect.GetIsActive()) {
				if (!bullets[60].isActive) {
					InitializeBullets(60, { .height = 80.0f });
					bullets[60].ShotDir({ 640.0f + (bullets[60].width), -200.0f }, { -1.0f, 0.0f }, 0.0f);

				}
			}
		}

	}
}