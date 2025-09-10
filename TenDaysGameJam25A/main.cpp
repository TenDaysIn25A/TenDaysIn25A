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
//#include"BackGround.h"

const char kWindowTitle[] = "1003_パリッチ";


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

	SceneManager sceneManager;

	DeltaTime deltaTime;
	deltaTime.Initialize();

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

		
		// ----------------------------------------------------------
		// シーン
		// ----------------------------------------------------------

		

		// サンプルシーン、ここで各自が自由に作業できる。
		switch (currentSampleScene) {
		case SampleScene::DAICHI:
			
			sampleSceneDaichi.Update();
			sampleSceneDaichi.Draw();
			
			//Novice::ScreenPrintf(0, 700, "Scene : DAICHI");
			break;
		case SampleScene::MIDZUKI:
			
			sampleSceneMidzuki.Update();
			sampleSceneMidzuki.Draw();
			
			//Novice::ScreenPrintf(0, 700, "Scene : MIDZUKI");
			break;
		case SampleScene::YUTO:

			sampleSceneYuto.Update();
			sampleSceneYuto.Draw();

			//Novice::ScreenPrintf(0, 700, "Scene : YUTO");
			break;

		case SampleScene::GAME_SCENE:

			sceneManager.Update();

			if (sceneManager.titleScene.buttonToEnd.IsClicked()) {
				sceneManager.currentScene = Scene::END;
			}

			//Novice::ScreenPrintf(0, 700, "Scene : GAME_SCENE");
			break;
		case SampleScene::COUNT:
			break;
		default:
			break;
		}

		deltaTime.Update();
		//Novice::ScreenPrintf(1260, 0, "%d", static_cast<int>(1.0f / deltaTime.deltaTime));

		// フレームの終了
		Novice::EndFrame();

		if (sceneManager.currentScene == Scene::END) {
			break;
		}


	}


	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
