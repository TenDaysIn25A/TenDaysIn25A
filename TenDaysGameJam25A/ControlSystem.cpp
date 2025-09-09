#include "ControlSystem.h"

void ControlSystem::Update() {
	input.Update();
	click.Update();
	Novice::GetAnalogInputLeft(0, &stickLeftX, &stickLeftY);
	//Novice::GetAnalogInputRight(0, &stickRightX, &stickRightY);
}

int ControlSystem::IsMoveUp() {
	if (input.GetKey(DIK_W)) {
		return true;
	}

	if (stickLeftY > 0.0f) {
		return true;
	}

	return false; 
}

int ControlSystem::IsMoveDown() {
	if (input.GetKey(DIK_S)) {
		return true;
	}

	if (stickLeftY < 0.0f) {
		return true;
	}

	return false;
}

int ControlSystem::IsMoveLeft() {
	if (input.GetKey(DIK_A)) {
		return true;
	}

	if (stickLeftX < 0.0f) {
		return true;
	}

	return false;
}

int ControlSystem::IsMoveRight() {
	if (input.GetKey(DIK_D)) {
		return true;
	}

	if (stickLeftX > 0.0f) {
		return true;
	}

	return false;
}

int ControlSystem::IsShot() { 
	if (click.GetClick(0)) {
		return true;
	}

	return false; 
}

int ControlSystem::IsPary() { return 0; }

int ControlSystem::IsDimensionChange() { 
	if (click.GetClick(1)) {
		return true;
	}

	return false;
}

