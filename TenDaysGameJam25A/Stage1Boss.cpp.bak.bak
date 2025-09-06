#include "Stage1Boss.h"

Stage1Boss::Stage1Boss() { Initialize(); }

void Stage1Boss::Initialize() {
	speed = 10.0f;
	width = 240.0f;
	height = 480.0f;
	isAlive = true;
	hp = 300;
	maxHp = 300;

	color = kColor;

	exchengePhaseSecondHp = 200;
	exchengePhaseThirdHp = 100;

	shotTimer = 0;
	shotCounter = 0;
	transform.position = { 640.0f - (width / 2.0f), 0.0f };
	transform.rotation = 0.0f;
	transform.scale = { 1.0f, 1.0f };
	attack = Stage1BossAttack::WALL;
	attackPhase = AttackPhase::FIRST;

	grHandleCaracter = Novice::LoadTexture("./Resources/images/box.png");
	grHandleBullet = Novice::LoadTexture("./Resources/images/box.png");

	for (int i = 0; i < kBulletMax; i++) {
		InitializeBullets(i, {});
		bullets[i].effect.Initialize(grHandleBullet, 30.0f, 30.0f);
	}

	hpGauge.Initialize();
	hpGauge.CreateHpGauge({0.0f,240.0f},hp,maxHp,500.0f,60.0f,color,true);
}

void Stage1Boss::InitializeBullets(int index, const BulletConfig& bulletConfig) {
	bullets[index].Initialize();
	bullets[index].width = bulletConfig.width;
	bullets[index].height = bulletConfig.height;
	bullets[index].damage = bulletConfig.damage;
	bullets[index].speed = bulletConfig.speed;
	bullets[index].color = bulletConfig.color;
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

	if (attackPhase == AttackPhase::FIRST) {
		if (hp <= exchengePhaseSecondHp) {
			attackPhase = AttackPhase::SECOND;
		}
	} else if (attackPhase == AttackPhase::SECOND) {
		if (hp <= exchengePhaseThirdHp) {
			attackPhase = AttackPhase::THIRD;
		}
	}

	hpGauge.ReferenceHp(hp,maxHp);
	hpGauge.Update();

	color = kColor;
}

void Stage1Boss::Draw() const {
	//死んだら、ここで返る
	if (!isAlive) {
		return;
	}

	Novice::ScreenPrintf(0, 0, "%d/%d", hp, maxHp);

	hpGauge.Draw();
	renderer.DrawSprite(transform, width, height, 0.0f, grHandleCaracter, color);

	for (int i = 0; i < kBulletMax; i++) {
		bullets[i].Draw();
	}
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
	switch (attack) {
	case Stage1BossAttack::WALL:
		AttackWall();
		break;
	case Stage1BossAttack::MACHINGUN:
		AttackMachingun();
		break;
	case Stage1BossAttack::FISHBONE:
		AttackFishBone();
		break;
	case Stage1BossAttack::ALL_WALL:
		AttackAllWall();
		break;
	case Stage1BossAttack::FOURWALL:
		AttackFourWall();
		break;
	case Stage1BossAttack::PAPYRUS:
		AttackFourWall();
		break;
	}

	shotTimer++;
}

void Stage1Boss::CommonAttackSelect() {
	switch (attackPhase) {
	case AttackPhase::FIRST:
		attack = Stage1BossAttack::WALL;
		break;
	case AttackPhase::SECOND:
		attack = Stage1BossAttack::MACHINGUN;
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
		randomAttack = 2;//Random::RandomInt(1, 2);

		if (randomAttack == 1) {
			attack = Stage1BossAttack::ALL_WALL;
		} else if (randomAttack == 2) {
			attack = Stage1BossAttack::FISHBONE;
		} else {
		}
		break;
	case AttackPhase::SECOND:
		randomAttack = 2;//Random::RandomInt(1, 2);

		if (randomAttack == 1) {
			attack = Stage1BossAttack::ALL_WALL;
		} else if (randomAttack == 2) {
			attack = Stage1BossAttack::FISHBONE;
		} else {
		}
		break;
	case AttackPhase::THIRD:
		randomAttack = 2;//Random::RandomInt(1, 2);

		if (randomAttack == 1) {
			attack = Stage1BossAttack::ALL_WALL;
		} else if (randomAttack == 2) {
			attack = Stage1BossAttack::FISHBONE;
		} else {
		}
		break;
	}
}

