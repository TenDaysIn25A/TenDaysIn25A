#include "Stage3Scene.h"

Stage3Scene::Stage3Scene() { Initialize(); }

void Stage3Scene::Initialize() {

	stage3Boss.Initialize();



	currentDimension = DimensionState::TWO;
}
void Stage3Scene::Update() {
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

	stage3Boss.Update();

	
	SetCamera();
}

void Stage3Scene::Draw() const {

	Novice::DrawBox(0, 120, 1281, 480, 0.0f, 0x000000FF, kFillModeSolid);

	stage3Boss.Draw();



}

void Stage3Scene::SetCamera() {
	
	stage3Boss.SetCamera(camera);
}

void Stage3Scene::CheckHitAll() {

}
