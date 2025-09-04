#include "Stage4Boss.h"

Stage4Boss::Stage4Boss() { Initialize(); }

void Stage4Boss::Initialize() {
	speed = 10.0f;
	width = 128.0f;
	height = 480.0f;
	isAlive = true;
	hp = 300;
	maxHp = 300;

	color = kColor;

	exchengePhaseSecondHp = 200;
	exchengePhaseThirdHp = 100;

	shotTimer = 0;
	shotCounter = 0;
	transform.position = { -576.0f, 0.0f };
	transform.rotation = 0.0f;
	transform.scale = { 1.0f, 1.0f };
	attack = Stage4BossAttack::WALL;
	attackPhase = AttackPhase::FIRST;

	grHandleCaracter = Novice::LoadTexture("./Resources/images/box.png");
	grHandleBullet = Novice::LoadTexture("./Resources/images/box.png");

	for (int i = 0; i < kBulletMax; i++) {
		InitializeBullets(i, {});
	}
}

void Stage4Boss::InitializeBullets(int index, const BulletConfig& bulletConfig) {
	bullets[index].Initialize();
	bullets[index].width = bulletConfig.width;
	bullets[index].height = bulletConfig.height;
	bullets[index].damage = bulletConfig.damage;
	bullets[index].speed = bulletConfig.speed;
	bullets[index].color = bulletConfig.color;
	bullets[index].grHandle = this->grHandleBullet;
}

void Stage4Boss::Update() {
	input.Update();

	//死んだら、ここで返る
	if (!isAlive) {
		return;
	}

	Shot();

	for (int i = 0; i < kBulletMax; i++) {
		bullets[i].Update();
	}

	if (attackPhase == AttackPhase::FIRST) {
		if (hp <= exchengePhaseSecondHp) {
			attackPhase = AttackPhase::SECOND;
		}
	} else if (attackPhase == AttackPhase::SECOND) {
		if (hp <= exchengePhaseThirdHp) {
			attackPhase = AttackPhase::THIRD;
		}
	}

	color = kColor;
}

void Stage4Boss::Draw() const {
	//死んだら、ここで返る
	if (!isAlive) {
		return;
	}

	Novice::ScreenPrintf(0, 0, "%d/%d", hp, maxHp);

	for (int i = 0; i < kBulletMax; i++) {
		bullets[i].Draw();
	}

	renderer.DrawSprite(transform, width, height, 0.0f, grHandleCaracter, color);
}

void Stage4Boss::SetCamera(const Transform2D& camera) { renderer.SetCamera(camera); }

void Stage4Boss::Move() {

}

void Stage4Boss::TakeDamage(int damage) {
	if (!isAlive) {
		return;
	}

	hp -= damage;

	color = kDamageColor;

	if (hp <= 0) {
		Destory();
	}
}

void Stage4Boss::Destory() {
	isAlive = false;

	for (int i = 0; i < kBulletMax; i++) {
		bullets[i].Deactive();
	}
}

void Stage4Boss::Shot() {
	switch (attack) {
	case Stage4BossAttack::WALL:
		AttackWall();
		break;
	case Stage4BossAttack::MACHINGUN:
		AttackMachingun();
		break;
	case Stage4BossAttack::TUNNEL:
		AttackFishBone();
		break;
	case Stage4BossAttack::ALL_WALL:
		AttackAllWall();
		break;
	case Stage4BossAttack::FOURWALL:
		AttackFourWall();
		break;
	}

	shotTimer++;
}

void Stage4Boss::CommonAttackSelect() {
	switch (attackPhase) {
	case AttackPhase::FIRST:
		attack = Stage4BossAttack::WALL;
		break;
	case AttackPhase::SECOND:
		attack = Stage4BossAttack::MACHINGUN;
		break;
	case AttackPhase::THIRD:
		attack = Stage4BossAttack::FOURWALL;
		break;
	}
}

void Stage4Boss::SpecialAttackSelect() {
	int randomAttack;
	switch (attackPhase) {
	case AttackPhase::FIRST:
		randomAttack = Random::RandomInt(1, 2);

		if (randomAttack == 1) {
			attack = Stage4BossAttack::ALL_WALL;
		} else if (randomAttack == 2) {
			attack = Stage4BossAttack::TUNNEL;
		} else {
		}
		break;
	case AttackPhase::SECOND:
		randomAttack = Random::RandomInt(1, 2);

		if (randomAttack == 1) {
			attack = Stage4BossAttack::ALL_WALL;
		} else if (randomAttack == 2) {
			attack = Stage4BossAttack::TUNNEL;
		} else {
		}
		break;
	case AttackPhase::THIRD:
		randomAttack = Random::RandomInt(1, 2);
		
		if (randomAttack == 1) {
			attack = Stage4BossAttack::ALL_WALL;
		} else if (randomAttack == 2) {
			attack = Stage4BossAttack::TUNNEL;
		} else {
		}
		break;
	}
}