void Stage1Boss::AttackWall() {
	if (shotTimer >= 80) {
		shotTimer = 0;

		if (shotCounter >= 7) {
			shotCounter = 0;

			SpecialAttackSelect();
		} else {
			shotCounter++;
		}
	}else if (shotTimer > 41) {
	}else if (shotTimer > 40) {
		int randomPosition;

		if (shotCounter >= 7) {
			randomPosition = Random::RandomInt(0, 1);

			for (int i = 0; i < kBulletMax; i++) {
				if (!bullets[i].isActive) {
					if (!bullets[i].effect.GetIsActive()) {
						InitializeBullets(i, { .height = 160.0f });
						if (randomPosition == 0) {
							bullets[i].ShotDir({ 640.0f + (bullets[i].width), 160.0f }, { -1.0f, 0.0f }, 0.0f);
						} else {
							bullets[i].ShotDir({ 640.0f + (bullets[i].width), -160.0f }, { -1.0f, 0.0f }, 0.0f);
						}
						break;
					}
				}
			}
		} else {
			randomPosition = Random::RandomInt(-1, 1);

			for (int i = 0; i < kBulletMax; i++) {
				if (!bullets[i].effect.GetIsActive()) {
					if (!bullets[i].isActive) {
						InitializeBullets(i, {});
						bullets[i].ShotDir({ 640.0f + (bullets[i].width), 0 + (160.0f * static_cast<float>(randomPosition)) }, { -1.0f, 0.0f }, 0.0f);
						break;
					}
				}
			}
		}

		
	} else {
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

		randomPositionY = Random::RandomInt(0, 2);

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

			for (int i = 0; i < kBulletMax; i++) {
				if (!bullets[i].isActive) {
					if (!bullets[i].effect.GetIsActive()) {
						InitializeBullets(i, { .speed = 8.0f });
						bullets[i].ShotDir({ 640.0f + (bullets[i].width), 0.0f }, { -1.0f, 0.0f }, 0.0f);
						break;
					}
				}
			}
		} else if (randomPositionY == 1) {
			for (int i = 0; i < kBulletMax; i++) {
				if (!bullets[i].isActive) {
					if (!bullets[i].effect.GetIsActive()) {
						InitializeBullets(i, { .speed = 8.0f });
						bullets[i].ShotDir({ 640.0f + (bullets[i].width), -160.0f }, { -1.0f, 0.0f }, 0.0f);
						break;
					}
				}
			}

			for (int i = 0; i < kBulletMax; i++) {
				if (!bullets[i].isActive) {
					if (!bullets[i].effect.GetIsActive()) {
						InitializeBullets(i, { .speed = 8.0f });
						bullets[i].ShotDir({ 640.0f + (bullets[i].width), 160.0f }, { -1.0f, 0.0f }, 0.0f);
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

			for (int i = 0; i < kBulletMax; i++) {
				if (!bullets[i].isActive) {
					if (!bullets[i].effect.GetIsActive()) {
						InitializeBullets(i, { .speed = 8.0f });
						bullets[i].ShotDir({ 640.0f + (bullets[i].width), 160.0f }, { -1.0f, 0.0f }, 0.0f);
						break;
					}
				}
			}
		}
	}
}

void Stage1Boss::AttackMachingun() {
	if (shotTimer >= 40) {
		shotTimer = 0;

		int randomPosition = Random::RandomInt(0, 3);

		for (int i = 0; i < kBulletMax; i++) {
			if (!bullets[i].isActive) {
				if (!bullets[i].effect.GetIsActive()) {
					InitializeBullets(i, { .height = 120.0f });
					bullets[i].ShotDir({ 640.0f + (bullets[i].width), -180.0f + (120.0f * static_cast<float>(randomPosition)) }, { -1.0f, 0.0f }, 0.0f);
					break;
				}
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

void Stage1Boss::AttackFishBone() {
	if (shotCounter >= 44) {
		if (shotTimer >= 20) {
			shotCounter = 0;
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
								InitializeBullets(i, { .height = 210.0f });
								bullets[i].ShotDir({ 640.0f + (bullets[i].width), 135.0f }, { -1.0f, 0.0f }, 0.0f);
								break;
							}
						}
					} else {
						if (!bullets[i].isActive) {
							if (!bullets[i].effect.GetIsActive()) {
								InitializeBullets(i, { .height = 120.0f });
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
								InitializeBullets(i, { .height = 210.0f });
								bullets[i].ShotDir({ 640.0f + (bullets[i].width), -135.0f }, { -1.0f, 0.0f }, 0.0f);
								break;
							}
						}

					} else {
						if (!bullets[i].isActive) {
							if (!bullets[i].effect.GetIsActive()) {
								InitializeBullets(i, { .height = 120.0f });
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

void Stage1Boss::AttackAllWall() {
	if (shotTimer >= 80) {
		shotTimer = 0;

		int randomPosition;

		if (shotCounter == 7 || shotCounter == 0) {
			for (int i = 0; i < kBulletMax; i++) {
				if (!bullets[i].isActive) {
					if (!bullets[i].effect.GetIsActive()) {
						InitializeBullets(i, { .height = 480.0f });
						bullets[i].ShotDir({ 640.0f + (bullets[i].width), 0.0f }, { -1.0f, 0.0f }, 0.0f);
						break;
					}
				}
			}
		} else {
			randomPosition = Random::RandomInt(-1, 1);

			for (int i = 0; i < kBulletMax; i++) {
				if (!bullets[i].isActive) {
					if (!bullets[i].effect.GetIsActive()) {
						InitializeBullets(i, {});
						bullets[i].ShotDir({ 640.0f + (bullets[i].width), 0 + (160.0f * static_cast<float>(randomPosition)) }, { -1.0f, 0.0f }, 0.0f);
						break;
					}
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