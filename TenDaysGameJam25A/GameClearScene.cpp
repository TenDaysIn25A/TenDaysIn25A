#include "GameClearScene.h"
GameClearScene::GameClearScene() { Initialize(); };

void GameClearScene::Initialize() {

	transform.position = { 0.0f,0.0f };

	buttonToRetry.Initialize(Novice::LoadTexture("./Resources/images/restart.png"),233.0f,44.0f);
	buttonToStageSelect.Initialize(Novice::LoadTexture("./Resources/images/go_back_to_Select.png"),377.0f,44.0f);

	buttonToRetry.transform.position = { 0.0f,-220.0f };
	buttonToStageSelect.transform.position = { 0.0f,-150.0f };

	grHandle = Novice::LoadTexture("./Resources/images/game_clear.png");
}

void GameClearScene::Update() {
	controler.Update();

	buttonToRetry.prevState = buttonToRetry.state;
	buttonToRetry.state = ButtonState::NONE;
	buttonToRetry.GetMousePos();
	buttonToRetry.CheckHitCursor();

	buttonToStageSelect.prevState = buttonToStageSelect.state;
	buttonToStageSelect.state = ButtonState::NONE;
	buttonToStageSelect.GetMousePos();
	buttonToStageSelect.CheckHitCursor();

	if (currentSelectButton == TO_RETRY) {
		if (controler.IsUp()) {
			currentSelectButton = TO_STAGESELECT;
		}

		if (controler.IsAccept()) {
			buttonToRetry.nextState = ButtonState::CLICKED;
		}

		buttonToRetry.state = ButtonState::HOVER;
	} else if (currentSelectButton == TO_STAGESELECT) {
		if (controler.IsDown()) {
			currentSelectButton = TO_RETRY;
		}

		if (controler.IsAccept()) {
			buttonToStageSelect.nextState = ButtonState::CLICKED;
		}

		buttonToStageSelect.state = ButtonState::HOVER;
	} else {

		if (controler.IsDown()) {
			currentSelectButton = TO_STAGESELECT;
		}

		if (controler.IsUp()) {
			currentSelectButton = TO_STAGESELECT;
		}

		if (controler.IsAccept()) {
			currentSelectButton = TO_STAGESELECT;
		}
	}

	buttonToRetry.Update();
	buttonToStageSelect.Update();
}

void GameClearScene::Draw() const {

	renderer.DrawBox(transform, 1280.0f, 720.0f, 0.0f, 0x000000FF, kFillModeSolid);
	renderer.DrawSprite(transform, 1008.0f, 192.0f, 0.0f, grHandle, 0xFFFFFFFF);

	buttonToRetry.Draw();
	buttonToStageSelect.Draw();

}

void GameClearScene::SetCamera() {

}
