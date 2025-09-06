#pragma once
#include "Dlib.h"
#include "Player.h"
#include "Enemy.h"
#include"BackGround.h"
#include"Stage1Scene.h"
#include"Stage2Scene.h"
#include"Stage3Scene.h"
#include"Stage4Scene.h"
#include"Stage5Scene.h"

class GameScene{

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

	void ExchangeStage(Stage changeStage);

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
	BackGround backGround;
	Stage currentStage;
	Click click;

	Player player;
	ParryState parryState;
	Enemy enemy;
	Stage1Scene stage1Scene;
	Stage2Scene stage2Scene;
	Stage3Scene stage3Scene;
	Stage4Scene stage4Scene;
	Stage5Scene stage5Scene;

	bool isChanging;

};
