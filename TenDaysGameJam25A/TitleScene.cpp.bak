#include "TitleScene.h"

TitleScene::TitleScene() { Initialize(); };

void TitleScene::Initialize() {
	transform.position = { 0.0f,0.0f };
	width = 1280.0f;
	height = 720.0f;
	grHandle = Novice::LoadTexture("./Resources/images/title.png");

	buttonToStageSelect.Initialize();
	buttonToConfig.Initialize();
	buttonToCredit.Initialize();

	buttonToStageSelect.transform.position = {0.0f, -100.0f};
	buttonToConfig.transform.position = {0.0f, -150.0f};
	buttonToCredit.transform.position = {0.0f, -200.0f};
}

void TitleScene::Update() {
	input.Update();
	buttonToStageSelect.Update();
	buttonToConfig.Update();
	buttonToCredit.Update();
}

void TitleScene::Draw() const {
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x000000FF, kFillModeSolid);
	renderer.DrawSprite(transform, width, height, 0.0f, grHandle, 0xFFFFFFFF);

	buttonToStageSelect.Draw();
	buttonToConfig.Draw();
	buttonToCredit.Draw();
}

void TitleScene::SetCamera() {


}