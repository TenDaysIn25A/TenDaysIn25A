#include "Enemy.h"

Enemy::Enemy() { Initialize(); }

void Enemy::Initialize() {
	speed = 10.0f;
	radius = 64.0f;
	isAlive = true;
	hp = 45;
	maxHp = 45;
	shotTimer = 0;
	shotCounter = 0;
	transform.position = { -500.0f, 0.0f };
	transform.rotation = 0.0f;
	transform.scale = { 1.0f, 1.0f };
	attack = EnemyAttack::WALL;

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


}

void Enemy::Draw() const {
	//死んだら、ここで返る
	if (!isAlive) {
		return;
	}

	for (int i = 0; i < kBulletMax; i++) {
		bullets[i].Draw();
	}

	renderer.DrawEllipse(transform, { radius,radius }, { 0.0f, 0.0f }, 0.0f, 0xFFAAAAFF, kFillModeSolid);
}

void Enemy::SetCamera(const Transform2D& camera) { renderer.SetCamera(camera); }

void Enemy::Move() {

}

void Enemy::Shot() {
	switch (attack) {
	case EnemyAttack::WALL:
		if (shotTimer >= 80) {
			AttackWall();
			shotTimer = 0;

			if (shotCounter >= 8) {
				shotCounter = 0;
				int randomAttack = Random::RandomInt(1, 3);

				if (randomAttack == 1) {
					attack = EnemyAttack::MACHINGUN;
				} else if (randomAttack == 2) {
					attack = EnemyAttack::TUNNEL;
				} else {
					attack = EnemyAttack::ALL_WALL;
				}
			} else {
				shotCounter++;
			}
		}
		break;
	case EnemyAttack::MACHINGUN:
		if (shotTimer >= 40) {
			AttackMachingun();
			shotTimer = 0;

			if (shotCounter >= 16) {
				shotCounter = 0;

				attack = EnemyAttack::WALL;

			} else {
				shotCounter++;
			}
		}
		break;
	case EnemyAttack::TUNNEL:
		if (shotTimer >= 20) {
			AttackTunnel();
			shotTimer = 0;

			if (shotCounter >= 60) {
				shotCounter = 0;

				attack = EnemyAttack::WALL;
			} else {
				shotCounter++;
			}

		} else if (shotTimer >= 8) {
		} else if (shotTimer >= 7) {
			AttackTunnel();
			shotCounter++;
		}
		break;
	case EnemyAttack::ALL_WALL:
		if (shotTimer >= 80) {
			AttackAllWall();
			shotTimer = 0;

			if (shotCounter >= 8) {
				shotCounter = 0;
				attack = EnemyAttack::WALL;
			} else {
				shotCounter++;
			}
		}
		break;
	}

	shotTimer++;
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

void Enemy::AttackWall() {
	int randomPosition;

	if (shotCounter >= 8) {
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


}

void Enemy::AttackMachingun() {
	int randomPosition = Random::RandomInt(0, 3);

	for (int i = 0; i < kBulletMax; i++) {
		if (!bullets[i].isActive) {
			bullets[i].height = 120.0f;
			bullets[i].ShotDir({ transform.position.x, -180.0f + (120.0f * static_cast<float>(randomPosition)) }, { 1.0f, 0.0f }, 0.0f);
			break;
		}
	}

}

void Enemy::AttackTunnel() {
	if (shotCounter % 2 == 0) {
		for (int i = 0; i < kBulletMax; i++) {
			if (!bullets[i].isActive) {
				bullets[i].height = 120.0f;
				bullets[i].ShotDir({ transform.position.x, 180.0f }, { 1.0f, 0.0f }, 0.0f);
				break;
			}
		}
	} else {
		for (int i = 0; i < kBulletMax; i++) {
			if (!bullets[i].isActive) {
				bullets[i].height = 120.0f;
				bullets[i].ShotDir({ transform.position.x, -180.0f }, { 1.0f, 0.0f }, 0.0f);
				break;
			}
		}
	}

	if (shotCounter % 16 == 15) {
		for (int i = 0; i < kBulletMax; i++) {
			if (!bullets[i].isActive) {
				bullets[i].height = 120.0f;
				bullets[i].ShotDir({ transform.position.x, 60.0f }, { 1.0f, 0.0f }, 0.0f);
				break;
			}
		}
	} else if (shotCounter % 16 == 7) {
		for (int i = 0; i < kBulletMax; i++) {
			if (!bullets[i].isActive) {
				bullets[i].height = 120.0f;
				bullets[i].ShotDir({ transform.position.x, -60.0f }, { 1.0f, 0.0f }, 0.0f);
				break;
			}
		}
	}
}

void Enemy::AttackAllWall(){
	for (int i = 0; i < kBulletMax; i++) {
		if (!bullets[i].isActive) {
			bullets[i].height = 480.0f;
			bullets[i].ShotDir({ transform.position.x, 0}, { 1.0f, 0.0f }, 0.0f);
			break;
		}
	}
}
