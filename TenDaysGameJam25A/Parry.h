#pragma once
#include "DrawEffects.h"
#include "Renderer.h"
#include "Vector2.h"
#include "Collision.h"
#include "Input.h"

enum class ParryState { NONE, NORMAL, JUST };

class Parry {

public:
	Parry();

	//=====================================
	// メンバ関数
	//=====================================
	void Initialize();
	void Update();
	void Draw() const;

	//=====================================
	// メンバ変数
	//=====================================

	// システム
	//-------------------------------
	Renderer renderer;
	Input input;
	DrawEffects effect;

	// プロパティ
	//------------------------------
	Transform2D transform;
	float width;
	float height;

	// フラグ
	//------------------------------
	bool isParryAble;
	bool isCanJust;
	ParryState parryState;

	// 定数
	//------------------------------
	static constexpr int kNomalParryAbleGrace = 8;
	static constexpr int kJustParryAbleGrace = 4;

	int canJustTimer;
	unsigned int color;
	FillMode kFillMode;
};
