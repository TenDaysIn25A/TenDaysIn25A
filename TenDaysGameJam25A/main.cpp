#include "BackGround.h"
#include "Color.h"
#include "Input.h"
#include "Renderer.h"
#include "Transform2D.h"
#include <Novice.h>
#include <time.h>
#include "DrawEffects.h"
#include "PlayerTest.h"
#include "SceneManager.h"
#include "GameScene.h"
#include"Dlib.h"
#include"BackGround.h"

const char kWindowTitle[] = "LC1A_03_04_15_19_10DaysGameJam";

enum class Scene { TITLE, STAGE_SELECT, CONFIG, CREDIT, INGAME, GAMECREAR, GAMEOVER, COUNT };
enum class SampleScene { DAICHI, MIDZUKI, YUTO, GAME_SCENE, COUNT };

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Input input;
	//int grHandleBackGround = Novice::LoadTexture("./Resources/images/backGround.png");

	// ここで自身のサンプルシーンに切り替える。
	SampleScene currentSampleScene = SampleScene::GAME_SCENE;
	SampleSceneDaichi sampleSceneDaichi;
	SampleSceneMidzuki sampleSceneMidzuki;
	SampleSceneYuto sampleSceneYuto;

	Scene currentScene = Scene::TITLE;
	TitleScene titleScene;
	StageSelectScene stageSelectScene;
	GameScene gameScene;
	ConfigScene configScene;
	CreditScene creditScene;
	GameClearScene gameClearScene;
	GameOverScene gameOverScene;


	BackGround backGround;
	backGround.Initialize();


	unsigned int currentTime = static_cast<unsigned int>(time(nullptr));
	srand(currentTime);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		input.Update();
		
		// ----------------------------------------------------------
		// デバッグ用
		// ----------------------------------------------------------

		if (input.GetKeyTrigger(DIK_1)) {
			currentSampleScene = SampleScene::GAME_SCENE;
			gameScene.Initialize();
		}

		if (input.GetKeyTrigger(DIK_2)) {
			currentSampleScene = SampleScene::MIDZUKI;
			sampleSceneMidzuki.Initialize();
		}
		
		if (input.GetKeyTrigger(DIK_3)) {
			currentSampleScene = SampleScene::YUTO;
			sampleSceneYuto.Initialize();
		}
		
		if (input.GetKeyTrigger(DIK_4)) {
			currentSampleScene = SampleScene::DAICHI;
			sampleSceneDaichi.Initialize();
		}

		if (input.GetKeyTrigger(DIK_F1)) {
			currentScene = Scene::TITLE;
			titleScene.Initialize();
		}

		if (input.GetKeyTrigger(DIK_F2)) {
			currentScene = Scene::STAGE_SELECT;
			stageSelectScene.Initialize();
		}

		if (input.GetKeyTrigger(DIK_F3)) {
			currentScene = Scene::CONFIG;
			configScene.Initialize();
		}

		if (input.GetKeyTrigger(DIK_F4)) {
			currentScene = Scene::CREDIT;
			creditScene.Initialize();
		}

		if (input.GetKeyTrigger(DIK_F5)) {
			currentScene = Scene::INGAME;
			gameScene.Initialize();
		}

		if (input.GetKeyTrigger(DIK_F6)) {
			currentScene = Scene::GAMECREAR;
			gameClearScene.Initialize();
		}
		
		if (input.GetKeyTrigger(DIK_F7)) {
			currentScene = Scene::GAMEOVER;
			gameOverScene.Initialize();
		}

		if (input.GetKeyTrigger(DIK_F8)) {
			currentScene = Scene::COUNT;
			sampleSceneDaichi.Initialize();
			sampleSceneMidzuki.Initialize();
			sampleSceneYuto.Initialize();
			gameScene.Initialize();
		}

		
		// ----------------------------------------------------------
		// シーン
		// ----------------------------------------------------------

		

		// サンプルシーン、ここで各自が自由に作業できる。
		switch (currentSampleScene) {
		case SampleScene::DAICHI:
			
			sampleSceneDaichi.Update();
			sampleSceneDaichi.Draw();
			
			Novice::ScreenPrintf(0, 700, "Scene : DAICHI");
			break;
		case SampleScene::MIDZUKI:
			
			sampleSceneMidzuki.Update();
			sampleSceneMidzuki.Draw();
			
			Novice::ScreenPrintf(0, 700, "Scene : MIDZUKI");
			break;
		case SampleScene::YUTO:

			sampleSceneYuto.Update();
			sampleSceneYuto.Draw();

			Novice::ScreenPrintf(0, 700, "Scene : YUTO");
			break;

		case SampleScene::GAME_SCENE:

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
				backGround.Update();
				backGround.Draw();

				gameScene.player.miss.Draw();
				gameScene.player.just.Draw();
				gameScene.player.nice.Draw();

				Novice::ScreenPrintf(100, 0, "INGAME");

				break;

			case Scene::GAMECREAR:

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


			//Novice::ScreenPrintf(0, 700, "Scene : GAME_SCENE");
			break;
		case SampleScene::COUNT:
			break;
		default:
			break;
		}

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (input.GetKeyTrigger(DIK_ESCAPE)) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
