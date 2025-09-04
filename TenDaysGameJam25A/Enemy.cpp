#include "Enemy.h"

Enemy::Enemy() { Initialize(); }

void Enemy::Initialize() {
	speed = 10.0f;
	radius = 64.0f;
	isAlive = true;
	hp = 150;
	maxHp = 150;
	shotTimer = 0;
	shotCounter = 0;
	transform.position = { -500.0f, 0.0f };
	transform.rotation = 0.0f;
	transform.scale = { 1.0f, 1.0f };
	attack = EnemyAttack::WALL;
	attackPhase = AttackPhase::FIRST;

	for (int i = 0; i < kBulletMax; i++) {
		bullets[i].Initialize();
		bullets[i].width = 80.0f;
		bullets[i].height = 160.0f;
	}


}

void Enemy::Update() {
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
		if (hp <= (maxHp / 3) * 2) {
			attackPhase = AttackPhase::SECOND;
		}
	} else if (attackPhase == AttackPhase::SECOND) {
		if (hp <= (maxHp / 3)) {
			attackPhase = AttackPhase::THIRD;
		}
	}

}

void Enemy::Draw() const {
	//死んだら、ここで返る
	if (!isAlive) {
		return;
	}

	Novice::ScreenPrintf(0, 0, "%d/%d", hp, maxHp);

	for (int i = 0; i < kBulletMax; i++) {
		bullets[i].Draw();
	}

	renderer.DrawEllipse(transform, { radius,radius }, { 0.0f, 0.0f }, 0.0f, 0xFFAAAAFF, kFillModeSolid);
}

void Enemy::SetCamera(const Transform2D& camera) { renderer.SetCamera(camera); }

void Enemy::Move() {

}

void Enemy::TakeDamage(int damage) {
	if (!isAlive) {
		return;
	}

	hp -= damage;

	if (hp <= 0) {
		Destory();
	}
}

void Enemy::Destory() {
	isAlive = false;
}

void Enemy::Shot() {
	switch (attack) {
	case EnemyAttack::WALL:
		AttackWall();
		break;
	case EnemyAttack::MACHINGUN:
		AttackMachingun();
		break;
	case EnemyAttack::TUNNEL:
		AttackFishBone();
		break;
	case EnemyAttack::ALL_WALL:
		AttackAllWall();
		break;
	}

	shotTimer++;
}

void Enemy::CommonAttackSelect() {
	switch (attackPhase) {
	case AttackPhase::FIRST:
		attack = EnemyAttack::WALL;
		break;
	case AttackPhase::SECOND:
		attack = EnemyAttack::MACHINGUN;
		break;
	case AttackPhase::THIRD:
		break;
	}
}

void Enemy::SpecialAttackSelect() {
	int randomAttack;
	switch (attackPhase) {
	case AttackPhase::FIRST:
		randomAttack = 1;//Random::RandomInt(1, 2);

		if (randomAttack == 1) {
			attack = EnemyAttack::ALL_WALL;
		} else if (randomAttack == 2) {
			attack = EnemyAttack::TUNNEL;
		} else {
		}
		break;
	case AttackPhase::SECOND:
		randomAttack = Random::RandomInt(1, 2);

		if (randomAttack == 1) {
			attack = EnemyAttack::ALL_WALL;
		} else if (randomAttack == 2) {
			attack = EnemyAttack::TUNNEL;
		} else {
		}
		break;
	case AttackPhase::THIRD:
		break;
	}
}

void Enemy::AttackWall() {
	if (shotTimer >= 80) {
		shotTimer = 0;

		int randomPosition;

		if (shotCounter >= 7) {
			randomPosition = Random::RandomInt(0, 1);

			for (int i = 0; i < kBulletMax; i++) {
				if (!bullets[i].isActive) {
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
					bullets[i].height = 160.0f;
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

void Enemy::AttackMachingun() {
	if (shotTimer >= 40) {
		shotTimer = 0;

		int randomPosition = Random::RandomInt(0, 3);

		for (int i = 0; i < kBulletMax; i++) {
			if (!bullets[i].isActive) {
				bullets[i].height = 120.0f;
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

void Enemy::AttackFishBone() {
	if (shotTimer % 10 == 0) {
		if (shotTimer >= 20) {
			shotTimer = 0;
		}

		if (shotCounter % 2 == 0) {
			for (int i = 0; i < kBulletMax; i++) {
				if (shotCounter % 10 == 4) {
					if (!bullets[i].isActive) {
						bullets[i].height = 240.0f;
						bullets[i].ShotDir({ transform.position.x, 120.0f }, { 1.0f, 0.0f }, 0.0f);
						break;

					}
				} else {
					if (!bullets[i].isActive) {
						bullets[i].height = 120.0f;
						bullets[i].ShotDir({ transform.position.x, 180.0f }, { 1.0f, 0.0f }, 0.0f);
						break;
					}
				}


			}
		} else {
			for (int i = 0; i < kBulletMax; i++) {
				if (shotCounter % 10 == 9) {
					if (!bullets[i].isActive) {
						bullets[i].height = 240.0f;
						bullets[i].ShotDir({ transform.position.x, -120.0f }, { 1.0f, 0.0f }, 0.0f);
						break;
					}

				} else {
					if (!bullets[i].isActive) {
						bullets[i].height = 120.0f;
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

void Enemy::AttackAllWall() {
	if (shotTimer >= 639) {
		for (int i = 0; i < kBulletMax; i++) {
			if (!bullets[i].isActive) {
				bullets[i].height = 480.0f;
				bullets[i].ShotDir({ transform.position.x, 0 }, { 1.0f, 0.0f }, 0.0f);
				break;
			}
		}

		shotTimer = 0;
		shotCounter = 0;

		CommonAttackSelect();

	} else if (shotTimer % 60 == 0) {
		for (int i = 0; i < kBulletMax; i++) {
			if (!bullets[i].isActive) {
				bullets[i].height = 480.0f;
				bullets[i].ShotDir({ transform.position.x, 0 }, { 1.0f, 0.0f }, 0.0f);
				break;
			}
		}
	}
}