void Stage4Boss::AttackWall() {
	if (shotTimer >= 80) {
		shotTimer = 0;

		int randomPosition;

		if (shotCounter >= 7) {
			randomPosition = Random::RandomInt(0, 1);

			for (int i = 0; i < kBulletMax; i++) {
				if (!bullets[i].isActive) {
					InitializeBullets(i, {});
					bullets[i].height = 160.0f;
					if (randomPosition == 0) {
						bullets[i].ShotDir({ transform.position.x, 160.0f }, { 1.0f, 0.0f }, 0.0f);
					} else {
						bullets[i].ShotDir({ transform.position.x, -160.0f }, { 1.0f, 0.0f }, 0.0f);
					}
					break;
				}
			}
		} else {
			randomPosition = Random::RandomInt(-1, 1);

			for (int i = 0; i < kBulletMax; i++) {
				if (!bullets[i].isActive) {
					InitializeBullets(i, {});
					bullets[i].ShotDir({ transform.position.x, 0 + (160.0f * static_cast<float>(randomPosition)) }, { 1.0f, 0.0f }, 0.0f);
					break;
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

void Stage4Boss::AttackFourWall() {
	randomPositionY;

	if (shotTimer >= 160) {
		shotTimer = -1;

		if (shotCounter >= 3) {
			shotCounter = 0;

			SpecialAttackSelect();
		} else {
			shotCounter++;
		}
	} else if (shotTimer >= 80) {

	} else if (shotTimer >= 1) {
		if (shotTimer % 20 == 0) {
			for (int i = 0; i < kBulletMax; i++) {
				if (!bullets[i].isActive) {
					InitializeBullets(i, {});
					bullets[i].ShotDir({ transform.position.x, 0 + (160.0f * static_cast<float>(randomPositionY)) }, { 1.0f, 0.0f }, 0.0f);
					break;
				}
			}
		}

	} else {

		randomPositionY = Random::RandomInt(-1, 1);

		for (int i = 0; i < kBulletMax; i++) {
			if (!bullets[i].isActive) {
				InitializeBullets(i, {});
				bullets[i].ShotDir({ transform.position.x, 0 + (160.0f * static_cast<float>(randomPositionY)) }, { 1.0f, 0.0f }, 0.0f);
				break;
			}
		}

	}
}

void Stage4Boss::AttackMachingun() {
	if (shotTimer >= 40) {
		shotTimer = 0;

		int randomPosition = Random::RandomInt(0, 3);

		for (int i = 0; i < kBulletMax; i++) {
			if (!bullets[i].isActive) {
				InitializeBullets(i,{.height = 120.0f});
				bullets[i].ShotDir({ transform.position.x, -180.0f + (120.0f * static_cast<float>(randomPosition)) }, { 1.0f, 0.0f }, 0.0f);
				break;
			}
		}

		if (shotCounter >= 15) {
			shotCounter = 0;

			SpecialAttackSelect();

		} else {
			shotCounter++;
		}
	}



}

void Stage4Boss::AttackFishBone() {
	if (shotTimer % 10 == 0) {
		if (shotTimer >= 20) {
			shotTimer = 0;
		}

		if (shotCounter % 2 == 0) {
			for (int i = 0; i < kBulletMax; i++) {
				if (shotCounter % 10 == 4) {
					if (!bullets[i].isActive) {
						InitializeBullets(i,{.height = 200.0f});
						bullets[i].ShotDir({ transform.position.x, 140.0f }, { 1.0f, 0.0f }, 0.0f);
						break;

					}
				} else {
					if (!bullets[i].isActive) {
						InitializeBullets(i,{.height = 120.0f});
						bullets[i].ShotDir({ transform.position.x, 180.0f }, { 1.0f, 0.0f }, 0.0f);
						break;
					}
				}


			}
		} else {
			for (int i = 0; i < kBulletMax; i++) {
				if (shotCounter % 10 == 9) {
					if (!bullets[i].isActive) {
						InitializeBullets(i,{.height = 200.0f});
						bullets[i].ShotDir({ transform.position.x, -140.0f }, { 1.0f, 0.0f }, 0.0f);
						break;
					}

				} else {
					if (!bullets[i].isActive) {
						InitializeBullets(i,{.height = 120.0f});
						bullets[i].ShotDir({ transform.position.x, -180.0f }, { 1.0f, 0.0f }, 0.0f);
						break;
					}
				}
			}
		}

		if (shotCounter >= 59) {
			shotCounter = 0;

			CommonAttackSelect();
		} else {
			shotCounter++;
		}
	}


}

void Stage4Boss::AttackAllWall() {
	if (shotTimer >= 80) {
		shotTimer = 0;

		int randomPosition;

		if (shotCounter == 7 || shotCounter == 0) {
			for (int i = 0; i < kBulletMax; i++) {
				if (!bullets[i].isActive) {
					bullets[i].height = 480.0f;
					InitializeBullets(i, {.height = 480.0f});
					bullets[i].ShotDir({ transform.position.x, 0.0f }, { 1.0f, 0.0f }, 0.0f);
					break;
				}
			}
		} else {
			randomPosition = Random::RandomInt(-1, 1);

			for (int i = 0; i < kBulletMax; i++) {
				if (!bullets[i].isActive) {
					InitializeBullets(i, {});
					bullets[i].ShotDir({ transform.position.x, 0 + (160.0f * static_cast<float>(randomPosition)) }, { 1.0f, 0.0f }, 0.0f);
					break;
				}
			}
		}

		if (shotCounter >= 7) {
			shotCounter = 0;

			CommonAttackSelect();
		} else {
			shotCounter++;
		}
	}
}
