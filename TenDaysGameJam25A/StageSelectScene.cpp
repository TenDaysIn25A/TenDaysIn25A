#include "StageSelectScene.h"

StageSelectScene::StageSelectScene() {
	Initialize();
	tutorialDefault = { 0.0f,0.0f };
	chochinStageDefault = { 550.0f,0.0f };
	isTutorialCleared = false;
};

void StageSelectScene::Initialize() {

	buttonToStage.Initialize();
	buttonToRightSide.Initialize();
	buttonToLeftSide.Initialize();
	buttonToTitle.Initialize();

	buttonToLeftSide.transform.position = { -550.0f,0.0f };
	buttonToRightSide.transform.position = { 550.0f,0.0f };
	buttonToStage.transform.position = { 0.0f,-200.0f };
	buttonToTitle.transform.position = { -550.0f,320.0f };

	//buttonToLeftSide.width = 128.0f;
	//buttonToLeftSide.height = 128.0f;
	//buttonToRightSide.width = 128.0f;
	//buttonToRightSide.height = 128.0f;
	//buttonToStage.width = 200.0f;
	//buttonToStage.height = 100.0f;
	//buttonToTitle.width = 40.0f;
	//buttonToTitle.height = 40.0f;

	buttonToStage.Initialize(Novice::LoadTexture("./Resources/images/battleStart.png"), 287.0f, 67.0f);
	buttonToRightSide.Initialize(Novice::LoadTexture("./Resources/images/right.png"), 69.0f, 80.0f);
	buttonToLeftSide.Initialize(Novice::LoadTexture("./Resources/images/left.png"), 69.0f, 80.0f);
	buttonToTitle.Initialize(Novice::LoadTexture("./Resources/images/back.png"), 137.0f, 44.0f);

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

	tutorialFishBone.position = { tutorialDefault.x + kTutorialStageTextOffset.x, tutorialDefault.y + kTutorialStageTextOffset.y };
	tutorialFishBoneHeight = 220.0f;
	tutorialFishBoneWidth = 80.0f;
	tutorialFishBone.rotation = 0.0f;
	tutorialFishBone.Rotate(90.0f);
	grHandleTutorialFishBone = Novice::LoadTexture("./Resources/images/fishBoneBickBottom.png");

	tutorialStageText.position = kTutorialStageTextOffset;
	grhandleTutorialStageText = Novice::LoadTexture("./Resources/images/tutorial.png");
	tutorialStageTextWidth = 497.0f;
	tutorialStageTextHeight = 67.0f;

	textAmplitudeY = 30.0f;
	textWavingThetaY = 0.0f;
	chochinStageColorTextColor = 0xFFFFFFFF;

	backGround.position = { 0.0f,0.0f };

	isAnimationLeftMove = false;

	currentSelectButton = TO_NONE;
}

