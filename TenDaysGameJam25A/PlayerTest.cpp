#include "PlayerTest.h"

PlayerTest::PlayerTest() { Initialize(); }

void PlayerTest::Initialize() { 
	speed = 10.0f; 
	radius = 40.0f;
	isAlive = true;
	transform.position = {0.0f, 0.0f};
	transform.rotation = 0.0f;
	transform.scale = {1.0f, 1.0f};
}
	
void PlayerTest::Update() { 
	input.Update(); 
	effect.Update();

	if (input.GetKeyTrigger(DIK_SPACE)) {
		isAlive = !isAlive;

	}
	
	// 死んでたら、ここで返る
	if (!isAlive) {
		return;
	}
	
	Move();
	ClampInWindow();
}

void PlayerTest::Draw() const {
	effect.Draw();

	// 死んでたら、ここで返る
	if (!isAlive) {
		return;
	}
	
	renderer.DrawEllipse(transform, {radius, radius}, {0.0f, 0.0f}, 0.0f, 0xFFFFFFFF, kFillModeSolid);
}

void PlayerTest::SetCamera(const Transform2D& camera) { renderer.SetCamera(camera); }

void PlayerTest::Move() {

	direction = {0.0f, 0.0f};

	if (input.GetKey(DIK_W)) {
		direction.y = 1.0f;
	}

	if (input.GetKey(DIK_S)) {
		direction.y = -1.0f;
	}

	if (input.GetKey(DIK_D)) {
		direction.x = 1.0f;
	}

	if (input.GetKey(DIK_A)) {
		direction.x = -1.0f;
	}

	velocity = Vector2::Normalize(direction) * speed;
	transform.Translate(velocity);
	
}

void PlayerTest::ClampInWindow() {
	if (transform.position.x <= -640.0f + radius) {
		transform.position.x = -640.0f + radius;
	}

	if (transform.position.x >= 640.0f - radius) {
		transform.position.x = 640.0f - radius;
	}

	if (transform.position.y <= -360.0f + radius) {
		transform.position.y = -360.0f + radius;
	}

	if (transform.position.y >= 360.0f - radius) {
		transform.position.y = 360.0f - radius;
	}
}
