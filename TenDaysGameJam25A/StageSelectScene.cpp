#include "StageSelectScene.h"

StageSelectScene::StageSelectScene() { Initialize(); };

void StageSelectScene::Initialize() {

	buttonToStage.Initialize();
	buttonToRightSide.Initialize();
	buttonToLeftSide.Initialize();
	buttonToTitle.Initialize();

	buttonToLeftSide.transform.position = { -550.0f,0.0f };
	buttonToRightSide.transform.position = { 550.0f,0.0f };
	buttonToStage.transform.position = { 0.0f,-250.0f };
	buttonToTitle.transform.position = { -590.0f,310.0f };

	buttonToLeftSide.width = 128.0f;
	buttonToLeftSide.height = 128.0f;
	buttonToRightSide.width = 128.0f;
	buttonToRightSide.height = 128.0f;
	buttonToStage.width = 200.0f;
	buttonToStage.height = 100.0f;
	buttonToTitle.width = 40.0f;
	buttonToTitle.height = 40.0f;

	currentStage = Stage::STAGE1;
}

void StageSelectScene::Update() {

	input.Update();
	buttonToStage.Update();
	buttonToRightSide.Update();
	buttonToLeftSide.Update();
	buttonToTitle.Update();

	if (buttonToRightSide.IsClicked()) {

		if (currentStage == Stage::STAGE1) {
			currentStage = Stage::STAGE2;
		} else if (currentStage == Stage::STAGE2) {
			currentStage = Stage::STAGE3;
		} 
	}

	if (buttonToLeftSide.IsClicked()) {

		if (currentStage == Stage::STAGE3) {
			currentStage = Stage::STAGE2;
		} else if (currentStage == Stage::STAGE2) {
			currentStage = Stage::STAGE1;
		}
	}

}

void StageSelectScene::Draw() const {
	buttonToStage.Draw();
	buttonToRightSide.Draw();
	buttonToLeftSide.Draw();
	buttonToTitle.Draw();
}

void StageSelectScene::SetCamera() {

}