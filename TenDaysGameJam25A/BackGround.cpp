#include "BackGround.h"

BackGround::BackGround() { Initialize(); }

void BackGround::Initialize() {

	underBGPos = twoDimBGPosBottom;
	topBGPos = twoDimBGPosTop;
	grHandleHalfBg = Novice::LoadTexture("./Resources/images/halfBackGround.png");

	isChanging = false;
	tweenStep = 0;
	t = 0.0f;
	duration = 0.25f;
}

void BackGround::Update() {

	input.Update();

	if (input.GetKeyTrigger(DIK_F) && !isChanging) {
		isChanging = true;
		tweenStep = 0;
		t = 0.0f;

		startUnder = underBGPos;
		startTop = topBGPos;

		midUnder = midDimBGPosBottom;

		midTop = midDimBGPosTop;

		if (currentDimension == DimensionState::TWO) { 
			endUnder = oneDimBGPosBottom;
			endTop = oneDimBGPosTop;
		} else { 
			endUnder = twoDimBGPosBottom;
			endTop = twoDimBGPosTop;
		}
	}

	if (isChanging) {

		t += 1.0f / 60.0f / duration;
		if (t > 1.0f) t = 1.0f;

		if (tweenStep == 0) {
			underBGPos.y = startUnder.y + (midUnder.y - startUnder.y) * Tweening::Easing(t, EASE_INOUT_QUAD);
			topBGPos.y   = startTop.y + (midTop.y - startTop.y) * Tweening::Easing(t, EASE_INOUT_QUAD);

			if (t >= 1.0f) {
				tweenStep = 1;
				t = 0.0f;
				startUnder = underBGPos;
				startTop = topBGPos;
			}

		} else if (tweenStep == 1) {
			underBGPos.y = startUnder.y + (endUnder.y - startUnder.y) * Tweening::Easing(t, EASE_INOUT_QUAD);
			topBGPos.y   = startTop.y + (endTop.y - startTop.y) * Tweening::Easing(t, EASE_INOUT_QUAD);

			if (t >= 1.0f) {
				underBGPos = endUnder;
				topBGPos = endTop;

				currentDimension = (currentDimension == DimensionState::TWO) ? DimensionState::ONE : DimensionState::TWO;
				isChanging = false;
			}
		}
	}
}

void BackGround::Draw() {

	Novice::DrawSprite(
		static_cast<int>(underBGPos.x),
		static_cast<int>(underBGPos.y),
		grHandleHalfBg, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);

	Novice::DrawSprite(
		static_cast<int>(topBGPos.x),
		static_cast<int>(topBGPos.y),
		grHandleHalfBg, 1.0f, 1.0f, static_cast<float>(M_PI), 0xFFFFFFFF);
}