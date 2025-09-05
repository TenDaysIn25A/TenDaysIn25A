#include "Stage3Scene.h"

Stage3Scene::Stage3Scene() { Initialize(); }

void Stage3Scene::Initialize() {

	enemy.Initialize();

	backGround.Initialize();

	currentDimension = DimensionState::TWO;
}
void Stage3Scene::Update() {
	// ここで各更新処理を行う
	input.Update();

	backGround.Update();
	
	if (backGround.isChanging) {
		return;
	}

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

void Stage3Scene::Draw() const {

	Novice::DrawBox(0, 120, 1281, 480, 0.0f, 0x000000FF, kFillModeSolid);

	enemy.Draw();

	backGround.Draw();

}

void Stage3Scene::SetCamera() {
	
	enemy.SetCamera(camera);
}

void Stage3Scene::CheckHitAll() {

}
