#include "StageSelectScene.h"

StageSelectScene::StageSelectScene() {
	Initialize();
	chochinStageDefault = { 550.0f,0.0f };
};

void StageSelectScene::Initialize() {

	buttonToStage.Initialize();
	buttonToRightSide.Initialize();
	buttonToLeftSide.Initialize();
	buttonToTitle.Initialize();

	buttonToLeftSide.transform.position = { -550.0f,0.0f };
	buttonToRightSide.transform.position = { 550.0f,0.0f };
	buttonToStage.transform.position = { 0.0f,-300.0f };
	buttonToTitle.transform.position = { -590.0f,310.0f };

	buttonToLeftSide.width = 128.0f;
	buttonToLeftSide.height = 128.0f;
	buttonToRightSide.width = 128.0f;
	buttonToRightSide.height = 128.0f;
	buttonToStage.width = 200.0f;
	buttonToStage.height = 100.0f;
	buttonToTitle.width = 40.0f;
	buttonToTitle.height = 40.0f;

	currentStage = Stage::TUTORIAL;


	chochinAnimationCount = 0;
	animationFirtSpeed = 88.0f;

	chochinLight.position = { chochinStageDefault.x + kChochinLightOffsetX ,chochinStageDefault.y + kChochinLightOffsetY };
	chochinLightWidth = 345.0f;
	chochinLightHeight = 220.0f;
	grHandleStageSelectChochinLight0 = Novice::LoadTexture("./Resources/images/stageSelectChochinLight0.png");
	grHandleStageSelectChochinLight1 = Novice::LoadTexture("./Resources/images/stageSelectChochinLight1.png");
	grHandleStageSelectChochinLight2 = Novice::LoadTexture("./Resources/images/stageSelectChochinLight2.png");
	grHandleStageSelectChochinLight3 = Novice::LoadTexture("./Resources/images/stageSelectChochinLight3.png");
	chochinLightTheta = 110.0f;

	chochinStageWhiteText.position = { kChochinStageWhiteTextOffset };
	grHandleChochinStageWhiteText = Novice::LoadTexture("./Resources/images/chochinStageWhiteTxt.png");
	chochinStageWhiteTextWidth = 418.0f;
	chochinStageWhiteTextHeight = 60.0f;

	chochinStageColorText.position = { chochinStageWhiteText.position.x + chochinStageColorTextOffsetX,chochinStageWhiteText.position.y };
	grHandleChochinStageColorText = Novice::LoadTexture("./Resources/images/chochinStageColorTxt.png");
	chochinStageColorTextWidth = 128.0f;
	chochinStageColorTextHeight = 60.0f;
	chochinStageTextColorChongeTimer = 180;

	chochinTextAmplitudeY = 30.0f;
	chochinTextWavingThetaY = 0.0f;
	chochinStageColorTextColor = 0xFFFFFFFF;

	backGround.position = { 0.0f,0.0f };

	isAnimationLeftMove = false;


}

