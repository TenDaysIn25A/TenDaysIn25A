#include "BackGround.h"

BackGround::BackGround() { Initialize(); }

void BackGround::Initialize() {

	underBGPos = twoDimBGPosBottom;
	topBGPos = twoDimBGPosTop;
	grHandleHalfBg = Novice::LoadTexture("./Resources/images/halfBackGround.png");

	isChanging = false;
	tweenStep = 0;
	t = 0.0f;
	duration = 0.15f;
	dimansionState = DimensionState::TWO;
	currentDimension = DimensionState::TWO;
}

void BackGround::Update() {

	input.Update();
	click.Update();

	if (click.GetClickNotAnswer(1)) {

		if (currentDimension == DimensionState::ONE) {

			if (!isChanging) {
				Activate();
			}
		}
	}

	if (isChanging) {

		t += 1.0f / 60.0f / duration;
		if (t > 1.0f) {
			t = 1.0f;
		}

		if (tweenStep == 0) {
			underBGPos.y = startUnder.y + (midUnder.y - startUnder.y) * Tweening::Easing(t, ease);
			topBGPos.y = startTop.y + (midTop.y - startTop.y) * Tweening::Easing(t, ease);

			if (t >= 1.0f) {
				tweenStep = 1;
				t = 0.0f;
				startUnder = underBGPos;
				startTop = topBGPos;
				isChanging = false;
				currentDimension = (currentDimension == DimensionState::TWO) ? DimensionState::ONE : DimensionState::TWO;
			}
		}
	}

	if (tweenStep == 1) {

		t += 1.0f / 60.0f / duration;
		if (t > 1.0f) {
			t = 1.0f;
		}
		underBGPos.y = startUnder.y + (endUnder.y - startUnder.y) * Tweening::Easing(t, ease);
		topBGPos.y = startTop.y + (endTop.y - startTop.y) * Tweening::Easing(t, ease);

		if (t >= 1.0f) {
			underBGPos = endUnder;
			topBGPos = endTop;
		}
	}
}

void BackGround::Activate() {
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

void BackGround::Draw() const {

	Novice::DrawSprite(static_cast<int>(underBGPos.x), static_cast<int>(underBGPos.y), grHandleHalfBg, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);

	Novice::DrawSprite(static_cast<int>(topBGPos.x), static_cast<int>(topBGPos.y), grHandleHalfBg, 1.0f, 1.0f, static_cast<float>(M_PI), 0xFFFFFFFF);
}