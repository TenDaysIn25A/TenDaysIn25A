#pragma once
#include "Dlib.h"
#include "PlayerTest.h"
#include"Player.h"
#include"Enemy.h"
#include"Parry.h"
#include"Light.h"
#include"Stage2Scene.h"

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
	Stage2Scene stage2Scene;

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
	int grHandleChochinMouthBottom0;
	int grHandleChochinMouthBottom1;
	int grHandleChochinMouthBottom2;
	int grHandleChochinMouthBottom3;
	float chochinMouthBottomTheta;

	Transform2D chochinMouthTop;
	float chochinMouthTopWidth;
	float chochinMouthTopHeight;
	int grHandleChochinMouthTop0;
	int grHandleChochinMouthTop1;
	int grHandleChochinMouthTop2;
	int grHandleChochinMouthTop3;
	float chochinMouthTopTheta;
	int chochinAnimationCount;

	Transform2D chochinEies;
	float chochinEiesWidth;
	float chochinEiesHeight;
	int grHandleChochinEies;
	float chochinEiesTheta;
	int chochinEiesRotateTimer;
	const float kChochinEiesOffsetX = 0.0f;
	const float kChochinEiesOffsetY = 320.0f;

	Transform2D chochinLight;
	float chochinLightWidth;
	float chochinLightHeight;
	int grHandleChochinLight0;
	int grHandleChochinLight1;
	int grHandleChochinLight2;
	int grHandleChochinLight3;
	float chochinLightTheta;
	float chochinLightThetaSpeed;
	bool chochinLightIsActive;
	const float kChochinLightOffsetX = -100.0f;
	const float kChochinLightOffsetY = 330.0f;

	Transform2D chochinStageColorText;
	int grHandleChochinStageColorText;
	const float chochinStageColorTextOffsetX = -284.0f;
	float chochinStageColorTextWidth;
	float chochinStageColorTextHeight;
	unsigned int chochinStageColorTextColor;
	int chochinStageTextColorChongeTimer;

	Transform2D chochinStageWhiteText;
	int grHandleChochinStageWhiteText;
	float chochinStageWhiteTextWidth;
	float chochinStageWhiteTextHeight;
	const Vector2 kChochinStageWhiteTextOffset = { 60.0f,-200.0f };

	float textAmplitudeY;
	float textWavingThetaY;


	float chochinAmplitudeX;
	float chochinAmplitudeY;
	float chochinWavingThetaX;
	float chochinWavingThetaY;
	float chochinThetaSpeed;
	const float kChochinMouthOffsetX = 550.0f;
	const float kChochinMouthOffsetY = -200.0f;

	unsigned int chochinColor;

	PlayerTest samplePlayer;
	Player player;
	int grHandlePlayer;
	float playerTheta;
	float playerWidth;
	float playerHeight;
	float playerRotateTheta;
	ParryState parryState;
};
