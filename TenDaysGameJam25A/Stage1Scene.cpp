#include "Stage1Scene.h"

Stage1Scene::Stage1Scene() { Initialize(); }

void Stage1Scene::Initialize() {

	enemy.Initialize();

	currentDimension = DimensionState::TWO;
}
void Stage1Scene::Update() {


	enemy.Update();


	SetCamera();
}

void Stage1Scene::Draw() const {

	enemy.Draw();

}

void Stage1Scene::SetCamera() {
	enemy.SetCamera(camera);
}

void Stage1Scene::CheckHitAll() {

}
