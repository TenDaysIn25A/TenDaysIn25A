#include "GameOverScene.h"

GameOverScene::GameOverScene() { Initialize(); };

void GameOverScene::Initialize() {
	transform.position = { 0.0f,0.0f };

	buttonToRetry.Initialize();
	buttonToStageSelect.Initialize();

	buttonToRetry.transform.position = { 0.0f,-150.0f };
	buttonToStageSelect.transform.position = { 0.0f,-300.0f };

	buttonToRetry.width = 200.0f;
	buttonToRetry.height = 100.0f;
	buttonToStageSelect.width = 200.0f;
	buttonToStageSelect.height = 100.0f;

	grHandle = Novice::LoadTexture("./Resources/images/gameover.png");
}

void GameOverScene::Update() {
	buttonToRetry.Update();
	buttonToStageSelect.Update();
}

void GameOverScene::Draw() const {

	renderer.DrawBox(transform, 1280.0f, 720.0f, 0.0f, 0x000000FF, kFillModeSolid);
	renderer.DrawSprite(transform, 1168.0f, 208.0f, 0.0f, grHandle, 0xFFFFFFFF);

	buttonToRetry.Draw();
	buttonToStageSelect.Draw();

}

void GameOverScene::SetCamera() {

}