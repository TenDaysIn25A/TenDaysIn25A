#include "DrawEffects.h"

void DrawEffects::StartImplosion(const Vector2& endPosition, float range, float duration, const Transform2D& camera, Ease ease) {

	Initialize(endPosition, range, duration, camera, ease, EFFECT_IMPLSION);

	if (isPlayerEffect) {
		// ランダムに散らばった開始位置
		for (int i = 0; i < kCircleCountPlayer; i++) {
			spawnPos_[i] = {Random::RandomFloat(endPosition.x - range, endPosition.x + range), Random::RandomFloat(endPosition.y - range, endPosition.y + range)};
		}
	} else {
		// ランダムに散らばった開始位置
		for (int i = 0; i < kCircleCount; i++) {
			spawnPos_[i] = {Random::RandomFloat(endPosition.x - range, endPosition.x + range), Random::RandomFloat(endPosition.y - range, endPosition.y + range)};
		}
	}
}

void DrawEffects::StartExplosion(const Vector2& startPosition, float range, float duration, const Transform2D& camera, Ease ease) {
	Initialize(startPosition, range, duration, camera, ease, EFFECT_EXPLOSION);

	if (isPlayerEffect) {
		// 爆発なので、開始位置は中心
		for (int i = 0; i < kCircleCountPlayer; i++) {
			// ランダム方向に散らばらせる
			float angle = Random::RandomFloat(0.0f, 2.0f * static_cast<float>(M_PI));
			float distance = Random::RandomFloat(0.0f, range);
			spawnPos_[i] = startPosition + Vector2(cosf(angle), sinf(angle)) * distance;
		}

	} else {
		// 爆発なので、開始位置は中心
		for (int i = 0; i < kCircleCount; i++) {
			// ランダム方向に散らばらせる
			float angle = Random::RandomFloat(0.0f, 2.0f * static_cast<float>(M_PI));
			float distance = Random::RandomFloat(0.0f, range);
			spawnPos_[i] = startPosition + Vector2(cosf(angle), sinf(angle)) * distance;
		}
	}
}

void DrawEffects::Update(float deltaTime) {
	if (!isActive_) {
		return;
	}

	t_ += deltaTime / duration_;

	if (t_ >= 1.0f) {
		t_ = 1.0f;
		isActive_ = false;
	}
}

void DrawEffects::Draw() const {
	if (!isActive_) {
		return;
	}

	float easedT = Tweening::Easing(t_, easeType_);

	if (isPlayerEffect) {
		for (int i = 0; i < kCircleCountPlayer; i++) {
			Vector2 currentPos;
			Transform2D currentTransform;

			if (type_ == EFFECT_IMPLSION) {
				currentPos = Lerp(spawnPos_[i], endPosition_, easedT);
			} else if (type_ == EFFECT_EXPLOSION) {
				currentPos = Lerp(endPosition_, spawnPos_[i], easedT);
			}

			unsigned int alpha = Lerp(0x00000000u, 0x000000FFu, easedT);
			currentTransform.position = currentPos;
			currentTransform.scale_ = {scale_, scale_};

			if (isActiveFade_) {
				renderer_.DrawSprite(currentTransform, 6.0f, 6.0f, 0.0f, grHandle_, color_ - alpha);
			} else {
				renderer_.DrawSprite(currentTransform, 6.0f, 6.0f, 0.0f, grHandle_, color_);
			}
		}

	} else {

		for (int i = 0; i < kCircleCount; i++) {
			Vector2 currentPos;
			Transform2D currentTransform;

			if (type_ == EFFECT_IMPLSION) {
				currentPos = Lerp(spawnPos_[i], endPosition_, easedT);
			} else if (type_ == EFFECT_EXPLOSION) {
				currentPos = Lerp(endPosition_, spawnPos_[i], easedT);
			}

			unsigned int alpha = Lerp(0x00000000u, 0x000000FFu, easedT);
			currentTransform.position = currentPos;
			currentTransform.scale_ = {scale_, scale_};

			if (isActiveFade_) {
				renderer_.DrawSprite(currentTransform, 6.0f, 6.0f, 0.0f, grHandle_, color_ - alpha);
			} else {
				renderer_.DrawSprite(currentTransform, 6.0f, 6.0f, 0.0f, grHandle_, color_);
			}
		}
	}
}

void DrawEffects::Initialize(const Vector2& pos, float range, float duration, const Transform2D& camera, Ease ease, EffectType type) {
	alpha_ = 0x00000000;
	endPosition_ = pos;
	range_ = range;
	duration_ = duration;
	t_ = 0.0f;
	isActive_ = true;
	easeType_ = ease;
	type_ = type;
	renderer_.SetCamera(camera);
}

Vector2 DrawEffects::Lerp(const Vector2& a, const Vector2& b, float t) { return a + (b - a) * t; }
float DrawEffects::Lerp(float a, float b, float t) { return a + (b - a) * t; }
unsigned int DrawEffects::Lerp(unsigned int a, unsigned int b, float t) { return static_cast<unsigned int>(a + (b - a) * t); }