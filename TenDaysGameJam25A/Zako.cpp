#include "Zako.h"

Zako::Zako() { Initialize(); };

void Zako::Initialize() {

	transform.position = { 500.0f,0.0f };

	width = 80.0f;
	height = 220.0f;
	hp = kMaxHp;

	grHandleZako = Novice::LoadTexture("./Resources/images/fishBoneBickBottom.png");
	transform.rotation = 0.0f;
	transform.Rotate(90.0f);

	tutorialInterval = 0;

	for (int bi = 0;bi < kBulletMax;bi++) {
		bullets[bi].Initialize();
	}

	hpGauge.Initialize();
	hpGauge.CreateHpGauge({ 360.0f,300.0f }, hp, kMaxHp, 500.0f, 60.0f, 0xFFFFFFFF, true);


	parryArea.position.x = -1000.0f;
	isStop = false;
	isAlive = true;
	color = 0xFFFFFFFF;
}

void Zako::Update() {

	if (tutorialLevel == 1) {

		if (!bullets[0].isActive) {
			bullets[0].transform.position = { 550.0f,0.0f };
			bullets[0].height = 80.0f;
			bullets[0].ShotDir(bullets[0].transform.position, { -1.0f,0.0f }, 0.0f);
		}

		if (bullets[0].transform.position.x <= 0.0f) {
			bullets[0].transform.position.x = 0.0f;
			bullets[0].speed = 0.0f;
		} else {
			bullets[0].Update();
		}

	} else if (tutorialLevel == 4) {



		if (tutorialInterval == 179) {
			if (!bullets[0].isActive) {
				bullets[0].transform.position = { 550.0f,0.0f };
				bullets[0].height = 80.0f;
				bullets[0].speed = 10.0f;
				bullets[0].ShotDir(bullets[0].transform.position, { -1.0f,0.0f }, 0.0f);
			}
		} else if(tutorialInterval == 180){

			if (bullets[0].transform.position.x <= parryArea.position.x) {
				if (!isStop) {
					bullets[0].transform.position.x = parryArea.position.x;
					isStop = true;
				}

				bullets[0].speed = 0.0f;
			} else {
				if (!isStop) {
					bullets[0].Update();
				}
			}
		}
	} else {
		bullets[0].speed = 10.0f;
		bullets[0].Update();
	}

	hpGauge.ReferenceHp(hp, kMaxHp);
	hpGauge.Update();
}

void Zako::Draw()const {

	if (currentDimension == DimensionState::TWO) {
		renderer.DrawSprite(transform, width, height, 0.0f, grHandleZako, 0xFFFFFFFF);
	} else {
		renderer.DrawBox(transform, height, width, 0.0f, 0xFFFFFFFF, kFillModeSolid);
	}

	for (int i = 0;i < kBulletMax;i++) {
		renderer.DrawSprite(bullets[i].transform, bullets[i].width, bullets[i].height, 0.0f, bullets[i].grHandleBox, 0xFFFFFFFF);
	}
}

void Zako::AttackZako() {

	if (!bullets[0].isActive) {
		bullets[0].ShotDir(bullets[0].transform.position, { -1.0f,0.0f }, 0.0f);
	}
}
void Zako::TakeDamage(int damage) {
	if (!isAlive) {
		return;
	}

	hp -= damage;

	color = kDamagedColor;

	if (hp <= 0) {
		Destroy();
	}
}

void Zako::Destroy() {
	isAlive = false;
}