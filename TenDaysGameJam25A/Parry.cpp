#include "Parry.h"


Parry::Parry() { Initialize(); }

void Parry::Initialize() {
	color = 0xFFFF00FF;
	parryState = ParryState::NONE;
}

void Parry::Update() {

	input.Update();

	if (!isParryAble) {
		parryState = ParryState::NONE;

		color = 0xFFFF00FF;
		kFillMode = kFillModeWireFrame;

		canJustTimer = 0;

		return;
	}



	if (isCanJust) {

		canJustTimer++;

		if (input.GetKeyTrigger(DIK_SPACE)) {

			// ジャストパリィ判定
			if (canJustTimer < kJustParryAbleGrace) {
				parryState = ParryState::JUST;
				color = 0xFF0000FF;
			}
		}

		if (canJustTimer >= kJustParryAbleGrace) {
			isCanJust = false;
			parryState = ParryState::NONE;
		}

	} else {

		// ノーマルパリィ判定
		if (input.GetKeyTrigger(DIK_SPACE)) {
			parryState = ParryState::NORMAL;
		}
		
	}

	if (parryState == ParryState::NONE) {
		color = 0xFFFF00FF;
		kFillMode = kFillModeWireFrame;
	} else {
		kFillMode = kFillModeSolid;
	}
}

void Parry::Draw() const {
	// パリィ可能範囲
	Novice::DrawBox(
		static_cast<int>(transform.position.x - width / 2.0f),
		static_cast<int>(transform.position.y - height / 2.0f),
		static_cast<int>(width),
		static_cast<int>(height),
		0.0f,
		color,
		kFillMode
	);
}
