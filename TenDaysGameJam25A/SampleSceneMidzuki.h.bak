#pragma once
#include "Dlib.h"
#include "PlayerTest.h"
#include"Player.h"
#include"Enemy.h"
#include"Parry.h"
#include"Light.h"

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
	void CheckHitAll();
	

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


	//システム
	//-------------------------------------
	Input input;
	Transform2D camera;
	DimensionState dimensionState;
	Renderer renderer;
	Light light;

	Transform2D box;
	float boxWidth;
	float boxHeight;

	Transform2D playerLeftTop;
	Transform2D playerRightTop;
	Transform2D playerLeftBottom;
	Transform2D playerRightBottom;
	Vector2 radius;

	unsigned int leftTopColor;
	unsigned int rightTopColor;
	unsigned int leftBottomColor;
	unsigned int rightBottomColor;

	PlayerTest samplePlayer;
	Player player;
	ParryState parryState;
	Enemy enemy;


};
