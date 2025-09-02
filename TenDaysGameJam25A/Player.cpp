#include "Player.h"

Player::Player() { Initialize(); }

void Player::Initialize() {
	transform.position = {300.0f,0.0f};
	isAlive = true;
	life = 3;
	isHit = false;
	invincibleTimer = 60;
	speed = 5.0f;
	parry.Initialize();

	transform.position.x = 800.0f;
	transform.position.y = 360.0f;
	width = 80.0f;
	height = 80.0f;

	parry.transform.position.x = transform.position.x -width;
	parry.transform.position.y = transform.position.y;
	parry.width = width;
	parry.height = height;
	parry.parryState = ParryState::NONE;

}

void Player::Update() { 
	input.Update();
	transform.position.x = 800.0f + (3 - life) * 160.0f;

	if (life == 0) {
		isAlive = false;
	}

	if (isHit) {

		if (invincibleTimer > 0) {
			invincibleTimer--;
		} else {
			isHit = false;
			invincibleTimer = 60;
		}

	} else {

	}


	if (currentDimension == DimensionState::ONE) {

		parry.Update();

		parry.transform.position.x = transform.position.x - width;

	} else {
		Move();
	}
	
}

void Player::Draw() const {}

void Player::SetCamera(const Transform2D& camera) { renderer.SetCamera(camera); }

void Player::Move() {
	velocity = {0.0f, 0.0f};
	
	if (input.GetKey(DIK_W)) {
		direction.y = 1.0f;
	}

	if (input.GetKey(DIK_S)) {
		direction.y = -1.0f;
	}
	velocity = Vector2::Normalize(direction) * speed;
	transform.Translate(velocity);
}

void Player::ClampInWindow2D() {
	
}

void Player::ClampInWindow1D() { 
	transform.position.y = 0.0f; 
}
