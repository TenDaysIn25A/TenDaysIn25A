#include "TitleScene.h"

TitleScene::TitleScene() { Initialize(); };

void TitleScene::Initialize() {

	transform.position = { 0.0f,0.0f };
	width = 1280.0f;
	height = 720.0f;
	grHandle = Novice::LoadTexture("./Resources/images/title.png");
}

void TitleScene::Update() {

	input.Update();

}

void TitleScene::Draw() const {

	

}

void TitleScene::SetCamera() {


}