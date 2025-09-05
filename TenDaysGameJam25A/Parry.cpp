#include "Parry.h"


Parry::Parry() { Initialize(); }

void Parry::Initialize() {
	color = 0xFFFF00FF;
	parryState = ParryState::NONE;
	
}

void Parry::Update() {

	input.Update();

	click.Update();

	parryState = ParryState::NONE;

	if (click.GetClickTrigger(0)) {
		isParry = true;
	} else {
		isParry = false;
	}

	if (isParry) {
		fillMode = kFillModeSolid;
	} else {
		fillMode = kFillModeWireFrame;
		color = 0xFFFF00FF;
	}
}

void Parry::Draw() const {
	if (currentDimension != DimensionState::ONE) {
		return;
	}

	// パリィ可能範囲
	renderer.DrawBox(transform, width, height, 0.0f, color, fillMode);
}

void Parry::SetCamera(const Transform2D& camera) { renderer.SetCamera(camera); }
