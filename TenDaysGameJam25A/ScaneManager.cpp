#include"SceneManager.h"

SceneManager::SceneManager() { Initialize(); };

void SceneManager::Initialize() {

}

void SceneManager::Update() {

	switch (currentScene) {

	case Scene::TITLE:

		titleScene.Update();
		titleScene.Draw();

		Novice::ScreenPrintf(100, 0, "TITLE");

		break;

	case Scene::STAGE_SELECT:

		stageSelectScene.Update();
		stageSelectScene.Draw();

		Novice::ScreenPrintf(100, 0, "STAGE_SELECT");

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

		gameScene.SetIsChanging(backGround.isChanging);
		gameScene.Update();
		gameScene.Draw();


		gameScene.player.miss.Draw();
		gameScene.player.just.Draw();
		gameScene.player.nice.Draw();

		if (!gameScene.enemy.isAlive) {
			ExchangeScene(Scene::GAMECLEAR);
		}

		if (!gameScene.player.isAlive) {
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