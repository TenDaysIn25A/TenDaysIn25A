#pragma once
#include "Dlib.h"
#include "PlayerTest.h"
#include"Player.h"
#include"Parry.h"

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

	PlayerTest samplePlayer;
	Player player;
	ParryState parryState;

	float noteX;
	float noteWidth;
	float noteHeight;
	float noteSpeed;
	int noteRespawnTimer;
	bool isNoteShoot;
};
