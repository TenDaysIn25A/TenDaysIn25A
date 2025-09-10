#include "ControlSystem.h"

void ControlSystem::Update() {
	input.Update();
	click.Update();
	Novice::GetAnalogInputLeft(0, &stickLeftX, &stickLeftY);
	prevL2 = checkL2;
	prevR2 = checkR2;
	checkL2 = Novice::IsPressButton(0, kPadButton10);
	checkR2 = Novice::IsPressButton(0, kPadButton11);
	//Novice::GetAnalogInputRight(0, &stickRightX, &stickRightY);
}

int ControlSystem::IsMoveUp() {
	if (input.GetKey(DIK_W)) {
		return true;
	}

	return false; 
}

int ControlSystem::IsMoveDown() {
	if (input.GetKey(DIK_S)) {
		return true;
	}
	return false;
}

int ControlSystem::IsMoveLeft() {
	if (input.GetKey(DIK_A)) {
		return true;
	}

	return false;
}

int ControlSystem::IsMoveRight() {
	if (input.GetKey(DIK_D)) {
		return true;
	}

	//if (stickLeftX > 0.0f) {
	//	return true;
	//}

	return false;
}

Vector2 ControlSystem::GetStickDirection() { return {static_cast<float>(stickLeftX), static_cast<float>(-stickLeftY)}; }


int ControlSystem::IsShot() { 
	if (click.GetClick(0)) {
		return true;
	}

	if (checkR2) {
		return true;
	}

	return false; 
}

int ControlSystem::IsPary() {
	if (click.GetClickTrigger(0)) {
		return true;
	}

	if (checkL2) {
		return true;
	}

	return false;
}

int ControlSystem::IsDimensionChange() { 
	if (click.GetClick(1)) {
		return true;
	}

	return false;
}

int ControlSystem::IsInPause() { 
	if (input.GetKeyTrigger(DIK_ESCAPE)) {
		return true;
	}

	return false; }

int ControlSystem::IsAccept() { return false; }

int ControlSystem::IsBack() { 
	if (input.GetKeyTrigger(DIK_ESCAPE)) {
		return true;
	}

	return false; 
}

