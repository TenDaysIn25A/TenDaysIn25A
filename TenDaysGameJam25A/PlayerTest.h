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

	// 根幹
	// ----------------------------------------------

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
	/// mainやGameSceneからカメラを取得してください。
	/// </summary>
	/// <param name="camera"></param>
	void SetCamera(const Transform2D& camera);

	// 機能
	// ----------------------------------------------
	
	/// <summary>
	/// 移動
	/// </summary>
	void Move();

	/// <summary>
	/// 画面内にクランプする。
	/// </summary>
	void ClampInWindow2D();

	// ----------------------------------------------
	// メンバ変数
	// ----------------------------------------------

	// システム
	// ----------------------------------------------
	Renderer renderer;	// 描画ライブラリをこれで使えるようにしてください。
	Input input;		// 入力ライブラリをこれで使えるようにしてください。
	DrawEffects effect;	// エフェクト描画ライブラリをこれで使えるようにしてください。

	// プレイヤープロパティ
	// ----------------------------------------------

	Transform2D transform; // positionとか宣言しなくてええんやで

	float speed;
	Vector2 direction;
	Vector2 velocity;

	float radius;

	bool isAlive;
};
