#include "TutorialScene.h"

TutorialScene::TutorialScene() {
	Initialize(); 
	isClear = false;
 };

void TutorialScene::Initialize() {
	zako.Initialize();
	currentTutorialLevel = 0;
	intervalTimer = 0;
	startTimer = 0;
	isSafe = false;
	isShot = false;

	grHandleHowToMove = Novice::LoadTexture("./Resources/images/howToMove.png");
	grHandleHowToShot = Novice::LoadTexture("./Resources/images/howToShot.png");
	grHandleHowToParitti = Novice::LoadTexture("./Resources/images/howToParicchi.png");
	grHandleHowToParry = Novice::LoadTexture("./Resources/images/howToParry.png");

	howToMoveWidth = 720.0f;
	howToMoveHeight = 72.0f;
	howToShotWidth = 709.0f;
	howToShotHeight = 67.0f;
	howToParittiWidth = 637.0f; 
	howToParittiHeight = 67.0f;
	howToParryWidth = 565.0f;
	howToParryHeight = 67.0f;
	fukidashiWidth = 885.0f;
	fukidashiHeight = 237.0f;

	tutorialFukidashi.position = { -40.0f,117.0f };
	tutorialText.position = { tutorialFukidashi.position.x,tutorialFukidashi.position.y + kTextOffsetY };

	grHandleInfoA = Novice::LoadTexture("./Resources/images/infoA.png");
	grHandleInfoB = Novice::LoadTexture("./Resources/images/infoB.png");
	grHandleInfoParry = Novice::LoadTexture("./Resources/images/infoParryA.png");
	grHandleInfoShot = Novice::LoadTexture("./Resources/images/infoShot.png");
	grHandleInfoParicchi = Novice::LoadTexture("./Resources/images/infoParicchi.png");
	grHandleFukidashi = Novice::LoadTexture("./Resources/images/fukidashi.png");

	info.position = { 430.0f,-300.0f };
	infoParryHeight = 96.0f;
	infoParryWidth = 330.0f;
	infoShotHeight = 96.0f;
	infoShotWidth = 380.0f;
	infoParicchiWidth = 390.0f;
	infoParicchiHeight = 96.0f;
	infoParicchi.position = { 30.0f,-300.0f };
}

void TutorialScene::Update() {
	input.Update();
	click.Update();
	zako.tutorialLevel = currentTutorialLevel;
	zako.tutorialInterval = intervalTimer;
	zako.Update();
	if (currentTutorialLevel == 0) {
		currentWalker = DimesionWalker::TUTORIAL;
		startTimer++;

		if (startTimer >= 60) {
			currentTutorialLevel = 1;
		}
	} else if(currentTutorialLevel == 1){

		if (intervalTimer < kTutorialInterval) {
			intervalTimer++;
		} else {

		}

	} else if (currentTutorialLevel == 2) {

		if (intervalTimer < kTutorialInterval) {
			intervalTimer++;
		} else {

		}

	} else if (currentTutorialLevel == 3) {

		if (intervalTimer < kTutorialInterval) {
			intervalTimer++;
		} else {

		}

	} else if (currentTutorialLevel == 4) {

		if (intervalTimer < kTutorialInterval) {
			intervalTimer++;
		} else {

		}
	} else if (currentTutorialLevel == 5) {

		if (intervalTimer < kTutorialInterval) {
			intervalTimer++;
		} else {
			currentTutorialLevel = 6;
			intervalTimer = 0;
			currentWalker = DimesionWalker::TUTORIAL;
		}
	} else {

		if (intervalTimer < kTutorialInterval) {
			intervalTimer++;
		}

	}
}
void TutorialScene::Draw()const {
	zako.Draw();
	


}