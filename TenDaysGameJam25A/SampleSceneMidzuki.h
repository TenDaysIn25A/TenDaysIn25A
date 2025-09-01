#pragma once
#include "Dlib.h"
#include "PlayerTest.h"

class SampleSceneMidzuki {
public:

	SampleSceneMidzuki();

	/// <summary>
	/// 初期化をここに
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理をここに
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理をここに　※constによってこの中での値の変更は禁止されている。
	/// </summary>
	void Draw() const;

	// アクセッサ (Set～とか、Get～とか)
	// ----------------------------------------------

	/// <summary>
	/// 描画カメラセット
	/// </summary>
	/// <param name="camera"></param>
	void SetCamera();

	// 機能
	// ----------------------------------------------

	// ----------------------------------------------
	// メンバ変数
	// ----------------------------------------------

	Transform2D camera;
	PlayerTest samplePlayer;
};
