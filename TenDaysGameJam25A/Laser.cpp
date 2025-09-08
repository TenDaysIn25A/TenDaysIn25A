#include "Laser.h"

#include "Laser.h"

Laser::Laser() { Initialize(); }

void Laser::Initialize() {
	width = 1280.0f;
	height = 240.0f;
	isActive = false;

	color = kColor;

	transform.position = { 0.0f, 0.0f };
	transform.rotation = 0.0f;
	transform.scale = { 1.0f, 1.0f };

	timer = 0;
	timerMax = 0;

	grHandleBox = Novice::LoadTexture("./Resources/images/box.png");
}

void Laser::Update() {
	if (!isActive) {
		return;
	}

	if (timer >= timerMax) {
		isActive = false;
	}

	timer++;
}

void Laser::Draw()const {
	if (!isActive) {
		return;
	}
	
	if (currentDimension == DimensionState::TWO) {
		renderer.DrawSprite(transform, width, beforeHeight, 0.0f, grHandleBox, color);
	} else {
		Transform2D t = transform;
		t.position.y = 0.0f;
		renderer.DrawSprite(t, width, beforeHeight, 0.0f, grHandleBox, color);
	}
}

void Laser::LaserCreate(const Vector2& position, float setWidth, float setHeight, int setTimerMax) {
	transform.position = position;
	transform.position.x = 0.0f;
	width = setWidth;
	beforeHeight = setHeight;
	height = setHeight;
	timerMax = setTimerMax;

	timer = 0;
	isActive = true;
}
