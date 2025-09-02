#pragma once
#include "Dlib.h"
#include "Player.h"
#include "Enemy.h"

class GameScene {
public:
	GameScene();

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

	void SetIsChanging(bool flag) { isChanging = flag; };

	// 機能
	// ----------------------------------------------

	/// <summary>
	/// 全オブジェクトの当たり判定の取得
	/// </summary>
	void CheckHitAll();

	// ----------------------------------------------
	// メンバ変数
	// ----------------------------------------------

	// システム
	//-------------------------------------
	Input input;
	Transform2D camera;
	DimensionState dimensionState;
	Renderer renderer;

	Player player;
	ParryState parryState;
	Enemy enemy;

	bool isChanging;
};