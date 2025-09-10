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

	bullets[0].grHandle = Novice::LoadTexture("./Resources/images/chochinFish1.png");
	bullets[1].grHandle = Novice::LoadTexture("./Resources/images/chochinWaveH.png");
	auHandleTakeDamage = Novice::LoadAudio("./Resources/sounds/snd_bullet_hit.mp3");

	hpGauge.Initialize();
	hpGauge.CreateHpGauge({ 360.0f,300.0f }, hp, kMaxHp, 500.0f, 60.0f, 0xFFFFFFFF, true);


	player.position.x = -1000.0f;
	isStop1 = false;
	isStop0 = false;
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

	} else if (tutorialLevel == 3 ) {



		if (tutorialInterval == 160) {
			if (!bullets[1].isActive) {
				bullets[1].transform.position = { 640.0f,0.0f };
				bullets[1].height = 960.0f;
				bullets[1].speed = 10.0f;
				bullets[1].ShotDir(bullets[1].transform.position, { -1.0f,0.0f }, 0.0f);
			}

			if (!bullets[0].isActive) {
				bullets[0].transform.position = { 400.0f,120.0f };
				bullets[0].height = 80.0f;
				bullets[0].ShotDir(bullets[0].transform.position, { -1.0f,0.0f }, 0.0f);
			}

		} else if(tutorialInterval == 180){

			if (bullets[1].transform.position.x <= player.position.x + 80.0f) {
				if (!isStop1) {
					bullets[1].transform.position.x = player.position.x + 80.0f;
					isStop1 = true;
				}

				bullets[1].speed = 0.0f;
			} else {
				if (!isStop1) {
					bullets[1].Update();
				}
			}

			if (bullets[0].transform.position.x <= player.position.x + 80.0f) {
				if (!isStop0) {
					bullets[0].transform.position.x = player.position.x + 80.0f;
					isStop0 = true;
				}

				bullets[0].speed = 0.0f;
			} else {
				if (!isStop0) {
					bullets[0].Update();
				}
			}

		}
	} else if (tutorialLevel == 4) {

		if (bullets[1].transform.position.x <= player.position.x + 80.0f) {
			if (!isStop1) {
				bullets[1].transform.position.x = player.position.x + 80.0f;
				isStop1 = true;
			}

			bullets[1].speed = 0.0f;
		} else {
			if (!isStop1) {
				bullets[1].Update();
			}
		}

		if (bullets[0].transform.position.x <= player.position.x + 80.0f) {
			if (!isStop0) {
				bullets[0].transform.position.x = player.position.x + 80.0f;
				isStop0 = true;
			}

			bullets[0].speed = 0.0f;
		} else {
			if (!isStop0) {
				bullets[0].Update();
			}
		}

	}else{
		bullets[0].speed = 10.0f;
		bullets[0].Update();
	
	}

	hpGauge.ReferenceHp(hp, kMaxHp);
	hpGauge.Update();
}

void Zako::Draw()const {

	if (currentDimension == DimensionState::TWO) {
		renderer.DrawSprite(transform, width, height, 0.0f, grHandleZako, 0xFFFFFFFF);

		for (int i = 0;i < kBulletMax;i++) {
			if (bullets[i].isActive) {
				renderer.DrawSprite(bullets[i].transform, bullets[i].width, bullets[i].height, 0.0f, bullets[i].grHandle, 0xFFFFFFFF);
			}
		}
	} else {
		renderer.DrawBox(transform, height, width, 0.0f, 0xFFFFFFFF, kFillModeSolid);
		for (int i = 0;i < kBulletMax;i++) {
			Transform2D oneDim[kBulletMax];
			oneDim[i].position = {bullets[i].transform.position.x,0.0f};
			if (bullets[i].isActive) {
				renderer.DrawSprite(oneDim[i], bullets[i].width, bullets[i].height, 0.0f, bullets[i].grHandleBox, 0xFFFFFFFF);
			}
		}
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

	Novice::PlayAudio(auHandleTakeDamage, false, 0.05f);
}

void Zako::Destroy() {
	isAlive = false;
}