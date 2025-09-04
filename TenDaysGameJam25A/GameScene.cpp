#include "GameScene.h"

GameScene::GameScene() { Initialize(); };

void GameScene::Initialize() {

	stage1Scene.Initialize();
	stage2Scene.Initialize();
	stage3Scene.Initialize();
	stage4Scene.Initialize();
	stage5Scene.Initialize();

}

void GameScene::Update() {

	switch (currentStage) {

	case Stage::STAGE1:

		stage1Scene.Update();
		stage1Scene.Draw();

		Novice::ScreenPrintf(100, 16, "Stage1");

		break;

	case Stage::STAGE2:
		stage2Scene.Update();
		stage2Scene.Draw();

		Novice::ScreenPrintf(100, 16, "Stage2");

		break;

	case Stage::STAGE3:
		stage3Scene.Update();
		stage3Scene.Draw();

		Novice::ScreenPrintf(100, 16, "Stage3");

		break;

	case Stage::STAGE4:
		stage4Scene.Update();
		stage4Scene.Draw();

		Novice::ScreenPrintf(100, 16, "Stage4");

		break;

	case Stage::STAGE5:
		stage5Scene.Update();
		stage5Scene.Draw();

		Novice::ScreenPrintf(100, 16, "Stage5");

		break;
	}
}

void GameScene::Draw()const {

}

void GameScene::ExchangeStage(Stage changeStage) {

	switch (changeStage) {

	case Stage::STAGE1:
		stage1Scene.Initialize();
		currentStage = Stage::STAGE1;

		break;

	case Stage::STAGE2:
		stage2Scene.Initialize();
		currentStage = Stage::STAGE2;

		break;

	case Stage::STAGE3:
		stage3Scene.Initialize();
		currentStage = Stage::STAGE3;

		break;

	case Stage::STAGE4:
		stage4Scene.Initialize();
		currentStage = Stage::STAGE4;

		break;

	case Stage::STAGE5:
		stage5Scene.Initialize();
		currentStage = Stage::STAGE5;

		break;
	}
}