void StageSelectScene::Update() {

	input.Update();
	
	controler.Update();

	buttonToStage.prevState = buttonToStage.state;
	buttonToStage.state = ButtonState::NONE;
	buttonToStage.GetMousePos();
	buttonToStage.CheckHitCursor();

	buttonToRightSide.prevState = buttonToRightSide.state;
	buttonToRightSide.state = ButtonState::NONE;
	buttonToRightSide.GetMousePos();
	buttonToRightSide.CheckHitCursor();

	buttonToLeftSide.prevState = buttonToLeftSide.state;
	buttonToLeftSide.state = ButtonState::NONE;
	buttonToLeftSide.GetMousePos();
	buttonToLeftSide.CheckHitCursor();

	buttonToTitle.prevState = buttonToTitle.state;
	buttonToTitle.state = ButtonState::NONE;
	buttonToTitle.GetMousePos();
	buttonToTitle.CheckHitCursor();

	if (currentSelectButton == TO_STAGE) {
		if (controler.IsUp()) {
			currentSelectButton = TO_RIGHTSIDE;
		}
		
		if (controler.IsRight()) {
			currentSelectButton = TO_RIGHTSIDE;
		}
		
		if (controler.IsLeft()) {
			currentSelectButton = TO_LEFTSIDE;
		}

		if (controler.IsDown()) {
		}
		
		if (controler.IsAccept()) {
			buttonToStage.nextState = ButtonState::CLICKED;
		}
		
		buttonToStage.state = ButtonState::HOVER;

	} else if (currentSelectButton == TO_RIGHTSIDE) {
		if (controler.IsUp()) {
			currentSelectButton = TO_TITLE;
		}

		if (controler.IsRight()) {
			buttonToRightSide.nextState = ButtonState::CLICKED;
		}

		if (controler.IsLeft()) {
			currentSelectButton = TO_LEFTSIDE;
		}

		if (controler.IsDown()) {
			currentSelectButton = TO_STAGE;
		}

		if (controler.IsAccept()) {
			buttonToRightSide.nextState = ButtonState::CLICKED;
		}

		buttonToRightSide.state = ButtonState::HOVER;
	} else if (currentSelectButton == TO_LEFTSIDE) {
		if (controler.IsUp()) {
			currentSelectButton = TO_TITLE;
		}

		if (controler.IsRight()) {
			currentSelectButton = TO_RIGHTSIDE;
		}

		if (controler.IsLeft()) {
			buttonToLeftSide.nextState = ButtonState::CLICKED;
		}

		if (controler.IsDown()) {
			currentSelectButton = TO_STAGE;
		}

		if (controler.IsAccept()) {
			buttonToLeftSide.nextState = ButtonState::CLICKED;
		}
		buttonToLeftSide.state = ButtonState::HOVER;
	} else if (currentSelectButton == TO_TITLE) {

		if (controler.IsRight()) {
			currentSelectButton = TO_RIGHTSIDE;
		}

		if (controler.IsLeft()) {
			currentSelectButton = TO_LEFTSIDE;
		}

		if (controler.IsDown()) {
			currentSelectButton = TO_LEFTSIDE;
		}

		if (controler.IsAccept()) {
			buttonToTitle.nextState = ButtonState::CLICKED;
		}
		buttonToTitle.state = ButtonState::HOVER;
	} else {
		if (controler.IsUp()) {
			currentSelectButton = TO_STAGE;
		}

		if (controler.IsRight()) {
			currentSelectButton = TO_STAGE;
		}

		if (controler.IsLeft()) {
			currentSelectButton = TO_STAGE;
		}

		if (controler.IsDown()) {
			currentSelectButton = TO_STAGE;
		}

		if (controler.IsAccept()) {
			currentSelectButton = TO_STAGE;
		}
	}

	buttonToStage.Update();
	buttonToRightSide.Update();
	buttonToLeftSide.Update();
	buttonToTitle.Update();


	if (chochinAnimationCount > 3) {
		chochinAnimationCount = 0;
	} else {
		chochinAnimationCount++;
	}

	if (isTutorialCleared) {

		if (isAnimationLeftMove || isAnimationRightMove) {

			if (isAnimationLeftMove) {

				chochinStageDefault.x -= animationFirtSpeed;
				tutorialDefault.x -= animationFirtSpeed;
				animationFirtSpeed -= kAnimationAcceleration;

				if (animationFirtSpeed < 2.0f) {
					animationFirtSpeed = 0.0f;
					isAnimationLeftMove = false;
				}

			} else {
				chochinStageDefault.x += animationFirtSpeed;
				tutorialDefault.x += animationFirtSpeed;
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
				}
			}

			if (buttonToLeftSide.IsClicked()) {

				if (currentStage == Stage::STAGE1) {
					currentStage = Stage::TUTORIAL;
					animationFirtSpeed = 88.0f;
					isAnimationRightMove = true;
				}
			}
		}
	}

	chochinLight.position = { chochinStageDefault.x + kChochinLightOffsetX,chochinStageDefault.y + kChochinLightOffsetY };
	tutorialFishBone.position = { tutorialDefault.x + kTutorialStageTextOffset.x, tutorialDefault.y + kTutorialStageTextOffset.y };

	chochinStageWhiteText.position.y = sinf(textWavingThetaY) * textAmplitudeY + kChochinStageWhiteTextOffset.y;
	tutorialStageText.position.y = sinf(textWavingThetaY) * textAmplitudeY + kChochinStageWhiteTextOffset.y;

	textWavingThetaY += float(M_PI) / 60.0f;

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
	
	renderer.DrawSprite(tutorialFishBone, tutorialFishBoneWidth, tutorialFishBoneHeight, 0.0f, grHandleTutorialFishBone, 0xFFFFFFFF);

	buttonToStage.Draw();
	buttonToRightSide.Draw();
	buttonToLeftSide.Draw();
	buttonToTitle.Draw();

	if (currentStage == Stage::TUTORIAL) {


		renderer.DrawSprite(tutorialStageText, tutorialStageTextWidth, tutorialStageTextHeight, 0.0f, grhandleTutorialStageText, 0xFFFFFFFF);
	} else if (currentStage == Stage::STAGE1) {
		renderer.DrawSprite(chochinStageWhiteText, chochinStageWhiteTextWidth, chochinStageWhiteTextHeight, 0.0f, grHandleChochinStageWhiteText, 0xFFFFFFFF);
		renderer.DrawSprite(chochinStageColorText, chochinStageColorTextWidth, chochinStageColorTextHeight, 0.0f, grHandleChochinStageColorText, chochinStageColorTextColor);
	} else {

	}
}

void StageSelectScene::SetCamera() {

}