void StageSelectScene::Update() {

	input.Update();
	buttonToStage.Update();
	buttonToRightSide.Update();
	buttonToLeftSide.Update();
	buttonToTitle.Update();

	chochinLight.position = { chochinStageDefault.x + kChochinLightOffsetX,chochinStageDefault.y + kChochinLightOffsetY };


	if (chochinAnimationCount > 3) {
		chochinAnimationCount = 0;
	} else {
		chochinAnimationCount++;
	}

	if (isAnimationLeftMove || isAnimationRightMove) {

		if (isAnimationLeftMove) {

			chochinStageDefault.x -= animationFirtSpeed;

			animationFirtSpeed -= kAnimationAcceleration;

			if (animationFirtSpeed < 2.0f) {
				animationFirtSpeed = 0.0f;
				isAnimationLeftMove = false;
			}

		} else {
			chochinStageDefault.x += animationFirtSpeed;

			animationFirtSpeed -= kAnimationAcceleration;

			if (animationFirtSpeed < 2.0f) {
				animationFirtSpeed = 0.0f;
				isAnimationRightMove = false;
			}
		}



	} else {
		if (buttonToRightSide.IsClicked()) {

			if (currentStage == Stage::TUTORIAL) {
				currentStage = Stage::STAGE1;
				isAnimationLeftMove = true;
				animationFirtSpeed = 88.0f;
			} else if (currentStage == Stage::STAGE1) {
				currentStage = Stage::STAGE2;
				isAnimationLeftMove = true;
				animationFirtSpeed = 88.0f;
			}
		}

		if (buttonToLeftSide.IsClicked()) {

			if (currentStage == Stage::STAGE2) {
				currentStage = Stage::STAGE1;
				animationFirtSpeed = 88.0f;
				isAnimationRightMove = true;
			} else if (currentStage == Stage::STAGE1) {
				currentStage = Stage::TUTORIAL;
				animationFirtSpeed = 88.0f;
				isAnimationRightMove = true;
			}
		}
	}



	chochinStageWhiteText.position.y = sinf(chochinTextWavingThetaY) * chochinTextAmplitudeY + kChochinStageWhiteTextOffset.y;

	chochinTextWavingThetaY += float(M_PI) / 60.0f;

	chochinStageColorText.position.y = chochinStageWhiteText.position.y;

	if (chochinStageTextColorChongeTimer > 0) {
		chochinStageTextColorChongeTimer--;

		if (chochinStageTextColorChongeTimer == 60) {
			chochinStageColorTextColor = 0x00FFFFFF;

		} else if (chochinStageTextColorChongeTimer == 55) {
			chochinStageColorTextColor = 0x00FFFFFF;
		} else if (chochinStageTextColorChongeTimer == 51) {
			chochinStageColorTextColor = 0x00FFFFFF;

		} else if (chochinStageTextColorChongeTimer == 120) {
			chochinStageColorTextColor = 0x00FFFFFF;
		}

		if (chochinStageTextColorChongeTimer == 57) {
			chochinStageColorTextColor = 0xFFFFFFFF;

		} else if (chochinStageTextColorChongeTimer == 53) {
			chochinStageColorTextColor = 0xFFFFFFFF;
		} else if (chochinStageTextColorChongeTimer == 41) {
			chochinStageColorTextColor = 0xFFFFFFFF;
		} else if (chochinStageTextColorChongeTimer == 116) {
			chochinStageColorTextColor = 0xFFFFFFFF;
		}

		if (chochinStageTextColorChongeTimer == 160) {
			chochinStageColorTextColor = 0xFFFFFFFF;
		}

	} else {
		chochinStageTextColorChongeTimer = 180;
		chochinStageColorTextColor = 0xFFFF00FF;
	}

}

void StageSelectScene::Draw() const {

	renderer.DrawBox(backGround, 1280.0f, 720.0f, 0.0f, 0x000000FF, kFillModeSolid);

	if (chochinAnimationCount == 0) {

		renderer.DrawSprite(chochinLight, chochinLightWidth, chochinLightHeight, chochinLightTheta, grHandleStageSelectChochinLight0, chochinStageColorTextColor);

	} else if (chochinAnimationCount == 1) {

		renderer.DrawSprite(chochinLight, chochinLightWidth, chochinLightHeight, chochinLightTheta, grHandleStageSelectChochinLight1, chochinStageColorTextColor);

	} else if (chochinAnimationCount == 2) {

		renderer.DrawSprite(chochinLight, chochinLightWidth, chochinLightHeight, chochinLightTheta, grHandleStageSelectChochinLight2, chochinStageColorTextColor);

	} else {

		renderer.DrawSprite(chochinLight, chochinLightWidth, chochinLightHeight, chochinLightTheta, grHandleStageSelectChochinLight3, chochinStageColorTextColor);

	}

	buttonToStage.Draw();
	buttonToRightSide.Draw();
	buttonToLeftSide.Draw();
	buttonToTitle.Draw();

	if(currentStage == Stage::TUTORIAL){


	}else if (currentStage == Stage::STAGE1) {
		renderer.DrawSprite(chochinStageWhiteText, chochinStageWhiteTextWidth, chochinStageWhiteTextHeight, 0.0f, grHandleChochinStageWhiteText, 0xFFFFFFFF);
		renderer.DrawSprite(chochinStageColorText, chochinStageColorTextWidth, chochinStageColorTextHeight, 0.0f, grHandleChochinStageColorText, chochinStageColorTextColor);
	} else {

	}
}

void StageSelectScene::SetCamera() {

}