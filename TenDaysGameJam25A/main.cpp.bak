#include "Color.h"
#include "Input.h"
#include "Renderer.h"
#include "Transform2D.h"
#include <Novice.h>
#include <time.h>
#include "DrawEffects.h"
#include "PlayerTest.h"
#include "SceneManager.h"

const char kWindowTitle[] = "LC1A_03_04_15_19_10DaysGameJam";

enum class Scene { TITLE, INGAME, GAMECREAR, GAMEOVER , COUNT };
enum class SampleScene { DAICHI, MIDZUKI, YUTO, COUNT };

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Input input;
	int grHandleBackGround = Novice::LoadTexture("./Resources/images/backGround.png");

	// ここで自身のサンプルシーンに切り替える。
	SampleScene currentSampleScene = SampleScene::DAICHI;
	SampleSceneDaichi sampleSceneDaichi;
	SampleSceneMidzuki sampleSceneMidzuki;
	SampleSceneYuto sampleSceneYuto;

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

		// 黒背景
		Novice::DrawSprite(0, 0, grHandleBackGround, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);

		if (input.GetKeyTrigger(DIK_1)) {
			currentSampleScene = SampleScene::DAICHI;
			sampleSceneDaichi.Initialize();
		}

		if (input.GetKeyTrigger(DIK_2)) {
			currentSampleScene = SampleScene::MIDZUKI;
			sampleSceneMidzuki.Initialize();
		}
		
		if (input.GetKeyTrigger(DIK_3)) {
			currentSampleScene = SampleScene::YUTO;
			sampleSceneYuto.Initialize();
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
