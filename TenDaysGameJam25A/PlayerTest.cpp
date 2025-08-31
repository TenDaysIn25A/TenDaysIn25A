#include "PlayerTest.h"

PlayerTest::PlayerTest() { Initialize(); }

void PlayerTest::Initialize() { 
	speed = 10.0f; 
	direction = Vector2::Normalize({1.0f, 1.0f});
	velocity = direction * speed;
	isAlive = true;
}
	
void PlayerTest::Update() {
	
}

void PlayerTest::Draw() const {}
