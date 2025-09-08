#include "Player.h"

Player::Player() { Initialize(); }

void Player::Initialize() {
	transform.position = { -300.0f, 0.0f };
	isAlive = true;
	currentLife = 3;
	for (int i = 0; i < currentLife; i++) {

		life[i].position.x = -580.0f + i * 60.0f;
		life[i].position.y = -300.0f;
	}
	grhandleLife = Novice::LoadTexture("./Resources/images/heart.png");
	isInvinciblity = false;
	isUpDamage = false;
	invincibleTimer = 0;
	speed = 10.0f;
	parry.Initialize();
	damageUpTime = 150;

	width = 80.0f;
	height = 79.0f;

	hitBoxHeight = 50.0f;
	hitBoxWidth = 50.0f;

	shotType = ShotType::MACHINEGUN;//ShotType::SHOTGUN;
	shotCoolTime = kDefaultShotCoolTime;
	magazine = 0;
	pelletAmount = 0;

	// パリィ
	parry.transform.position.x = transform.position.x + width;
	parry.transform.position.y = transform.position.y;
	parry.width = width;
	parry.height = height;
	parry.parryState = ParryState::NONE;
	parry.isParryAble = false;
	parry.isCanJust = false;

	grHandleCaracterDimTwo = Novice::LoadTexture("./Resources/images/Chiriri.png");
	grHandleCaracterDimOne = Novice::LoadTexture("./Resources/images/box.png");

	for (int bi = 0; bi < kBulletMax; bi++) {
		bullets[bi].Initialize();
		bullets[bi].height = 40.0f;
		bullets[bi].width = 40.0f;
		bullets[bi].direction = { 1.0f, 0.0f };
		bullets[bi].damage = kDefaultDamage;
		bullets[bi].speed = 40.0f;
		bullets[bi].grHandle = Novice::LoadTexture("./Resources/images/ChiririBulletA.png");
	}

	shotTimer = shotCoolTime;

	currentStamina = kMaxStamina;
	grhandleStamina = Novice::LoadTexture("./Resources/images/box.png");
	stamina.position = { 100.0f, -300.0f };
	staminaRecoverCoolTime = kStaminaRecoverCoolTime;

	miss.Initialize(Novice::LoadTexture("./Resources/images/miss.png"), 256.0f, 128.0f);
	nice.Initialize(Novice::LoadTexture("./Resources/images/nice.png"), 512.0f, 128.0f);
	just.Initialize(Novice::LoadTexture("./Resources/images/just.png"), 512.0f, 128.0f);

	leftTop.position = { transform.position.x - width / 2.0f,transform.position.y + height / 2.0f };
	rightTop.position = { transform.position.x + width / 2.0f,transform.position.y + height / 2.0f };
	leftBottom.position = { transform.position.x - width / 2.0f,transform.position.y - height / 2.0f };
	rightBottom.position = { transform.position.x + width / 2.0f,transform.position.y - height / 2.0f };
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


	if (currentDimension == DimensionState::ONE) {

		parry.Update();

		parry.transform.position.x = transform.position.x + width + 1;

		currentStamina -= kConsumedStamina;

		staminaRecoverCoolTime = kStaminaRecoverCoolTime;

		transform.rotation = 0.0f;
	} else {



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

		transform.Rotate(10.0f);
	}

	if (shotType == ShotType::MACHINEGUN) {
		MachinGunBullet();
	} else if (shotType == ShotType::SHOTGUN) {
		ShotGunBullet();
	}

	Move();

	ClampInWindow2D();

	leftTop.position = { transform.position.x - width / 2.0f,transform.position.y + height / 2.0f };
	rightTop.position = { transform.position.x + width / 2.0f,transform.position.y + height / 2.0f };
	leftBottom.position = { transform.position.x - width / 2.0f,transform.position.y - height / 2.0f };
	rightBottom.position = { transform.position.x + width / 2.0f,transform.position.y - height / 2.0f };




}

