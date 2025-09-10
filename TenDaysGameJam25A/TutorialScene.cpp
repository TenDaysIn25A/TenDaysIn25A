#include "TutorialScene.h"

TutorialScene::TutorialScene() { Initialize(); };

void TutorialScene::Initialize() {
	zako.Initialize();
	currentTutorialLevel = 0;
	startTimer = 0;
}

void TutorialScene::Update() {
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