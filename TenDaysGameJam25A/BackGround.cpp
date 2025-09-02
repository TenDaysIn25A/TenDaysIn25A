#include "BackGround.h"

BackGround::BackGround() { Initialize(); }

void BackGround::Initialize() {

	underBGPos = underTwoDirBGPos;
	topBGPos = topTwoDirBGPos;
	grHandleHalfBg = Novice::LoadTexture("./Resources/images/halfBackGround.png");
	speed = 20.0f;
}

void BackGround::Update() {

	input.Update();

	if (currentDimension == DimensionState::ONE) {

		if (input.GetKeyTrigger(DIK_F)) {

			if (!isChanging) {
				isChanging = true;
			}
		}

	} else {

		if (input.GetKeyTrigger(DIK_F)) {

			if (!isChanging) {
				isChanging = true;
			}
		}
	}

	if (isChanging) {

		if (currentDimension == DimensionState::ONE) {

			underBGPos.y -= speed;
			topBGPos.y += speed;

			if (underBGPos.y <= topBGPos.y) {

				speed *= -1.0f;

			}

			if (underBGPos.y > underTwoDirBGPos.y) {
				underBGPos.y = underTwoDirBGPos.y;
				topBGPos.y = topTwoDirBGPos.y;
				currentDimension = DimensionState::TWO;
				isChanging = false;
			}



		} else {

			underBGPos.y -= speed;
			topBGPos.y += speed;

			if (underBGPos.y <= topBGPos.y) {

				speed *= -1.0f;

			}

			if (underBGPos.y > underOneDirBGPos.y) {
				underBGPos.y = underOneDirBGPos.y;
				topBGPos.y = topOneDirBGPos.y;
				currentDimension = DimensionState::ONE;
				isChanging = false;
			}

		}

	}

}

void BackGround::Draw() {

	// 黒背景
	Novice::DrawSprite(
		static_cast<int>(underBGPos.x),
		static_cast<int>(underBGPos.y),
		grHandleHalfBg, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);

	Novice::DrawSprite(
		static_cast<int>(topBGPos.x),
		static_cast<int>(topBGPos.y),
		grHandleHalfBg, 1.0f, 1.0f, static_cast<float>(M_PI), 0xFFFFFFFF);

}


