#include "Stage2Scene.h"

Stage2Scene::Stage2Scene() { Initialize(); }

void Stage2Scene::Initialize() {

	stage2Boss.Initialize();

	currentDimension = DimensionState::TWO;
}

void Stage2Scene::Update() {

	stage2Boss.Update();

	SetCamera();
}

void Stage2Scene::Draw() const {

	stage2Boss.Draw();

}

void Stage2Scene::SetCamera() {
	stage2Boss.SetCamera(camera);
}

void Stage2Scene::CheckHitAll() {

}
