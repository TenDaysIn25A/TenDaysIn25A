#include "Bullet.h"

Bullet::Bullet() { Initialize(); }

void Bullet::Initialize() {
	speed = 10.0f;
	width = 80.0f;
	height = 100.0f;
	direction = { 0.0f, 0.0f };
	isActive = false;
	timer = 0;
	theta = 0.0f;
	waveAmplitudeY = 0.0f;
	waveOffsetY = 0.0f;
	isLightShines = false;
	isTurn = false;
	isHermitClabStop = false;
	transform.scale = { 1.0f,1.0f };
	transform.position = { -1000.0f, -1000.0f };
	grHandle = Novice::LoadTexture("./Resources/images/box.png");
	grHandleBox = Novice::LoadTexture("./Resources/images/box.png");
	effect.SetScale(2.0f);
	effect.Initialize();
	color = 0xFFFFFFFF;
	type = BulletType::SHOT;
}

void Bullet::Update() {
	effect.Update();

	if (!isActive) {
		return;
	}

	oneDimTransform.position = { transform.position.x, 0.0f };

	if (type == BulletType::RETURNFISH) {
		FishMove();
	} else if (type == BulletType::SQUID) {
		squidMove();
	} else if (type == BulletType::WAVE) {
		WaveMove();
	} else if (type == BulletType::TURN) {
		TurnMove();
	} else if (type == BulletType::HERMITCLAB) {
		ClabMove();
	} else {
		Move();
	}

	DeactiveOutOfWindow();
}

