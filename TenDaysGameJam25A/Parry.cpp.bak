#include "Parry.h"


Parry::Parry() { Initialize(); }

void Parry::Initialize() {
	parryState = ParryState::NONE;
	isJustParry = false;
	isNomalParry = false;
	isParryFailed = false;
}

int Parry::isPlayerParry(Vector2 notePos, float noteWidth, float noteHeight, Vector2 playerPos, float playerWidth, float playerHeight) {
	Initialize();

	int canParryTimer = 0;


	if (Collision::BoxToBox(playerPos, playerWidth, playerHeight, notePos, noteWidth, noteHeight)) {
		isParryAble = true;
	} else {
		isParryAble = false;
	}

	if (!isParryAble) {
		canParryTimer = 0;

		return false;
	}

	canParryTimer++;

	if (canParryTimer < kJustParryAbleGrace) {

		if (input.GetKeyTrigger(DIK_SPACE)) {
			isJustParry = true;

			return isJustParry;
		}

	} else if (canParryTimer < kNomalParryAbleGrace) {

		if (input.GetKeyTrigger(DIK_SPACE)) {
			isNomalParry = true;

			return isNomalParry;
		}
	} else {
		isParryFailed = true;

		return false;
	}

	return false;
}
