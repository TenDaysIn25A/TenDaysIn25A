#include "SceneManager.h"

// 生成時に初期化
SceneManager::SceneManager() {
	Initialize();
	currentScene = Scene::TITLE;
};

void SceneManager::Initialize() {
	currentSelectButton = NONE;

	gameScene.Initialize();
	isPause = false;
	buttonToSelect.Initialize();
	buttonToTitle.Initialize();
	buttonToContinue.Initialize();

	buttonToSelect.transform.position = {0.0f, 0.0f};
	buttonToTitle.transform.position = {0.0f, -70.0f};
	buttonToContinue.transform.position = {0.0f, 70.0f};

	buttonToContinue.Initialize(Novice::LoadTexture("./Resources/images/back.png"), 137.0f, 44.0f);
	buttonToSelect.Initialize(Novice::LoadTexture("./Resources/images/backToSelect.png"), 377.0f, 44.0f);
	buttonToTitle.Initialize(Novice::LoadTexture("./Resources/images/backToTitle.png"), 377.0f, 44.0f);

	auHandleTitle = Novice::LoadAudio("./Resources/sounds/mus_menu.mp3");
	auHandleStageTutorial = Novice::LoadAudio("./Resources/sounds/mus_stage_tutorial.mp3");
	auHandleStage1 = Novice::LoadAudio("./Resources/sounds/mus_stage_1_fight.m4a");
	auHandleResult = Novice::LoadAudio("./Resources/sounds/mus_result.mp3");

	currentBgmVolume = kBgmVolume;
}

