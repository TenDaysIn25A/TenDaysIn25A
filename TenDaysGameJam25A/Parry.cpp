#include "Parry.h"


Parry::Parry() { Initialize(); }

void Parry::Initialize() {
	color = 0xFFFF00FF;
	parryState = ParryState::NONE;
	fillMode = kFillModeWireFrame;
}

void Parry::Update() {

	isParry = false;
	parryState = ParryState::NONE;

	if (currentDimension == DimensionState::ONE) {
		if (controler.IsPary()) {
			isParry = true;
		}
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
