#include"SceneManager.h"

SceneManager::SceneManager() { Initialize(); };

void SceneManager::Initialize() {
	gameScene.Initialize();
	isPause = false;
	buttonToSelectFromPause.Initialize();
	buttonToTitleFromPause.Initialize();
	buttonToContinueFromPause.Initialize();
	
	buttonToSelectFromPause.transform.position = { 0.0f,-150.0f };
	buttonToTitleFromPause.transform.position = { 0.0f,-200.0f };
	buttonToContinueFromPause.transform.position = { -590.0f,310.0f };

	buttonToContinueFromPause.width = 40.0f;
	buttonToContinueFromPause.height = 40.0f;

}

void SceneManager::Update() {

	switch (currentScene) {

	case Scene::TITLE:

		titleScene.Update();
		titleScene.Draw();
		
		if (titleScene.buttonToStageSelect.IsClicked()) {
			ExchangeScene(Scene::STAGE_SELECT);
		}
		
		if (titleScene.buttonToConfig.IsClicked()) {
			ExchangeScene(Scene::CONFIG);
		}
		
		if (titleScene.buttonToCredit.IsClicked()) {
			ExchangeScene(Scene::CREDIT);
		}

		Novice::ScreenPrintf(100, 0, "TITLE");

		break;

	case Scene::STAGE_SELECT:

		stageSelectScene.Update();
		stageSelectScene.Draw();

		if (stageSelectScene.buttonToStage.IsClicked()) {
			gameScene.ExchangeStage(stageSelectScene.currentStage);
			ExchangeScene(Scene::INGAME);
		}

		if (stageSelectScene.buttonToTitle.IsClicked()) {
			ExchangeScene(Scene::TITLE);
		}

		Novice::ScreenPrintf(100, 0, "STAGE_SELECT");

		Novice::ScreenPrintf(100, 32, "SelectNow : %d", stageSelectScene.currentStage);

		break;

	case Scene::CONFIG:

		configScene.Update();
		configScene.Draw();

		if (configScene.buttonToTitle.IsClicked()) {
			ExchangeScene(Scene::TITLE);
		}

		Novice::ScreenPrintf(100, 0, "CONFIG");

		break;

	case Scene::CREDIT:

		creditScene.Update();
		creditScene.Draw();

		if (creditScene.buttonToTitle.IsClicked()) {
			ExchangeScene(Scene::TITLE);
		}

		Novice::ScreenPrintf(100, 0, "CREDIT");

		break;

	case Scene::INGAME:

		input.Update();
		if (!isPause) {
			gameScene.Update();
		}

		gameScene.Draw();

		if (isPause) {
			buttonToSelectFromPause.Update();
			buttonToTitleFromPause.Update();
			buttonToContinueFromPause.Update();

			if (buttonToSelectFromPause.IsClicked()) {
				ExchangeScene(Scene::STAGE_SELECT);
			}

			if (buttonToTitleFromPause.IsClicked()) {
				ExchangeScene(Scene::TITLE);
			}

			if (buttonToContinueFromPause.IsClicked()) {
				isPause = false;
			}

			Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x000000BB, kFillModeSolid);

			buttonToSelectFromPause.Draw();
			buttonToTitleFromPause.Draw();
			buttonToContinueFromPause.Draw();

			Novice::ScreenPrintf(100, 100, "Pause");
		}

		if (input.GetKeyTrigger(DIK_ESCAPE)) {
			isPause = !isPause;
		}

		if (!gameScene.stage1Scene.enemy.isAlive ||
			!gameScene.stage2Scene.enemy.isAlive ||
			!gameScene.stage3Scene.enemy.isAlive ||
			!gameScene.stage4Scene.enemy.isAlive ||
			!gameScene.stage5Scene.enemy.isAlive) {
			ExchangeScene(Scene::GAMECLEAR);
		}

		if (!gameScene.player.isAlive ) {
			ExchangeScene(Scene::GAMEOVER);
		}

		Novice::ScreenPrintf(100, 0, "INGAME");

		break;

	case Scene::GAMECLEAR:

		gameClearScene.Update();
		gameClearScene.Draw();

		if (gameClearScene.buttonToRetry.IsClicked()) {
			ExchangeScene(Scene::INGAME);
		}

		if (gameClearScene.buttonToStageSelect.IsClicked()) {
			ExchangeScene(Scene::STAGE_SELECT);
		}

		Novice::ScreenPrintf(100, 0, "GAMECLEAR");

		break;

	case Scene::GAMEOVER:

		gameOverScene.Update();
		gameOverScene.Draw();


		if (gameOverScene.buttonToRetry.IsClicked()) {
			ExchangeScene(Scene::INGAME);
		}

		if (gameOverScene.buttonToStageSelect.IsClicked()) {
			ExchangeScene(Scene::STAGE_SELECT);
		}

		Novice::ScreenPrintf(100, 0, "GAMEOVER");

		break;

	default:

		break;
	}
}

void SceneManager::ExchangeScene(Scene changeScene) {

	switch (changeScene) {
	case Scene::TITLE:
		currentScene = Scene::TITLE;
		titleScene.Initialize();
		Initialize();

		break;

	case Scene::STAGE_SELECT:
		currentScene = Scene::STAGE_SELECT;
		stageSelectScene.memCurrentStage = stageSelectScene.currentStage;
		stageSelectScene.Initialize();
		Initialize();
		stageSelectScene.currentStage = stageSelectScene.memCurrentStage;
		break;

	case Scene::CONFIG:
		currentScene = Scene::CONFIG;
		configScene.Initialize();

		break;

	case Scene::CREDIT:
		currentScene = Scene::CREDIT;
		creditScene.Initialize();

		break;

	case Scene::INGAME:
		currentScene = Scene::INGAME;
		gameScene.Initialize();

		break;

	case Scene::GAMECLEAR:
		currentScene = Scene::GAMECLEAR;
		gameClearScene.Initialize();

		break;

	case Scene::GAMEOVER:
		currentScene = Scene::GAMEOVER;
		gameOverScene.Initialize();

		break;
	}
}