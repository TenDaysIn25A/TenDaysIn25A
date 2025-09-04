#include "StageSelectScene.h"

StageSelectScene::StageSelectScene() { Initialize(); };

void StageSelectScene::Initialize() {

	

}

void StageSelectScene::Update() {

	input.Update();

	if (input.GetKeyTrigger(DIK_Z)) {
		currentStage = Stage::STAGE1;
	}

	if (input.GetKeyTrigger(DIK_X)) {
		currentStage = Stage::STAGE2;
	}
	
	if (input.GetKeyTrigger(DIK_C)) {
		currentStage = Stage::STAGE3;
	}
	
	if (input.GetKeyTrigger(DIK_V)) {
		currentStage = Stage::STAGE4;
	}
	
	if (input.GetKeyTrigger(DIK_B)) {
		currentStage = Stage::STAGE5;
	}

}

void StageSelectScene::Draw() const {



}

void StageSelectScene::SetCamera() {

}