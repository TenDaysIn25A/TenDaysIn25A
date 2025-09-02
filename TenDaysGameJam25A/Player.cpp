#include "Player.h"

Player::Player() { Initialize(); }

void Player::Initialize() {
	transform.position = { 300.0f,0.0f };
	isAlive = true;
	life = 3;
	isHit = false;
	isUpDamage = false;
	invincibleTimer = 60;
	speed = 5.0f;
	parry.Initialize();
	damageUpTime = 150;

	width = 80.0f;
	height = 80.0f;

	parry.transform.position.x = transform.position.x - width;
	parry.transform.position.y = transform.position.y;
	parry.width = width;
	parry.height = height;
	parry.parryState = ParryState::NONE;
	parry.isParryAble = false;
	parry.isCanJust = false;
	grHandleCaracter = Novice::LoadTexture("./Resources/images/box.png");

	for (int bi = 0;bi < kBulletMax;bi++) {
		bullets[bi].Initialize();
		bullets[bi].height = 40.0f;
		bullets[bi].width = 40.0f;
		bullets[bi].direction = { -1.0f,0.0f };
		bullets[bi].damage = kDefaultDamage;
		bullets[bi].speed = 25.0f;
	}

	shotTimer = kShotCoolTime;
}

void Player::Update() {
	input.Update();

	transform.position.x = 300.0f + (3 - life) * 160.0f;

	if (life == 0) {
		Destroy();
	}

	if (isHit) {

		if (invincibleTimer > 0) {
			invincibleTimer--;
		} else {
			isHit = false;
			invincibleTimer = 60;
		}
	}

	if (isUpDamage) {

		damageUpTime--;

		for (int bi = 0;bi < kBulletMax;bi++) {
			bullets[bi].damage = kUpedDamage;
		}

		if (damageUpTime == 0) {
			damageUpTime = 150;
			isUpDamage = false;
		}
	} else {
		for (int bi = 0;bi < kBulletMax;bi++) {
			bullets[bi].damage = kDefaultDamage;
		}
	}

	if (currentDimension == DimensionState::ONE) {

		parry.Update();

		parry.transform.position.x = transform.position.x - width;

	} else {

		Move();

		if (input.GetKey(DIK_SPACE)) {

			if (shotTimer >= kShotCoolTime) {

				shotTimer = 0;

				for (int bi = 0;bi < kBulletMax;bi++) {

					if (!bullets[bi].isActive) {
						bullets[bi].ShotDir(transform.position, bullets[bi].direction, 0.0f);

						if (isUpDamage) {
							bullets[bi].color = 0xFFFF00FF;
						} else {
							bullets[bi].color = 0xFFFFFFFF;
						}

						break;
					}
					
				}
			}
		}

		ClampInWindow2D();
	}

	for (int bi = 0;bi < kBulletMax;bi++) {
		bullets[bi].Update();
	}

	if (shotTimer < kShotCoolTime) {
		shotTimer++;
	}
}

void Player::Draw() const {
	parry.Draw();
	renderer.DrawSprite(transform, width, height, 0.0f, grHandleCaracter, 0x2222FFFF);

	for (int bi = 0;bi < kBulletMax;bi++) {
		bullets[bi].Draw();
	}

}

void Player::SetCamera(const Transform2D& camera) { renderer.SetCamera(camera); }

void Player::Move() {
	velocity = { 0.0f, 0.0f };
	direction = { 0.0f, 0.0f };

	if (input.GetKey(DIK_W)) {
		direction.y = 1.0f;
	}

	if (input.GetKey(DIK_S)) {
		direction.y = -1.0f;
	}

	velocity = Vector2::Normalize(direction) * speed;
	transform.Translate(velocity);
}

void Player::ClampInWindow2D() {
	if (transform.position.y >= 200.0f) {
		transform.position.y = 200.0f;
	}

	if (transform.position.y <= -200.0f) {
		transform.position.y = -200.0f;
	}
}

void Player::ClampInWindow1D() {
	transform.position.y = 0.0f;
}

void Player::Destroy() { isAlive = false; }
