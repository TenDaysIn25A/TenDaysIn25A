#pragma once
#include "Color.h"
#include "Random.h"
#include "Renderer.h"
#include "Transform2D.h"
#include "Tweening.h"
#include "Vector2.h"
#include <cmath>

enum EffectType { EFFECT_NONE, EFFECT_IMPLSION, EFFECT_EXPLOSION };

class DrawEffects {
public:
	DrawEffects();
	~DrawEffects() = default;

	void Initialize();
	void Update(float deltaTime = 1.0f / 60.0f);
	void Draw() const;

	// 吸い込みエフェクト
	void StartImplosion(const Vector2& endPosition, float range, float duration, const Transform2D& camera, Ease ease = EASE_OUT_QUAD);
	// 爆発エフェクト
	void StartExplosion(const Vector2& startPosition, float range, float duration, const Transform2D& camera, Ease ease = EASE_OUT_QUAD);

	bool GetIsActive() const { return isActive_; }
	void SetTexture(int textureHandle) { grHandle_ = textureHandle; }
	void SetColor(unsigned int color) { color_ = color; }

	void SetScale(float scale) { scale_ = scale; }
	void SetIsActiveFade(int isActiveFade) { isActiveFade_ = isActiveFade; }
	float GetT() { return t_; }

private:
	static constexpr int kCircleCount = 10;
	static constexpr int kCircleCountPlayer = 50;

	Vector2 spawnPos_[kCircleCountPlayer];
	Vector2 endPosition_;
	float range_;
	float duration_;
	float t_;
	bool isActive_;
	bool isActiveFade_;
	Ease easeType_;
	EffectType type_;
	unsigned int alpha_;
	unsigned int color_;

	float scale_ = 1.0f;
	int isPlayerEffect = false;

	Renderer renderer_;
	int grHandle_ = Novice::LoadTexture("./Resources/images/fx2.png");

	void Initialize(const Vector2& pos, float range, float duration, const Transform2D& camera, Ease ease, EffectType type);

	static Vector2 Lerp(const Vector2& a, const Vector2& b, float t);
	static float Lerp(float a, float b, float t);
	static unsigned int Lerp(unsigned int a, unsigned int b, float t);
};