void SceneManager::Update() {
	controler.Update();

	switch (currentScene) {

	case Scene::TITLE:
		if (!Novice::IsPlayingAudio(bgmPlayHandle)) {
			bgmPlayHandle = Novice::PlayAudio(auHandleTitle, true, 0.3f);
		}

		titleScene.Update();
		titleScene.Draw();

		if (titleScene.buttonToStageSelect.IsClicked()) {
			ExchangeScene(Scene::STAGE_SELECT);
		}

		// if (titleScene.buttonToConfig.IsClicked()) {
		//	ExchangeScene(Scene::CONFIG);
		// }

		// if (titleScene.buttonToCredit.IsClicked()) {
		//	ExchangeScene(Scene::CREDIT);
		// }

		// Novice::ScreenPrintf(100, 0, "TITLE");

		break;

	case Scene::STAGE_SELECT:
		if (!Novice::IsPlayingAudio(bgmPlayHandle)) {
			bgmPlayHandle = Novice::PlayAudio(auHandleTitle, true, currentBgmVolume);
		}

		stageSelectScene.Update();
		stageSelectScene.Draw();
		stageSelectScene.isTutorialCleared = gameScene.tutorialScene.isClear;

		if (stageSelectScene.buttonToStage.IsClicked()) {
			Novice::StopAudio(bgmPlayHandle);

			gameScene.ExchangeStage(stageSelectScene.currentStage);
			ExchangeScene(Scene::INGAME);
		}

		if (stageSelectScene.buttonToTitle.IsClicked()) {
			ExchangeScene(Scene::TITLE);
		}

		// Novice::ScreenPrintf(100, 0, "STAGE_SELECT");

		// Novice::ScreenPrintf(100, 32, "SelectNow : %d", stageSelectScene.currentStage);

		break;

	case Scene::CONFIG:

		configScene.Update();
		configScene.Draw();

		if (configScene.buttonToTitle.IsClicked()) {
			ExchangeScene(Scene::TITLE);
		}

		// Novice::ScreenPrintf(100, 0, "CONFIG");

		break;

	case Scene::CREDIT:

		creditScene.Update();
		creditScene.Draw();

		if (creditScene.buttonToTitle.IsClicked()) {
			ExchangeScene(Scene::TITLE);
		}

		// Novice::ScreenPrintf(100, 0, "CREDIT");

		break;

	case Scene::INGAME:
		switch (stageSelectScene.currentStage) {
		case Stage::TUTORIAL:
			if (!Novice::IsPlayingAudio(bgmPlayHandle)) {
				bgmPlayHandle = Novice::PlayAudio(auHandleStageTutorial, true, currentBgmVolume);
			}
			break;
		case Stage::STAGE1:
			if (!gameScene.stage1Scene.stage1Boss.isAlive) {
				if (currentBgmVolume <= 0.0f) {
					currentBgmVolume = 0.0f;
				} else {
					currentBgmVolume -= 0.01f;
					Novice::SetAudioVolume(bgmPlayHandle, currentBgmVolume);
				}
			}

			if (gameScene.stage1Scene.stage1Boss.isPlayedAudioRoar) {
				if (!Novice::IsPlayingAudio(bgmPlayHandle)) {
					bgmPlayHandle = Novice::PlayAudio(auHandleStage1, true, currentBgmVolume);
				}
			}
			break;
		case Stage::STAGE2:
			break;
		}

		if (!isPause) {
			gameScene.Update();
		}

		gameScene.Draw();

		if (isPause) {
			buttonToContinue.prevState = buttonToContinue.state;
			buttonToContinue.state = ButtonState::NONE;
			buttonToContinue.GetMousePos();
			buttonToContinue.CheckHitCursor();
			
			buttonToSelect.prevState = buttonToSelect.state;
			buttonToSelect.state = ButtonState::NONE;
			buttonToSelect.GetMousePos();
			buttonToSelect.CheckHitCursor();

			buttonToTitle.prevState = buttonToTitle.state;
			buttonToTitle.state = ButtonState::NONE;
			buttonToTitle.GetMousePos();
			buttonToTitle.CheckHitCursor();

			if (currentSelectButton == TO_CONTINUE) {
				if (controler.IsDown()) {
					currentSelectButton = TO_SELECT;
				}
				
				if (controler.IsAccept()) {
					buttonToContinue.nextState = ButtonState::CLICKED;
				}

				buttonToContinue.state = ButtonState::HOVER;
			} else if (currentSelectButton == TO_SELECT) {
				if (controler.IsDown()) {
					currentSelectButton = TO_TITLE;
				}

				if (controler.IsUp()) {
					currentSelectButton = TO_CONTINUE;
				}

				if (controler.IsAccept()) {
					buttonToSelect.nextState = ButtonState::CLICKED;
				}

				buttonToSelect.state = ButtonState::HOVER;
			} else if (currentSelectButton == TO_TITLE) {

				if (controler.IsUp()) {
					currentSelectButton = TO_SELECT;
				}

				if (controler.IsAccept()) {
					buttonToTitle.nextState = ButtonState::CLICKED;
				}

				buttonToTitle.state = ButtonState::HOVER;
			} else {
				if (controler.IsDown()) {
					currentSelectButton = TO_CONTINUE;
				}

				if (controler.IsUp()) {
					currentSelectButton = TO_CONTINUE;
				}

				if (controler.IsAccept()) {
					currentSelectButton = TO_CONTINUE;
				}
			}

			buttonToSelect.Update();
			buttonToTitle.Update();
			buttonToContinue.Update();

			if (buttonToSelect.IsClicked()) {
				ExchangeScene(Scene::STAGE_SELECT);
				currentBgmVolume = 0.3f;
				Novice::StopAudio(bgmPlayHandle);
			}

			if (buttonToTitle.IsClicked()) {
				ExchangeScene(Scene::TITLE);
				currentBgmVolume = 0.3f;
				Novice::StopAudio(bgmPlayHandle);
			}

			if (buttonToContinue.IsClicked()) {
				isPause = false;
			}

			Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x000000BB, kFillModeSolid);

			buttonToSelect.Draw();
			buttonToTitle.Draw();
			buttonToContinue.Draw();

			// Novice::ScreenPrintf(100, 100, "Pause");
		}

		if (controler.IsInPause()) {
			isPause = !isPause;

			if (gameScene.stage1Scene.stage1Boss.isAlive) {
				if (isPause) {
					Novice::SetAudioVolume(bgmPlayHandle, kBgmVolume / 2.0f);
				} else {
					Novice::SetAudioVolume(bgmPlayHandle, kBgmVolume);
				}
			}
		}

		if (gameScene.stage1Scene.stage1Boss.isEnd || !gameScene.stage2Scene.stage2Boss.isAlive || !gameScene.stage3Scene.stage3Boss.isAlive || !gameScene.stage4Scene.enemy.isAlive ||
		    !gameScene.stage5Scene.enemy.isAlive || !gameScene.tutorialScene.zako.isAlive) {
			gameScene.tutorialScene.isClear = true;
			currentBgmVolume = 0.3f;
			Novice::StopAudio(bgmPlayHandle);
			ExchangeScene(Scene::GAMECLEAR);
		}

		if (!gameScene.player.isAlive) {
			currentBgmVolume = 0.3f;
			Novice::StopAudio(bgmPlayHandle);
			ExchangeScene(Scene::GAMEOVER);
		}

		// Novice::ScreenPrintf(100, 0, "INGAME");

		break;

	case Scene::GAMECLEAR:
		if (!Novice::IsPlayingAudio(bgmPlayHandle)) {
			bgmPlayHandle = Novice::PlayAudio(auHandleResult, true, currentBgmVolume);
		}

		gameClearScene.Update();
		gameClearScene.Draw();

		if (gameClearScene.buttonToRetry.IsClicked()) {
			Novice::StopAudio(bgmPlayHandle);
			ExchangeScene(Scene::INGAME);
		}

		if (gameClearScene.buttonToStageSelect.IsClicked()) {
			Novice::StopAudio(bgmPlayHandle);
			ExchangeScene(Scene::STAGE_SELECT);
		}

		// Novice::ScreenPrintf(100, 0, "GAMECLEAR");

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

		// Novice::ScreenPrintf(100, 0, "GAMEOVER");

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