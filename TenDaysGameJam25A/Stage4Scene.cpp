#include "Stage4Scene.h"

Stage4Scene::Stage4Scene() { Initialize(); }

void Stage4Scene::Initialize() {

	enemy.Initialize();



	currentDimension = DimensionState::TWO;
}
void Stage4Scene::Update() {
	// ここで各更新処理を行う
	input.Update();


	
	if (input.GetKeyTrigger(DIK_I)) {
		Initialize();
	}

	if (input.GetKeyTrigger(DIK_0)) {
		if (currentDimension == DimensionState::ONE) {
			currentDimension = DimensionState::TWO;
		} else {
			currentDimension = DimensionState::ONE;
		}
	}

	enemy.Update();

	

	CheckHitAll();

	

	SetCamera();
}

void Stage4Scene::Draw() const {

	Novice::DrawBox(0, 120, 1281, 480, 0.0f, 0x000000FF, kFillModeSolid);

	enemy.Draw();




}

void Stage4Scene::SetCamera() {
	
	enemy.SetCamera(camera);
}

void Stage4Scene::CheckHitAll() {

	
}

