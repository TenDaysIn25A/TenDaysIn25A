#include "Player.h"

Player::Player() { Initialize(); }

void Player::Initialize() {
	transform.position = {300.0f,0.0f};
	isAlive = true;
	speed = 5.0f;
}

void Player::Update() { 
	input.Update();


	if (currentDimension == DimensionState::ONE) {
		
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
