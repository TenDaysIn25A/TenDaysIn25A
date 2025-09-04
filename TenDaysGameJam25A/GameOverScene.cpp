#include "GameOverScene.h"

GameOverScene::GameOverScene() { Initialize(); };

void GameOverScene::Initialize() {

	buttonToRetry.Initialize();
	buttonToStageSelect.Initialize();

	buttonToRetry.transform.position = { 0.0f,-150.0f };
	buttonToStageSelect.transform.position = { 0.0f,-300.0f };

	buttonToRetry.width = 200.0f;
	buttonToRetry.height = 100.0f;
	buttonToStageSelect.width = 200.0f;
	buttonToStageSelect.height = 100.0f;
}

void GameOverScene::Update() {

	buttonToRetry.Update();
	buttonToStageSelect.Update();

}

void GameOverScene::Draw() const {

	buttonToRetry.Draw();
	buttonToStageSelect.Draw();

}

void GameOverScene::SetCamera() {

}