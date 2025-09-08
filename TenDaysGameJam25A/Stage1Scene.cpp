#include "Stage1Scene.h"

Stage1Scene::Stage1Scene() { Initialize(); }

void Stage1Scene::Initialize() {

	stage1Boss.Initialize();

	currentDimension = DimensionState::TWO;
}

void Stage1Scene::Update() {

	stage1Boss.Update();

	SetCamera();
}

void Stage1Scene::Draw() const {

	stage1Boss.Draw();

}

void Stage1Scene::SetCamera() {
	stage1Boss.SetCamera(camera);
}

void Stage1Scene::CheckHitAll() {

}
