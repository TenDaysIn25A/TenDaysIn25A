#include "Player.h"

Player::Player() { Initialize(); }

void Player::Initialize() {
	transform.position = { -300.0f,0.0f };
	isAlive = true;
	currentLife = 3;
	for(int i = 0;i < currentLife;i++){
	
		life[i].position.x = -580.0f + i * 60.0f;
		life[i].position.y = -300.0f;

	}
	grhandleLife = Novice::LoadTexture("./Resources/images/box.png");
	isInvinciblity = false;
	isUpDamage = false;
	invincibleTimer = 0;
	speed = 10.0f;
	parry.Initialize();
	damageUpTime = 150;

	width = 80.0f;
	height = 80.0f;

	shotCoolTime = kDefaultShotCoolTime;

	//パリィ
	parry.transform.position.x = transform.position.x + width;
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
		bullets[bi].direction = { 1.0f,0.0f };
		bullets[bi].damage = kDefaultDamage;
		bullets[bi].speed = 40.0f;
	}

	shotTimer = shotCoolTime;

	currentStamina = kMaxStamina;
	grhandleStamina = Novice::LoadTexture("./Resources/images/box.png");
	stamina.position = { 100.0f,-300.0f };
	staminaRecoverCoolTime = kStaminaRecoverCoolTime;

	miss.Initialize(Novice::LoadTexture("./Resources/images/miss.png"), 256.0f, 128.0f);
	nice.Initialize(Novice::LoadTexture("./Resources/images/nice.png"), 512.0f, 128.0f);
	just.Initialize(Novice::LoadTexture("./Resources/images/just.png"), 512.0f, 128.0f);
}

void Player::Update() {
	input.Update();
	click.Update();

	miss.Update();
	nice.Update();
	just.Update();

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

		parry.transform.position.x = transform.position.x + width + 1;


		currentStamina -= kConsumedStamina;


		staminaRecoverCoolTime = kStaminaRecoverCoolTime;
	} else {

		Move();

		if (click.GetClick(0)) {

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

		if (currentStamina < kMaxStamina) {

			if (staminaRecoverCoolTime > 0) {
				staminaRecoverCoolTime--;
			} else {
				currentStamina += kRecoverStaminaAmount;
			}

		} else {
			currentStamina = kMaxStamina;
			staminaRecoverCoolTime = kStaminaRecoverCoolTime;
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

	currentLife -= damage;
	invincibleTimer = kInvincibleTimer;

	if (currentLife <= 0) {
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

	if (input.GetKey(DIK_A)) {
		direction.x = -1.0f;
	}

	if (input.GetKey(DIK_S)) {
		direction.y = -1.0f;
	}

	if (input.GetKey(DIK_D)) {
		direction.x = 1.0f;
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

	if (transform.position.x >= 380.0f) {
		transform.position.x = 380.0f;
	}

	if (transform.position.x <= -600.0f) {
		transform.position.x = -600.0f;
	}
}

void Player::ClampInWindow1D() {
	transform.position.y = 0.0f;
}

void Player::Destroy() { isAlive = false; }
