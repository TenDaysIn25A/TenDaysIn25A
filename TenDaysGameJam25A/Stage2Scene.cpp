#include "Stage2Scene.h"

Stage2Scene::Stage2Scene() { Initialize(); }

void Stage2Scene::Initialize() {

	enemy.Initialize();

	backGround.Initialize();

	currentDimension = DimensionState::TWO;
}
void Stage2Scene::Update() {
	// ここで各更新処理を行う
	input.Update();

	backGround.Update();
	
	if (backGround.isChanging) {
		return;
	}


	if (input.GetKeyTrigger(DIK_0)) {
		if (currentDimension == DimensionState::ONE) {
			currentDimension = DimensionState::TWO;
		} else {
			currentDimension = DimensionState::ONE;
		}
	}

	if (input.GetKeyTrigger(DIK_I)) {
		Initialize();
	}

	enemy.Update();




	SetCamera();
}

void Stage2Scene::Draw() const {

	Novice::DrawBox(0, 120, 1281, 480, 0.0f, 0x000000FF, kFillModeSolid);

	enemy.Draw();

	backGround.Draw();


}

void Stage2Scene::SetCamera() {
	enemy.SetCamera(camera);
}

void Stage2Scene::CheckHitAll() {

}
