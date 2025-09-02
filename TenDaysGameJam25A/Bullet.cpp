#include "Bullet.h"

Bullet::Bullet() { Initialize(); }

void Bullet::Initialize() {
	speed = 10.0f;
	width = 80.0f;
	height = 100.0f;
	direction = {0.0f, 0.0f};
	isActive = false;
	transform.position = {-1000.0f, -1000.0f};
	grHandle = Novice::LoadTexture("./Resources/images/box.png");
	effect.SetScale(2.0f);
}

void Bullet::Update() {
	effect.Update();

	if (!isActive) {
		return;
	}
		
	oneDimTransform.position = {transform.position.x, 0.0f};

	Move();
	DeactiveOutOfWindow();
}

void Bullet::Draw() const {
	effect.Draw();

	if (!isActive) {
		return;
	}

	if (currentDimension == DimensionState::TWO) {
		renderer.DrawSprite(transform, width, height, 0.0f, grHandle, 0xFFFFFFFF);
	}
	if (currentDimension == DimensionState::ONE) {
		renderer.DrawSprite(oneDimTransform, width, 80.0f, 0.0f, grHandle, 0xFFFFFFFF);
	} 

} 

void Bullet::ShotPos(const Vector2& startPos, const Vector2& endPos, float spreadRotationDegree) {
	isActive = true;
	transform.position = startPos;

	// 基本の向き
	Vector2 baseDir = Vector2::Normalize(endPos - startPos);

	float spreadRadian = spreadRotationDegree * (static_cast<float>(M_PI) / 180.0f);

	float angle = Random::RandomFloat(-spreadRadian, spreadRadian);

	float cosA = std::cos(angle);
	float sinA = std::sin(angle);
	direction.x = baseDir.x * cosA - baseDir.y * sinA;
	direction.y = baseDir.x * sinA + baseDir.y * cosA;

	// 速度
	velocity = direction * speed;

	// 回転角度を direction_ から求める
	transform.rotation = static_cast<float>(std::atan2(direction.y, direction.x));
}

void Bullet::ShotDir(const Vector2& startPos, const Vector2& dir, float spreadRotationDegree) {

	isActive = true;
	transform.position = startPos;

	// 基本の向き
	Vector2 baseDir = Vector2::Normalize(dir);

	float spreadRadian = spreadRotationDegree * (static_cast<float>(M_PI) / 180.0f);

	float angle = Random::RandomFloat(-spreadRadian, spreadRadian);

	float cosA = std::cos(angle);
	float sinA = std::sin(angle);
	direction.x = baseDir.x * cosA - baseDir.y * sinA;
	direction.y = baseDir.x * sinA + baseDir.y * cosA;

	// 速度
	velocity = direction * speed;

	// 回転角度を direction_ から求める
	transform.rotation = static_cast<float>(std::atan2(direction.y, direction.x));
}

void Bullet::Deactive() {
	isActive = false;
	effect.StartExplosion(transform.position, 500.0f, 0.7f, renderer.GetCamera(), EASE_OUT_QUAD);
}

void Bullet::SetCamera(const Transform2D& camera) { renderer.SetCamera(camera); }

void Bullet::DeactiveOutOfWindow() {
	if (transform.position.x >= 640.0f + width) {
		Deactive();
	}
	
	if (transform.position.x <= -(640.0f + width)) {
		Deactive();
	}
	
	if (transform.position.y >= 360.0f + height) {
		Deactive();
	}
	
	if (transform.position.y <= -(360.0f + height)) {
		Deactive();
	}
}

void Bullet::Move() { transform.Translate(velocity); }
