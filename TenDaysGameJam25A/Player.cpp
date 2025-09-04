#include "Player.h"

Player::Player() { Initialize(); }

void Player::Initialize() {
	transform.position = { 300.0f,0.0f };
	isAlive = true;
	life = 3;
	isInvinciblity = false;
	isUpDamage = false;
	invincibleTimer = 0;
	speed = 5.0f;
	parry.Initialize();
	damageUpTime = 150;

	width = 80.0f;
	height = 80.0f;

	shotCoolTime = kDefaultShotCoolTime;

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
		bullets[bi].speed = 40.0f;
	}

	shotTimer = shotCoolTime;

	miss.Initialize(Novice::LoadTexture("./Resources/images/miss.png"), 256.0f, 128.0f);
	nice.Initialize(Novice::LoadTexture("./Resources/images/nice.png"), 512.0f, 128.0f);
	just.Initialize(Novice::LoadTexture("./Resources/images/just.png"), 512.0f, 128.0f);
}

void Player::Update() {
	input.Update();

	miss.Update();
	nice.Update();
	just.Update();

	transform.position.x = 300.0f + (3 - life) * 160.0f;

	if (isInvinciblity) {

		if (invincibleTimer > 0) {
			invincibleTimer--;
		} else {
			isInvinciblity = false;
		}
	}

	if (isUpDamage) {

		damageUpTime--;

		for (int bi = 0;bi < kBulletMax;bi++) {
			bullets[bi].damage = kUpedDamage;
		}

		shotCoolTime = kUpedShotCoolTime;

		if (damageUpTime == 0) {
			damageUpTime = 150;
			isUpDamage = false;
		}
	} else {
		for (int bi = 0;bi < kBulletMax;bi++) {
			bullets[bi].damage = kDefaultDamage;
		}

		shotCoolTime = kDefaultShotCoolTime;
	}

	if (currentDimension == DimensionState::ONE) {

		parry.Update();

		parry.transform.position.x = transform.position.x - width;


	} else {

		Move();

		if (input.GetKey(DIK_SPACE)) {

			if (shotTimer >= shotCoolTime) {

				shotTimer = 0;

				for (int bi = 0;bi < kBulletMax;bi++) {

					if (!bullets[bi].isActive) {
						bullets[bi].ShotDir(transform.position, bullets[bi].direction, 0.0f);

						if (isUpDamage) {
							bullets[bi].color = 0xFF0000FF;
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

	if (shotTimer < shotCoolTime) {
		shotTimer++;
	}
}

void Player::TakeDamage(int damage) {

	if (isInvinciblity) {
		return;
	}

	life -= damage;
	invincibleTimer = kInvincibleTimer;

	if (life <= 0) {
		Destroy();
	}

}

void Player::Draw() const {
	parry.Draw();

	if (invincibleTimer % 4 <= 1) {
		renderer.DrawSprite(transform, width, height, 0.0f, grHandleCaracter, 0x2222FFFF);
	}

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
