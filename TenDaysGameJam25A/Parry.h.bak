#pragma once
#include "DrawEffects.h"
#include "Renderer.h"
#include "Vector2.h"
#include "Collision.h"
#include "Input.h"

enum class ParryState { NONE, GOOD, JUST };

class Parry {

public:
	Parry();
	void Initialize();

	//=====================================
	// メンバ関数
	//=====================================
	int isPlayerParry(Vector2 notePos, float noteWidth, float noteWeight, Vector2 playerPos, float playerWidth, float playerHeight);

	//=====================================
	// メンバ変数
	//=====================================

	// システム
	//-------------------------------
	Renderer renderer;
	Input input;
	DrawEffects effect;

	// フラグ
	//------------------------------
	bool isParryAble;
	bool isJustParry;
	bool isNomalParry;
	bool isParryFailed;
	ParryState parryState;

	// 定数
	//------------------------------
	const int kNomalParryAbleGrace = 8;
	const int kJustParryAbleGrace = 3;
};
