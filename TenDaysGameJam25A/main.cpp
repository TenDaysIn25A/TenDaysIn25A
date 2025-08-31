#include "Color.h"
#include "Input.h"
#include "Renderer.h"
#include "Transform2D.h"
#include <Novice.h>
#include <time.h>
#include "DrawEffects.h"
#include "PlayerTest.h"

const char kWindowTitle[] = "LC1A_03_04_15_19_10DaysGameJam";

enum class Scene { TITLE, INGAME, GAMECREAR, GAMEOVER ,COUNT };

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Input input;
	DrawEffects effects;
	Transform2D camera;
	effects.SetColor(0xFF0000FF);
	effects.StartExplosion({0.0f, 0.0f}, 100.0f, 1.0f, camera, EASE_OUT_QUAD);

	PlayerTest player;

	float s = 1.0f;
	int c = 0;

	unsigned int currentTime = static_cast<unsigned int>(time(nullptr));
	srand(currentTime);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		input.Update();
		
		if (!effects.GetIsActive()) {
			c++;
			if (c % 2 == 0) {
				effects.StartExplosion({0.0f, 0.0f}, 100.0f * s, 1.0f, camera, EASE_OUT_QUAD);
			} else {
				effects.StartImplosion({0.0f, 0.0f}, 100.0f * s, 1.0f, camera, EASE_OUT_QUAD);
			}
		}
		
		player.Update();
		player.Draw();

		effects.SetScale(s);
		s += 0.0016f;

		effects.Update();
		effects.Draw();

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
