#include"SceneManager.h"

SceneManager::SceneManager() { Initialize(); };

void SceneManager::Initialize() {
	gameScene.Initialize();
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
			currentScene = Scene::INGAME;
		}

		Novice::ScreenPrintf(100, 0, "STAGE_SELECT");

		Novice::ScreenPrintf(100, 32, "SelectNow : %d",stageSelectScene.currentStage );

		break;

	case Scene::CONFIG:

		configScene.Update();
		configScene.Draw();

		Novice::ScreenPrintf(100, 0, "CONFIG");

		break;

	case Scene::CREDIT:

		creditScene.Update();
		creditScene.Draw();

		Novice::ScreenPrintf(100, 0, "CREDIT");

		break;

	case Scene::INGAME:

		gameScene.Update();
		gameScene.Draw();

		if (!gameScene.stage1Scene.enemy.isAlive||
			!gameScene.stage2Scene.enemy.isAlive||
			!gameScene.stage3Scene.enemy.isAlive||
			!gameScene.stage4Scene.enemy.isAlive||
			!gameScene.stage5Scene.enemy.isAlive) {
			ExchangeScene(Scene::GAMECLEAR);
		}

		if (!gameScene.stage1Scene.player.isAlive ||
			!gameScene.stage2Scene.player.isAlive || 
			!gameScene.stage3Scene.player.isAlive || 
			!gameScene.stage4Scene.player.isAlive || 
			!gameScene.stage5Scene.player.isAlive) {
			ExchangeScene(Scene::GAMEOVER);
		}

		Novice::ScreenPrintf(100, 0, "INGAME");

		break;

	case Scene::GAMECLEAR:

		gameClearScene.Update();
		gameClearScene.Draw();

		Novice::ScreenPrintf(100, 0, "GAMECLEAR");

		break;

	case Scene::GAMEOVER:

		gameOverScene.Update();
		gameOverScene.Draw();

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

		break;
		
	case Scene::STAGE_SELECT:
		currentScene = Scene::STAGE_SELECT;
		stageSelectScene.Initialize();

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