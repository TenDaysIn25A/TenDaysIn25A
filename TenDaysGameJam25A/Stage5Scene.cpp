#include "Stage5Scene.h"

Stage5Scene::Stage5Scene() { Initialize(); }

void Stage5Scene::Initialize() {

	enemy.Initialize();



	currentDimension = DimensionState::TWO;
}
void Stage5Scene::Update() {
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

	


	

	SetCamera();
}

void Stage5Scene::Draw() const {

	Novice::DrawBox(0, 120, 1281, 480, 0.0f, 0x000000FF, kFillModeSolid);

	enemy.Draw();



}

void Stage5Scene::SetCamera() {
	
	enemy.SetCamera(camera);
}

void Stage5Scene::CheckHitAll() {

}