void Bullet::Draw() const {
	effect.Draw();

	if (!isActive) {
		return;
	}

	if (currentDimension == DimensionState::TWO) {
		renderer.DrawSprite(transform, width, height, 0.0f, grHandle, color);
	}
	if (currentDimension == DimensionState::ONE) {
		renderer.DrawSprite(oneDimTransform, width, 80.0f, 0.0f, grHandleBox, color);
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

void Bullet::WaveDir(const Vector2& startPos, const Vector2& dir, float setTheta, float amplitude, float waveOffset) {

	isActive = true;
	transform.position = startPos;

	// 基本の向き
	Vector2 baseDir = Vector2::Normalize(dir);

	waveAmplitudeY = amplitude;
	waveOffsetY = waveOffset;
	theta = setTheta;

	float angle = 0.0f;

	float cosA = std::cos(angle);
	float sinA = std::sin(angle);
	direction.x = baseDir.x * cosA - baseDir.y * sinA;
	direction.y = baseDir.x * sinA + baseDir.y * cosA;

	// 速度
	velocity = direction * speed;

	// 回転角度を direction_ から求める
	transform.rotation = static_cast<float>(std::atan2(direction.y, direction.x));

	type = BulletType::WAVE;
}

void Bullet::TurnDir(const Vector2& startPos, const Vector2& dir, float amplitude) {

	isActive = true;
	transform.position = startPos;

	// 基本の向き
	Vector2 baseDir = Vector2::Normalize({ dir.x,0.0f });

	waveAmplitudeY = amplitude;
	waveOffsetX = startPos.x;
	waveOffsetY = 0.0f;
	if (dir.y >= 0.0f) {
		theta = 90.0f;
	} else {
		theta = 270.0f;
	}

	float angle = 0.0f;

	float cosA = std::cos(angle);
	float sinA = std::sin(angle);
	direction.x = baseDir.x * cosA - baseDir.y * sinA;
	direction.y = baseDir.x * sinA + baseDir.y * cosA;

	// 速度
	velocity = direction * speed;

	// 回転角度を direction_ から求める
	transform.rotation = static_cast<float>(std::atan2(direction.y, direction.x));
	direction.y = dir.y;

	type = BulletType::TURN;
}

void Bullet::Deactive() {
	isActive = false;
	effect.StartExplosion(transform.position, 500.0f, 0.7f, renderer.GetCamera(), EASE_OUT_QUAD);
	transform.position = { -1000.0f,-1000.0f };
}

void Bullet::SetCamera(const Transform2D& camera) { renderer.SetCamera(camera); }

void Bullet::DeactiveOutOfWindow() {
	if (velocity.x >= 0.0f) {
		if (transform.position.x >= 640.0f + width) {
			Deactive();
		}
	} else {
		if (transform.position.x <= -(640.0f + width)) {
			Deactive();
		}
	}

	if (transform.position.y >= 360.0f + height) {
		Deactive();
	}

	if (transform.position.y <= -(360.0f + height)) {
		Deactive();
	}
}


void Bullet::Move() { transform.Translate(velocity); }

void Bullet::FishMove() {
	if (isLightShines) {
		if (transform.rotation < static_cast<float>(M_PI) * 2.0f) {
			if (transform.rotation >= 5.41f) {
				speed -= 1.0f;
			} else {
				if (transform.rotation < 4.11f) {
					speed += 1.0f;
				} else {
					speed = 10.0f;

				}
			}

			transform.Rotate(speed);
			if (transform.rotation >= static_cast<float>(M_PI) * 2.0f) {
				speed = 0.0f;
			}
		} else {
			speed += 0.4f;

			velocity = direction * -speed;

			transform.rotation = static_cast<float>(M_PI) * 2.0f;
			transform.Translate(velocity);

		}
	} else {
		if (transform.position.x <= -300.0f) {
			if (velocity.x < 0.0f) {
				velocity.x += 0.5f;
				transform.Translate(velocity);
			} else {
				velocity.x = 0.0f;
			}
		} else {
			transform.Translate(velocity);
		}
	}
}

void Bullet::squidMove() {
	if (velocity.x > 1.0f) {
		velocity.x = -20.0f;
		transform.scale.x = 1.0f;
		transform.Translate(velocity);
	} else {
		transform.Scale({ -0.01f,0.0f });
		velocity.x += 0.4f;
		transform.Translate(velocity);
	}
}

void Bullet::WaveMove() {
	transform.position.x += velocity.x;
	transform.position.y = (sinf(theta * (static_cast<float>(M_PI) / 180.0f)) * waveAmplitudeY) + waveOffsetY;
	theta += 5.0f;

	if (theta >= 360.0f) {
		theta -= 360.0f;
	}
}

void Bullet::TurnMove() {
	waveOffsetX += velocity.x;
	transform.position.x = (cosf(theta * (static_cast<float>(M_PI) / 180.0f)) * waveAmplitudeY) + waveOffsetX;
	transform.position.y = (sinf(theta * (static_cast<float>(M_PI) / 180.0f)) * waveAmplitudeY) + waveOffsetY;

	if (direction.y >= 0.0f) {
		if (theta >= 270.0f) {
			theta = 270.0f;
			transform.rotation = static_cast<float>(M_PI) * 2;
			velocity.x = speed;
		} else {
			if (waveOffsetX <= -400.0f) {
				velocity.x = 0.0f;
				theta += (speed / 2.0f) * (100.0f / waveAmplitudeY);
				transform.Rotate((speed / 2.0f) * (100.0f / waveAmplitudeY));
			}
		}
	} else {
		if (theta <= 90.0f) {
			theta = 90.0f;
			transform.rotation = static_cast<float>(M_PI) * 2;
			velocity.x = speed;
		} else {
			if (waveOffsetX <= -400.0f) {
				velocity.x = 0.0f;
				theta -= (speed / 2.0f) * (100.0f / waveAmplitudeY);
				transform.Rotate(-(speed / 2.0f) * (100.0f / waveAmplitudeY));
			}
		}
	}
}

void Bullet::PlayerBulletHit() {
	if (type == BulletType::HERMITCLAB) {
		isHermitClabStop = true;
		velocity.x = 10.0f;
	}
}

void Bullet::ClabMove() {
	if (isHermitClabStop) {
		if (velocity.x <= 0.0f) {
			velocity.x = 0.0f;
		} else {
			velocity -= 1.0f;
		}
	}

	transform.Translate(velocity);
}

void Bullet::FishLightShine(const Vector2& lightPos) {
	isLightShines = true;

	// 基本の向き

	Vector2 baseDir = Vector2::Normalize(transform.position - lightPos);

	baseDir;

	/*float spreadRadian = (static_cast<float>(M_PI) / 180.0f);

	float angle = Random::RandomFloat(-spreadRadian, spreadRadian);

	float cosA = std::cos(angle);
	float sinA = std::sin(angle);
	direction.x = baseDir.x * cosA - baseDir.y * sinA;
	direction.y = baseDir.x * sinA + baseDir.y * cosA;*/

	// 速度
	velocity = direction * -speed;

	speed = 0.0f;
	// 回転角度を direction_ から求める
	//transform.rotation = static_cast<float>(std::atan2(direction.y, direction.x));
}
