#pragma once
#include "Dlib.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyHpGauge.h"

class Zako{

public:

	//========================
	// メンバ関数
	//========================

	Zako();

	void Initialize();
	void Update();
	void Draw()const;

	void AttackZako();

	void TakeDamage(int damage);

	void Destroy();

	//===========================
	// メンバ変数
	//===========================

	//システム
	Transform2D transform;
	Renderer renderer;

	EnemyHpGauge hpGauge;

	float width;
	float height;

	int hp;
	const int kMaxHp = 20;

	static constexpr int kBulletMax = 2;
	Bullet bullets[kBulletMax];

	Transform2D player;
	int tutorialLevel;

	int grHandleZako;

	int tutorialInterval;
	int isAlive;
	bool isStop1;
	bool isStop0;

	unsigned int color;
	const unsigned int kDamagedColor = 0xAA5555FF;

	int auHandleTakeDamage;
};

