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
	currentWalker = DimesionWalker::PLAYER;
	color = 0xFFFFFFFF;
}

void BackGround::Update() {

	input.Update();
	click.Update();

	if (currentWalker == DimesionWalker::PLAYER) {

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
				currentDimension = (currentDimension == DimensionState::TWO) ? DimensionState::ONE : DimensionState::TWO;
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
			isChanging = false;
		}
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

	if (currentWalker == DimesionWalker::BOSS) {
		Novice::DrawSprite(static_cast<int>(underBGPos.x), static_cast<int>(underBGPos.y), grHandleHalfBg, 1.0f, 1.0f, 0.0f, kBossColor);

		Novice::DrawSprite(static_cast<int>(topBGPos.x), static_cast<int>(topBGPos.y), grHandleHalfBg, 1.0f, 1.0f, static_cast<float>(M_PI), kBossColor);
	} else {
		Novice::DrawSprite(static_cast<int>(underBGPos.x), static_cast<int>(underBGPos.y), grHandleHalfBg, 1.0f, 1.0f, 0.0f, color);

		Novice::DrawSprite(static_cast<int>(topBGPos.x), static_cast<int>(topBGPos.y), grHandleHalfBg, 1.0f, 1.0f, static_cast<float>(M_PI), color);
	}
}