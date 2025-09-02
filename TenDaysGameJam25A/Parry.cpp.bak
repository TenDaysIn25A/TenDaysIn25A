#include "Parry.h"


Parry::Parry() { Initialize(); }

void Parry::Initialize() {
	parryState = ParryState::NONE;
}

void Parry::Update(float noteX, float noteWidth, float noteHeight, Vector2 playerPos, float playerWidth, float playerHeight) {

	input.Update();

	// プレイヤーがノーツに触れたときパリィ可能
	if (Collision::BoxToBox(playerPos, playerWidth, playerHeight, { noteX,playerPos.y }, noteWidth, noteHeight)) {
		isParryAble = true;
	} else {
		isParryAble = false;
	}

	if (!isParryAble) {
		parryState = ParryState::NONE;

		canParryTimer = 0;

		return;
	}

	canParryTimer++;

	if (input.GetKeyTrigger(DIK_SPACE)) {
		
		// パリィ判定
		if (canParryTimer < kJustParryAbleGrace) {
			parryState = ParryState::JUST;
		} else if (canParryTimer < kNomalParryAbleGrace) {
			parryState = ParryState::NORMAL;
		}
	}

	if (canParryTimer >= kNomalParryAbleGrace) {
		parryState = ParryState::NONE;
	}

	
}
