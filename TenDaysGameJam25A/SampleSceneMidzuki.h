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

	Transform2D chochinMouthBottom;
	float chochinMouthBottomWidth;
	float chochinMouthBottomHeight;
	int grHandleChochinMouthBottom;
	float chochinMouthBottomTheta;

	Transform2D chochinMouthTop;
	float chochinMouthTopWidth;
	float chochinMouthTopHeight;
	int grHandleChochinMouthTop;
	float chochinMouthTopTheta;

	Transform2D chochinEies;
	float chochinEiesWidth;
	float chochinEiesHeight;
	int grHandleChochinEies;
	float chochinEiesTheta;
	int chochinEiesRotateTimer;
	const float kChochinEiesOffsetX = 0.0f;
	const float kChochinEiesOffsetY = 320.0f;

	float chochinAmplitudeX;
	float chochinAmplitudeY;
	float chochinWavingThetaX;
	float chochinWavingThetaY;
	float chochinThetaSpeed;
	const float kChochinMouthOffsetX = 500.0f;
	const float kChochinMouthOffsetY = -200.0f;

	unsigned int chochinColor;

	PlayerTest samplePlayer;
	Player player;
	ParryState parryState;
	Enemy enemy;


};