void Player::MachinGunBullet() {

	if (isUpDamage) {

		damageUpTime--;

		for (int bi = 0; bi < kBulletMax; bi++) {
			bullets[bi].damage = kUpedDamage;
		}

		shotCoolTime = kUpedShotCoolTime;

		if (damageUpTime == 0) {
			damageUpTime = 150;
			isUpDamage = false;
		}
	} else {
		for (int bi = 0; bi < kBulletMax; bi++) {
			bullets[bi].damage = kDefaultDamage;
		}
		shotCoolTime = kDefaultShotCoolTime;
	}

	if (currentDimension == DimensionState::TWO) {

		for (int bi = 0; bi < kBulletMax; bi++) {
			bullets[bi].transform.Rotate(20.0f);
		}

		if (click.GetClick(0)) {

			if (shotTimer >= shotCoolTime) {

				bulletPattern = Random::RandomInt(1, 3);

				shotTimer = 0;

				for (int bi = 0; bi < kBulletMax; bi++) {

					if (!bullets[bi].isActive) {
						if (!bullets[bi].effect.GetIsActive()) {
							bullets[bi].ShotDir(transform.position, bullets[bi].direction, 0.0f);

							bullets[bi].transform.rotation = Random::RandomFloat(1.0f, 30.0f);

							if (bulletPattern == 1) {
								bullets[bi].grHandle = Novice::LoadTexture("./Resources/images/ChiririBulletA.png");
							} else if (bulletPattern == 2) {
								bullets[bi].grHandle = Novice::LoadTexture("./Resources/images/ChiririBulletB.png");
							} else {
								bullets[bi].grHandle = Novice::LoadTexture("./Resources/images/ChiririBulletC.png");
							}

							if (isUpDamage) {
								bullets[bi].color = 0xD00000FF;
							} else {
								bullets[bi].color = 0xFFFFFFFF;
							}
							break;
						}
					}
				}
			}
		}

	}

	for (int bi = 0; bi < kBulletMax; bi++) {
		bullets[bi].Update();
	}

	if (shotTimer < shotCoolTime) {
		shotTimer++;
	}
}

void Player::ShotGunBullet() {

	if (isUpDamage) {

		damageUpTime--;

		magazine = kUpedDamage;

	

		if (damageUpTime == 0) {
			damageUpTime = 150;
			isUpDamage = false;
		}

	} else {

		for (int bi = 0; bi < kBulletMax; bi++) {
			bullets[bi].damage = kDefaultDamage;
		}
		
	}

	shotCoolTime = kDefaultShotCoolTime;

	if (magazine > kMagazineSize) {
		magazine = kMagazineSize;
	}

	Novice::ScreenPrintf(0, 0, "%d", magazine);

	if (currentDimension == DimensionState::TWO) {

		for (int bi = 0; bi < kBulletMax; bi++) {
			bullets[bi].transform.Rotate(20.0f);
		}

		if (click.GetClick(0)) {

			if (magazine > 0) {
				if (shotTimer >= shotCoolTime) {

					bulletPattern = Random::RandomInt(1, 3);

					shotTimer = 0;

					for (int bi = 0; bi < kBulletMax; bi++) {

						if (!bullets[bi].isActive) {
							if (!bullets[bi].effect.GetIsActive()) {
								bullets[bi].ShotDir(transform.position, bullets[bi].direction, 20.0f);

								bulletPattern = Random::RandomInt(1, 3);

								bullets[bi].transform.rotation = Random::RandomFloat(1.0f, 30.0f);

								if (bulletPattern == 1) {
									bullets[bi].grHandle = Novice::LoadTexture("./Resources/images/ChiririBulletA.png");
								} else if (bulletPattern == 2) {
									bullets[bi].grHandle = Novice::LoadTexture("./Resources/images/ChiririBulletB.png");
								} else {
									bullets[bi].grHandle = Novice::LoadTexture("./Resources/images/ChiririBulletC.png");
								}

								if (isUpDamage) {
									bullets[bi].color = 0xD00000FF;
								} else {
									bullets[bi].color = 0xFFFFFFFF;
								}
								
								pelletAmount++;

								if (pelletAmount >= kPelletMaxAmount) {

									pelletAmount = 0;

									magazine--;
									break;
								}
							}
						}
					}
				}
			}
		}

	}

	for (int bi = 0; bi < kBulletMax; bi++) {
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

		if (currentDimension == DimensionState::TWO) {
			renderer.DrawSprite(transform, width, height, 0.0f, grHandleCaracterDimTwo, 0xFFFFFFFF);
		} else {
			renderer.DrawSprite(transform, width, height, 0.0f, grHandleCaracterDimOne, 0x00D000FF);
		}
	}

	for (int bi = 0; bi < kBulletMax; bi++) {
		bullets[bi].Draw();
	}
}

void Player::SetCamera(const Transform2D& camera) { renderer.SetCamera(camera); }

void Player::Move() {
	velocity = { 0.0f, 0.0f };
	direction = { 0.0f, 0.0f };

	if (currentDimension == DimensionState::TWO) {

		if (input.GetKey(DIK_W)) {
			direction.y = 1.0f;
		}

		if (input.GetKey(DIK_S)) {
			direction.y = -1.0f;
		}
	}

	if (input.GetKey(DIK_A)) {
		direction.x = -1.0f;
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

	if (transform.position.x >= 360.0f) {
		transform.position.x = 360.0f;
	}

	if (transform.position.x <= -600.0f) {
		transform.position.x = -600.0f;
	}
}

void Player::ClampInWindow1D() { transform.position.y = 0.0f; }

void Player::Destroy() { isAlive = false; }
