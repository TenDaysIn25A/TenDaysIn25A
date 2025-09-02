#include "Parry.h"


Parry::Parry() { Initialize(); }

void Parry::Initialize() {
	color = 0xFFFF00FF;
	parryState = ParryState::NONE;
	
}

void Parry::Update() {

	input.Update();

	parryState = ParryState::NONE;

	if (input.GetKeyTrigger(DIK_SPACE)) {
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

	//if (!isParryAble) {
	//	parryState = ParryState::NONE;

	//	color = 0xFFFF00FF;
	//	fillMode = kFillModeWireFrame;

	//	canJustTimer = 0;

	//	return;
	//}

	//if (isCanJust) {

	//	canJustTimer++;

	//	if (input.GetKeyTrigger(DIK_SPACE)) {

	//		// ジャストパリィ判定
	//		if (canJustTimer < kJustParryAbleGrace) {
	//			parryState = ParryState::JUST;
	//			color = 0xFF0000FF;
	//		}
	//	}

	//	if (canJustTimer >= kJustParryAbleGrace) {
	//		isCanJust = false;
	//		parryState = ParryState::NONE;
	//	}

	//} else {

	//	// ノーマルパリィ判定
	//	if (input.GetKeyTrigger(DIK_SPACE)) {
	//		parryState = ParryState::NORMAL;
	//	}
	//	
	//}

	//if (parryState == ParryState::NONE) {
	//	color = 0xFFFF00FF;
	//	fillMode = kFillModeWireFrame;
	//} else {
	//	fillMode = kFillModeSolid;
	//}
}

void Parry::Draw() const {
	// パリィ可能範囲
	renderer.DrawBox(transform, width, height, 0.0f, color, fillMode);
}

void Parry::SetCamera(const Transform2D& camera) { renderer.SetCamera(camera); }
