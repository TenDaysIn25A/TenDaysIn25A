#pragma once
#include "Renderer.h" // 描画を扱うライブラリ（必ずSetCameraを呼び出すこと）
#include "Transform2D.h" // スケール 回転 平行移動を扱うライブラリ
#include "Input.h" // inputを使えるようにするライブラリ
#include "DrawEffects.h" // エフェクトを描画できるようにするライブラリ

class PlayerTest {
public:

	// ----------------------------------------------
	// メンバ関数
	// ----------------------------------------------

	PlayerTest(); // 宣言時に自動で初期化
	~PlayerTest() = default;
	
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

	// ----------------------------------------------
	// メンバ変数
	// ----------------------------------------------

	// システム
	// ----------------------------------------------
	Input input;
	DrawEffects effect;

	// プレイヤープロパティ
	// ----------------------------------------------

	Transform2D transform; // positionとか宣言しなくてええんやで

	float speed;
	Vector2 direction;
	Vector2 velocity;

	int isAlive;
};
