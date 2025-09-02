#include "Enemy.h"

Enemy::Enemy() { Initialize(); }

void Enemy::Initialize() {
	speed = 10.0f;
	radius = 64.0f;
	isAlive = true;
	hp = 100;
	maxHp = 100;
	transform.position = { -500.0f, 0.0f };
	transform.rotation = 0.0f;
	transform.scale = { 1.0f, 1.0f };
}

void Enemy::Update() {
	input.Update();

	//死んだら、ここで返る
	if (!isAlive) {
		return;
	}

}

void Enemy::Draw() const {
	//死んだら、ここで返る
	if (!isAlive) {
		return;
	}

	renderer.DrawEllipse(transform, { radius,radius }, { 0.0f, 0.0f }, 0.0f, 0xFFAAAAFF, kFillModeSolid);

	Novice::ScreenPrintf(0, 0, "%d/%d", hp, maxHp);
}

void Enemy::SetCamera(const Transform2D& camera) { renderer.SetCamera(camera); }

void Enemy::Move() {

}

void Enemy::Shot() {

}

void Enemy::TakeDamage(int damage) {

	hp -= damage;

	if (hp <= 0) {
		Destory();
	}

}

void Enemy::Destory(){
	isAlive = false;
}
