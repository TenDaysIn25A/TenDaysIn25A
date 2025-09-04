#include "StageSelectScene.h"

StageSelectScene::StageSelectScene() { Initialize(); };

void StageSelectScene::Initialize() {

	buttonToStage.Initialize();
	buttonToRightSide.Initialize();
	buttonToLeftSide.Initialize();

	buttonToLeftSide.transform.position = { -550.0f,0.0f };
	buttonToRightSide.transform.position = { 550.0f,0.0f };
	buttonToStage.transform.position = { 0.0f,-250.0f };

	buttonToLeftSide.width = 128.0f;
	buttonToLeftSide.height = 128.0f;
	buttonToRightSide.width = 128.0f;
	buttonToRightSide.height = 128.0f;
	buttonToStage.width = 200.0f;
	buttonToStage.height = 100.0f;

	currentStage = Stage::STAGE1;
}

void StageSelectScene::Update() {

	input.Update();
	buttonToStage.Update();
	buttonToRightSide.Update();
	buttonToLeftSide.Update();

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

	//if (input.GetKeyTrigger(DIK_Z)) {
	//	currentStage = Stage::STAGE1;
	//}

	//if (input.GetKeyTrigger(DIK_X)) {
	//	currentStage = Stage::STAGE2;
	//}

	//if (input.GetKeyTrigger(DIK_C)) {
	//	currentStage = Stage::STAGE3;
	//}

	//if (input.GetKeyTrigger(DIK_V)) {
	//	currentStage = Stage::STAGE4;
	//}

	//if (input.GetKeyTrigger(DIK_B)) {
	//	currentStage = Stage::STAGE5;
	//}

}

void StageSelectScene::Draw() const {

	buttonToStage.Draw();
	buttonToRightSide.Draw();
	buttonToLeftSide.Draw();

}

void StageSelectScene::SetCamera() {

}