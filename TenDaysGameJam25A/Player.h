#pragma once
#include "Dlib.h"

class Player {
public:
	// ----------------------------------------------
	// メンバ関数
	// ----------------------------------------------

	Player(); // 宣言時に自動で初期化
	~Player() = default;

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

	/// <summary>
	/// 中央に揃える。
	/// </summary>
	void ClampInWindow1D();

	// ----------------------------------------------
	// メンバ変数
	// ----------------------------------------------

	// システム
	// ----------------------------------------------
	Renderer renderer;  // 描画ライブラリをこれで使えるようにしてください。
	Input input;        // 入力ライブラリをこれで使えるようにしてください。
	DrawEffects effect; // エフェクト描画ライブラリをこれで使えるようにしてください。

	// プレイヤープロパティ
	// ----------------------------------------------

	Transform2D transform;

	float speed;
	Vector2 direction;
	Vector2 velocity;

	float width;
	float height;
	int grHandleCaracter;

	bool isAlive;
};
