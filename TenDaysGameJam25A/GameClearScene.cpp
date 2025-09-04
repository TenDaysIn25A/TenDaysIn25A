#include "GameClearScene.h"
GameClearScene::GameClearScene() { Initialize(); };

void GameClearScene::Initialize() {

	buttonToRetry.Initialize();
	buttonToStageSelect.Initialize();

	buttonToRetry.transform.position = { 0.0f,-150.0f };
	buttonToStageSelect.transform.position = { 0.0f,-300.0f };

	buttonToRetry.width = 200.0f;
	buttonToRetry.height = 100.0f;
	buttonToStageSelect.width = 200.0f;
	buttonToStageSelect.height = 100.0f;

}

void GameClearScene::Update() {

	buttonToRetry.Update();
	buttonToStageSelect.Update();

}

void GameClearScene::Draw() const {

	buttonToRetry.Draw();
	buttonToStageSelect.Draw();

}

void GameClearScene::SetCamera() {

}
