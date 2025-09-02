#include "Enemy.h"

Enemy::Enemy() { Initialize(); }

void Enemy::Initialize() {
	speed = 10.0f;
	radius = 64.0f;
	isAlive = true;
	hp = 150;
	maxHp = 150;
	shotTimer = 0;
	transform.position = { -500.0f, 0.0f };
	transform.rotation = 0.0f;
	transform.scale = { 1.0f, 1.0f };
	attack = EnemyAttack::WALL;
	for (int i = 0; i < kBulletMax; i++) {
		bullets[i].Initialize();
		bullets[i].width = 80;
		bullets[i].height = 160;
	}
}

void Enemy::Update() {
	input.Update();

	//死んだら、ここで返る
	if (!isAlive) {
		return;
	}

	if (shotTimer >= 60) {
		AttackWall();
		shotTimer = 0;
	}

	for (int i = 0; i < kBulletMax; i++) {
		bullets[i].Update();
	}

	shotTimer++;
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

	Novice::ScreenPrintf(0, 0, "%d/%d", hp, maxHp);
}

void Enemy::SetCamera(const Transform2D& camera) { renderer.SetCamera(camera); }

void Enemy::Move() {

}

void Enemy::Shot() {
	switch (attack) {
	case EnemyAttack::WALL:
		AttackWall();
		break;
	case EnemyAttack::MACHINGUN:
		AttackMachingun();
		break;
	default:
		break;
	}
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
	int randomPosition = Random::RandomInt(-1, 1);

	for (int i = 0; i < kBulletMax; i++) {
		if (!bullets[i].isActive) {
			bullets[i].height = 160;
			bullets[i].ShotDir({transform.position.x, 0 + (160.0f * static_cast<float>(randomPosition))}, {1.0f, 0.0f}, 0.0f);
			break;
		}
	}
}

void Enemy::AttackMachingun() {}
